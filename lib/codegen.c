#include "codegen.h"
#include <stdio.h>

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

        case AST_ASSIGN:
            printf("%s", indent);
            // Aqui, você pode checar se a variável já foi declarada no C
            // Por enquanto, vamos assumir a declaração implícita que fizemos
            generate_code_recursive(node->left, 0);
            printf(" = ");
            generate_code_recursive(node->right, 0);
            printf(";\n");
            break;

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
            
        // ... Implementar casos para TODOS os outros tipos de nós ...
    }
}