#include "codegen.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h" // Incluído para ter acesso à enumeração NodeType

// --- Estrutura para rastrear variáveis escalares já declaradas em C ---
typedef struct DeclaredVar {
    char* name;
    struct DeclaredVar* next;
} DeclaredVar;

static DeclaredVar* declared_vars_head = NULL;

// Verifica se uma variável já foi adicionada à nossa lista
static int is_var_declared(const char* name) {
    DeclaredVar* current = declared_vars_head;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

// Adiciona uma variável à nossa lista
static void add_declared_var(const char* name) {
    DeclaredVar* new_var = (DeclaredVar*) malloc(sizeof(DeclaredVar));
    new_var->name = strdup(name);
    new_var->next = declared_vars_head;
    declared_vars_head = new_var;
}

// Libera a memória usada pela lista
static void free_declared_vars() {
    DeclaredVar* current = declared_vars_head;
    while (current != NULL) {
        DeclaredVar* temp = current;
        current = current->next;
        free(temp->name);
        free(temp);
    }
    declared_vars_head = NULL; // Reseta a lista
}
// --- Fim da estrutura de rastreamento ---


static void generate_code_recursive(ASTNode* node, int indent_level);

void generate_code(ASTNode* root) {
    if (!root) return;

    printf("#include <stdio.h>\n");
    printf("#include <stdlib.h>\n");
    printf("#include <string.h>\n");
    printf("#include <math.h>\n\n");
    printf("double runtime_input_c() { char b[256]; if(fgets(b,256,stdin)){return atof(b);} return 0.0; }\n\n");
    
    printf("int main() {\n");
    
    generate_code_recursive(root, 1);
    
    printf("\n    return 0;\n}\n");

    free_declared_vars(); // Limpa a lista no final de cada geração
}

void generate_code_recursive(ASTNode* node, int indent_level) {
    if (!node) return;

    char indent[100];
    for(int i = 0; i < indent_level * 4; ++i) indent[i] = ' ';
    indent[indent_level * 4] = '\0';

    switch (node->type) {
        case AST_STATEMENT_LIST:
            generate_code_recursive(node->left, indent_level);
            generate_code_recursive(node->right, indent_level);
            break;
            
        case AST_ARG_LIST:
            generate_code_recursive(node->left, 0);
            printf(", ");
            generate_code_recursive(node->right, 0);
            break;

        case AST_MATRIX_DECL:
            printf("%sdouble %s[", indent, node->value.strVal);
            generate_code_recursive(node->left, 0);
            printf("][");
            generate_code_recursive(node->right, 0);
            printf("];\n");
            break;

        case AST_MATRIX_ACCESS:
            printf("%s[", node->value.strVal);
            generate_code_recursive(node->left, 0);
            printf("][");
            generate_code_recursive(node->right, 0);
            printf("]");
            break;

        case AST_ASSIGN: {
            printf("%s", indent);
            
            // Lida com a declaração de variável escalar (não-matriz) na primeira vez
            if (node->left->type == AST_IDENTIFIER) {
                if (!is_var_declared(node->left->value.strVal)) {
                    printf("double ");
                    add_declared_var(node->left->value.strVal);
                }
            }
            
            generate_code_recursive(node->left, 0);
            printf(" = ");
            generate_code_recursive(node->right, 0);
            printf(";\n");
            break;
        }

        case AST_NUMBER:
            if (node->value.floatVal == (int)node->value.floatVal) {
                printf("%d", (int)node->value.floatVal);
            } else {
                printf("%f", node->value.floatVal);
            }
            break;
            
        case AST_PRINTF:
            printf("%s", indent);
            printf("printf(");
            generate_code_recursive(node->left, 0);
            if (node->right) {
                printf(", ");
                generate_code_recursive(node->right, 0);
            }
            printf(");\n");
            break;
        
        case AST_STRING: 
            printf("%s", node->value.strVal); 
            break;

        case AST_IDENTIFIER: 
            printf("%s", node->value.strVal); 
            break;

        case AST_INPUT: 
            printf("runtime_input_c()"); 
            break;
        
        case AST_IF:
            printf("%sif (", indent);
            generate_code_recursive(node->left, 0);
            printf(") {\n");
            generate_code_recursive(node->right, indent_level + 1);
            printf("\n%s}", indent);
            if (node->aux) {
                if (node->aux->type == AST_IF) {
                    printf(" else ");
                    generate_code_recursive(node->aux, indent_level);
                } else {
                    printf(" else {\n");
                    generate_code_recursive(node->aux, indent_level + 1);
                    printf("\n%s}", indent);
                }
            }
            printf("\n");
            break;

        case AST_WHILE:
            printf("%swhile (", indent);
            generate_code_recursive(node->left, 0);
            printf(") {\n");
            generate_code_recursive(node->right, indent_level + 1);
            printf("\n%s}\n", indent);
            break;

        // --- OPERADORES ---
        case AST_ADD: printf("("); generate_code_recursive(node->left, 0); printf(" + "); generate_code_recursive(node->right, 0); printf(")"); break;
        case AST_SUB: printf("("); generate_code_recursive(node->left, 0); printf(" - "); generate_code_recursive(node->right, 0); printf(")"); break;
        case AST_MUL: printf("("); generate_code_recursive(node->left, 0); printf(" * "); generate_code_recursive(node->right, 0); printf(")"); break;
        case AST_DIV: printf("("); generate_code_recursive(node->left, 0); printf(" / "); generate_code_recursive(node->right, 0); printf(")"); break;
        case AST_POW: printf("pow("); generate_code_recursive(node->left, 0); printf(", "); generate_code_recursive(node->right, 0); printf(")"); break;
        case AST_AND: printf("("); generate_code_recursive(node->left, 0); printf(" && "); generate_code_recursive(node->right, 0); printf(")"); break;
        case AST_OR:  printf("("); generate_code_recursive(node->left, 0); printf(" || "); generate_code_recursive(node->right, 0); printf(")"); break;
        case AST_EQ:  printf("("); generate_code_recursive(node->left, 0); printf(" == "); generate_code_recursive(node->right, 0); printf(")"); break;
        case AST_NEQ: printf("("); generate_code_recursive(node->left, 0); printf(" != "); generate_code_recursive(node->right, 0); printf(")"); break;
        case AST_GT:  printf("("); generate_code_recursive(node->left, 0); printf(" > "); generate_code_recursive(node->right, 0); printf(")"); break;
        case AST_LT:  printf("("); generate_code_recursive(node->left, 0); printf(" < "); generate_code_recursive(node->right, 0); printf(")"); break;
        case AST_GTE: printf("("); generate_code_recursive(node->left, 0); printf(" >= "); generate_code_recursive(node->right, 0); printf(")"); break;
        case AST_LTE: printf("("); generate_code_recursive(node->left, 0); printf(" <= "); generate_code_recursive(node->right, 0); printf(")"); break;

        default:
            fprintf(stderr, "Aviso: Gerador de codigo nao implementado para o no tipo %d\n", node->type);
            break;
    }
}