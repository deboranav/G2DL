#include "codegen.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Estrutura para rastrear variáveis já declaradas ---
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
}

static void generate_code_recursive(ASTNode* node, int indent_level);

// Função principal que inicia a geração de código
void generate_code(ASTNode* root) {
    if (!root) return;

    // Cabeçalhos C padrão
    printf("#include <stdio.h>\n");
    printf("#include <stdlib.h>\n");
    printf("#include <string.h>\n");
    printf("#include <math.h>\n\n");
    printf("double runtime_input_c() { char b[256]; if(fgets(b,256,stdin)){return atof(b);} return 0.0; }\n\n");
    
    printf("int main() {\n");
    
    // Inicia a geração recursiva a partir da raiz
    generate_code_recursive(root, 1); // Nível 1 de indentação
    
    printf("\n    return 0;\n}\n");

    free_declared_vars();
}

// Função recursiva que percorre a árvore
void generate_code_recursive(ASTNode* node, int indent_level) {
    if (!node) return;

    // Helper para indentação
    char indent[100];
    for(int i = 0; i < indent_level * 4; ++i) indent[i] = ' ';
    indent[indent_level * 4] = '\0';

    switch (node->type) {
        case AST_STATEMENT_LIST:
            generate_code_recursive(node->left, indent_level);
            generate_code_recursive(node->right, indent_level);
            break;

        case AST_NUMBER:
            printf("%f", node->value.floatVal);
            break;

        case AST_IDENTIFIER:
            printf("%s", node->value.strVal);
            break;

        case AST_ADD:
            printf("(");
            generate_code_recursive(node->left, 0);
            printf(" + ");
            generate_code_recursive(node->right, 0);
            printf(")");
            break;

        case AST_ASSIGN: {
            char* var_name = node->left->value.strVal;
            printf("%s", indent);

            if (!is_var_declared(var_name)) {
                printf("double ");
                add_declared_var(var_name);
            }
            
            generate_code_recursive(node->left, 0);
            printf(" = ");
            generate_code_recursive(node->right, 0);
            printf(";\n");
            break;
        }

        case AST_IF:
            printf("%sif (", indent);
            generate_code_recursive(node->left, 0); // Condição
            printf(") {\n");
            generate_code_recursive(node->right, indent_level + 1); // Corpo do IF
            printf("%s}\n", indent);
            if (node->aux) { // Existe um ELSE
                printf("%selse {\n", indent);
                generate_code_recursive(node->aux, indent_level + 1);
                printf("%s}\n", indent);
            }
            break;

        case AST_INPUT:
            printf("runtime_input_c()");
            break;
        
        case AST_PRINTF:
            printf("%s", indent);
            printf("printf(");
            generate_code_recursive(node->left, 0); // O formato da string
            if (node->right) {
                printf(", ");
                generate_code_recursive(node->right, 0); // A lista de argumentos
            }
            printf(");\n");
            break;
        
        case AST_SUB:
            printf("(");
            generate_code_recursive(node->left, 0);
            printf(" - ");
            generate_code_recursive(node->right, 0);
            printf(")");
            break;

        case AST_MUL:
            printf("(");
            generate_code_recursive(node->left, 0);
            printf(" * ");
            generate_code_recursive(node->right, 0);
            printf(")");
            break;
        
        case AST_DIV:
            printf("(");
            generate_code_recursive(node->left, 0);
            printf(" / ");
            generate_code_recursive(node->right, 0);
            printf(")");
            break;

        case AST_POW:
            printf("pow(");
            generate_code_recursive(node->left, 0);
            printf(", ");
            generate_code_recursive(node->right, 0);
            printf(")");
            break;
        
        case AST_STRING:
            printf("%s", node->value.strVal);
            break;
        
        default:
            fprintf(stderr, "Aviso: Gerador de codigo nao implementado para o no tipo %d\n", node->type);
            break;
        
    }
}