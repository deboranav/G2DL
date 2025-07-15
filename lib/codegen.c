#include "codegen.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

/*
 * =================================================================================
 * Protótipos das Funções de Geração
 * =================================================================================
 */
static void generate_expression(ASTNode *node);
static void generate_statement(ASTNode *node, int indent_level);
static void generate_definitions(ASTNode *node);
static void generate_implementations(ASTNode *node);
static void generate_main_body(ASTNode *node);


/*
 * =================================================================================
 * Função Principal (Ponto de Entrada)
 * =================================================================================
 */
void generate_code(ASTNode* root) {
    if (!root) return;

    // 1. Cabeçalhos padrão do C
    printf("#include <stdio.h>\n");
    printf("#include <stdlib.h>\n");
    printf("#include <string.h>\n");
    printf("#include <math.h>\n\n");
    printf("double runtime_input_c() { char b[256]; if(fgets(b,256,stdin)){return atof(b);} return 0.0; }\n\n");
    
    // 2. Primeira Passada: Gera typedefs de structs e protótipos de funções
    generate_definitions(root);
    printf("\n");

    // 3. Segunda Passada: Gera as implementações completas das funções
    generate_implementations(root);
    printf("\n");

    // 4. Terceira Passada: Gera a função main() com o código executável
    printf("int main(void) {\n");
    generate_main_body(root);
    printf("\n    return 0;\n}\n");
}


/*
 * =================================================================================
 * Lógica das Passadas de Geração
 * =================================================================================
 */

// Passada 1: Gera typedefs e protótipos.
void generate_definitions(ASTNode* node) {
    if (!node) return;
    if (node->type == AST_STATEMENT_LIST) {
        generate_definitions(node->left);
        generate_definitions(node->right);
    } else if (node->type == AST_TYPE_DEF) {
        printf("typedef struct %s %s;\n", node->left->value.strVal, node->left->value.strVal);
    } else if (node->type == AST_FUNC_DEF) {
        generate_expression(node->left);    // Tipo de retorno
        printf(" %s(", node->value.strVal); // Nome da função
        if (node->aux) generate_expression(node->aux); // Parâmetros
        printf(");\n");
    }
}

// Passada 2: Gera a implementação das funções.
void generate_implementations(ASTNode* node) {
    if (!node) return;
    if (node->type == AST_STATEMENT_LIST) {
        generate_implementations(node->left);
        generate_implementations(node->right);
    } else if (node->type == AST_TYPE_DEF) {
        // Gera a definição completa da struct
        printf("struct %s {\n", node->left->value.strVal);
        generate_statement(node->right, 1);
        printf("};\n\n");
    } else if (node->type == AST_FUNC_DEF) {
        // Gera a implementação completa da função
        generate_expression(node->left);    // Tipo de retorno
        printf(" %s(", node->value.strVal); // Nome da função
        if (node->aux) generate_expression(node->aux); // Parâmetros
        printf(") {\n");
        generate_statement(node->right, 1); // Corpo da função
        printf("}\n\n");
    }
}

// Passada 3: Gera o corpo da main.
void generate_main_body(ASTNode* node) {
    if (!node) return;
    if (node->type == AST_STATEMENT_LIST) {
        generate_main_body(node->left);
        generate_main_body(node->right);
    } else if (node->type != AST_TYPE_DEF && node->type != AST_FUNC_DEF) {
        generate_statement(node, 1);
    }
}


/*
 * =================================================================================
 * Funções Auxiliares Recursivas
 * =================================================================================
 */

// Gera o código para um COMANDO (statements que terminam em ';', ou estruturas de controle)
void generate_statement(ASTNode* node, int indent_level) {
    if (!node) return;

    char indent[100];
    for(int i = 0; i < indent_level * 4; ++i) indent[i] = ' ';
    indent[indent_level * 4] = '\0';

    switch(node->type) {
        case AST_STATEMENT_LIST: generate_statement(node->left, indent_level); generate_statement(node->right, indent_level); break;
        case AST_VAR_DECL:       printf("%s", indent); generate_expression(node->left); printf(" "); generate_expression(node->right); printf(";\n"); break;
        case AST_MATRIX_DECL:    printf("%sdouble %s[", indent, node->value.strVal); generate_expression(node->left); printf("]["); generate_expression(node->right); printf("];\n"); break;
        case AST_ASSIGN:         printf("%s", indent); generate_expression(node->left); printf(" = "); generate_expression(node->right); printf(";\n"); break;
        case AST_PRINTF:         printf("%s", indent); printf("printf("); generate_expression(node->left); if (node->right) { printf(", "); generate_expression(node->right); } printf(");\n"); break;
        case AST_RETURN:         printf("%sreturn ", indent); generate_expression(node->left); printf(";\n"); break;
        
        case AST_IF:
            printf("%sif (", indent); generate_expression(node->left); printf(") {\n");
            generate_statement(node->right, indent_level + 1);
            printf("%s}", indent);
            if(node->aux){ if (node->aux->type == AST_IF) { printf(" else "); generate_statement(node->aux, indent_level); } else { printf(" else {\n"); generate_statement(node->aux, indent_level + 1); printf("%s}", indent); } }
            printf("\n"); break;
        
        case AST_WHILE: 
            printf("%swhile (", indent); generate_expression(node->left); printf(") {\n"); 
            generate_statement(node->right, indent_level + 1); printf("\n%s}\n", indent); break;
        
        default: // Se não for um statement conhecido, deve ser uma expressão (ex: chamada de função)
            printf("%s", indent); generate_expression(node); printf(";\n"); break;
    }
}

// Gera o código para uma EXPRESSÃO (algo que resulta em um valor)
void generate_expression(ASTNode *node) {
    if (!node) return;
    switch(node->type) {
        case AST_NUMBER:         if(node->value.floatVal == (int)node->value.floatVal) printf("%d", (int)node->value.floatVal); else printf("%f", node->value.floatVal); break;
        case AST_STRING:         printf("%s", node->value.strVal); break;
        case AST_IDENTIFIER:     printf("%s", node->value.strVal); break;
        case AST_TYPE_SPECIFIER: printf("%s", node->value.strVal); break;
        case AST_INPUT:          printf("runtime_input_c()"); break;
        
        case AST_MEMBER_ACCESS:  generate_expression(node->left); printf(".%s", node->right->value.strVal); break;
        case AST_MATRIX_ACCESS:  printf("%s[", node->value.strVal); generate_expression(node->left); printf("]["); generate_expression(node->right); printf("]"); break;
        case AST_FUNC_CALL:      printf("%s(", node->left->value.strVal); if(node->right) generate_expression(node->right); printf(")"); break;
        
        case AST_ARG_LIST:       generate_expression(node->left); printf(", "); generate_expression(node->right); break;
        case AST_PARAM_LIST:     generate_expression(node->left); printf(", "); generate_expression(node->right); break;
        case AST_PARAM:          generate_expression(node->left); printf(" %s", node->right->value.strVal); break;
        
        case AST_ADD:            printf("("); generate_expression(node->left); printf(" + "); generate_expression(node->right); printf(")"); break;
        case AST_SUB:            printf("("); generate_expression(node->left); printf(" - "); generate_expression(node->right); printf(")"); break;
        case AST_MUL:            printf("("); generate_expression(node->left); printf(" * "); generate_expression(node->right); printf(")"); break;
        case AST_DIV:            printf("("); generate_expression(node->left); printf(" / "); generate_expression(node->right); printf(")"); break;
        case AST_POW:            printf("pow("); generate_expression(node->left); printf(", "); generate_expression(node->right); printf(")"); break;
        case AST_AND:            printf("("); generate_expression(node->left); printf(" && "); generate_expression(node->right); printf(")"); break;
        case AST_OR:             printf("("); generate_expression(node->left); printf(" || "); generate_expression(node->right); printf(")"); break;
        case AST_EQ:             printf("("); generate_expression(node->left); printf(" == "); generate_expression(node->right); printf(")"); break;
        case AST_NEQ:            printf("("); generate_expression(node->left); printf(" != "); generate_expression(node->right); printf(")"); break;
        case AST_GT:             printf("("); generate_expression(node->left); printf(" > "); generate_expression(node->right); printf(")"); break;
        case AST_LT:             printf("("); generate_expression(node->left); printf(" < "); generate_expression(node->right); printf(")"); break;
        case AST_GTE:            printf("("); generate_expression(node->left); printf(" >= "); generate_expression(node->right); printf(")"); break;
        case AST_LTE:            printf("("); generate_expression(node->left); printf(" <= "); generate_expression(node->right); printf(")"); break;
        case AST_UMINUS:         printf("-("); generate_expression(node->left); printf(")"); break;
        case AST_NOT:            printf("!("); generate_expression(node->left); printf(")"); break;
        
        default:                 fprintf(stderr, "\nCodeGen Erro: Expressao de tipo %d nao implementada.\n", node->type); break;
    }
}