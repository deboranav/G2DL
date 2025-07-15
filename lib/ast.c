#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbol_table.h"
#include "types.h"
#include "ast.h"

extern int yylineno;

// Função genérica para criar um nó
ASTNode* new_ast_node(NodeType type, ASTNode* left, ASTNode* right) {
    ASTNode* node = (ASTNode*) malloc(sizeof(ASTNode));
    if (!node) {
        fprintf(stderr, "Falha ao alocar memória para o nó da AST\n");
        exit(1);
    }
    node->type = type;
    node->left = left;
    node->right = right;
    node->aux = NULL; // Inicializa o ponteiro auxiliar
    node->value.strVal = NULL;
    return node;
}

// Função para criar um nó "folha" para um número
ASTNode* new_ast_leaf_number(double value) {
    ASTNode* node = new_ast_node(AST_NUMBER, NULL, NULL);
    node->value.floatVal = value;
    return node;
}

// Função para criar um nó "folha" para um identificador/variável
ASTNode* new_ast_leaf_id(char* name) {
    ASTNode* node = new_ast_node(AST_IDENTIFIER, NULL, NULL);
    node->value.strVal = name; // strdup(name) é mais seguro se a string original for liberada
    return node;
}

// Função para criar um nó "folha" para uma string literal
ASTNode* new_ast_leaf_string(char* str) {
    ASTNode* node = new_ast_node(AST_STRING, NULL, NULL);
    // Baseado na sua alteração, str já inclui as aspas.
    // Para gerar código C, talvez precisemos processá-lo depois.
    node->value.strVal = str; 
    return node;
}

ASTNode* new_ast_if_node(ASTNode* condition, ASTNode* if_body, ASTNode* else_body) {
    ASTNode* node = new_ast_node(AST_IF, condition, if_body);
    node->aux = else_body;
    return node;
}

ASTNode* new_ast_matrix_decl_node(char* name, ASTNode* rows, ASTNode* cols) { // <<< ADICIONADO
    ASTNode* node = new_ast_node(AST_MATRIX_DECL, rows, cols);
    node->value.strVal = strdup(name);
    return node;
}

ASTNode* new_ast_matrix_access_node(char* name, ASTNode* row_idx, ASTNode* col_idx) { // <<< ADICIONADO
    ASTNode* node = new_ast_node(AST_MATRIX_ACCESS, row_idx, col_idx);
    node->value.strVal = strdup(name);
    return node;
}

// Função recursiva para liberar a memória da árvore
void free_ast(ASTNode* node) {
    if (!node) return;
    free_ast(node->left);
    free_ast(node->right);
    free_ast(node->aux);

    if (node->type == AST_IDENTIFIER || node->type == AST_STRING || 
        node->type == AST_MATRIX_DECL || node->type == AST_MATRIX_ACCESS) {
        free(node->value.strVal);
    }
    free(node);
}

// Esta função auxiliar converte um NodeType em uma string legível
const char* nodetype_to_string(NodeType type) {
    switch (type) {
        case AST_NUMBER: return "NUMBER";
        case AST_STRING: return "STRING";
        case AST_IDENTIFIER: return "IDENTIFIER";
        case AST_MATRIX_DECL: return "MATRIX_DECL";
        case AST_MATRIX_ACCESS: return "MATRIX_ACCESS";
        case AST_ADD: return "ADD";
        case AST_SUB: return "SUB";
        case AST_MUL: return "MUL";
        case AST_DIV: return "DIV";
        case AST_EQ: return "EQ";
        case AST_NEQ: return "NEQ";
        case AST_LT: return "LT";
        case AST_GT: return "GT";
        case AST_LTE: return "LTE";
        case AST_GTE: return "GTE";
        case AST_AND: return "AND";
        case AST_OR: return "OR";
        case AST_POW: return "POW";
        case AST_UMINUS: return "UMINUS";
        case AST_NOT: return "NOT";
        case AST_ASSIGN: return "ASSIGN";
        case AST_IF: return "IF";
        case AST_WHILE: return "WHILE";
        case AST_PRINTF: return "PRINTF";
        case AST_INPUT: return "INPUT";
        case AST_FUNC_CALL: return "FUNC_CALL";
        case AST_ARG_LIST: return "ARG_LIST";
        case AST_STATEMENT_LIST: return "STATEMENT_LIST";
        default: return "UNKNOWN_NODE";
    }
}

// Função recursiva que imprime a árvore com indentação
void print_ast_recursive(ASTNode* node, int indent) {
    if (node == NULL) {
        return;
    }

    // Imprime a indentação
    for (int i = 0; i < indent; ++i) {
        printf("  ");
    }

    // Imprime o tipo do nó
    printf("- %s", nodetype_to_string(node->type));

    // Imprime o valor do nó, se for uma folha
    if (node->type == AST_NUMBER) {
        printf(": %f\n", node->value.floatVal);
    } else if (node->type == AST_IDENTIFIER || node->type == AST_STRING || 
               node->type == AST_MATRIX_DECL || node->type == AST_MATRIX_ACCESS) {
        printf(": %s\n", node->value.strVal);
    } else {
        printf("\n");
    }

    // Chama recursivamente para os filhos
    print_ast_recursive(node->left, indent + 1);
    print_ast_recursive(node->right, indent + 1);
    print_ast_recursive(node->aux, indent + 1);
}

// Função principal que inicia a impressão da AST
void print_ast(ASTNode* root) {
    printf("\n\n--- INICIO DA ARVORE SINTATICA (AST) ---\n");
    print_ast_recursive(root, 0);
    printf("--- FIM DA ARVORE SINTATICA (AST) ---\n\n");
}

// Função auxiliar para inferir o tipo de uma expressão
static DataType infer_type_from_expression(ASTNode* expr_node) {
    if (!expr_node) return TYPE_VOID; // Expressão vazia

    // Expanda isso conforme sua linguagem cresce
    switch(expr_node->type) {
        case AST_NUMBER:
            return TYPE_FLOAT; // Todos os números são float/double por padrão
        case AST_STRING:
            return TYPE_STRING;
        case AST_INPUT:
            return TYPE_FLOAT; // A função input() retorna um número
        case AST_IDENTIFIER: {
            // O tipo é o tipo da variável na tabela de símbolos
            Symbol* symbol = scope_lookup(expr_node->value.strVal);
            if (symbol) {
                return symbol->type;
            }
            // Erro será pego no 'semantic_traverse'
            return TYPE_VOID;
        }
        case AST_MATRIX_ACCESS: return TYPE_FLOAT;
        case AST_ADD:
        case AST_SUB:
        case AST_MUL:
        case AST_DIV:
        case AST_POW:
            return TYPE_FLOAT; 
        default:
            return TYPE_VOID; // Tipo desconhecido ou não aplicável
    }
}


// Função principal que percorre a árvore recursivamente
static void semantic_traverse(ASTNode* node) {
    if (!node) return;

    // Ações pré-ordem (acontecem antes de visitar os filhos)
    switch (node->type) {
        case AST_MATRIX_DECL: {
            char* name = node->value.strVal;
            
            // 1. Verifica se o símbolo já existe no escopo atual
            if (scope_lookup_current(name)) {
                fprintf(stderr, "Erro semantico na linha %d: Redeclaracao da matriz '%s'.\n", yylineno, name);
            } else {
                // 2. Extrai as dimensões. Assume que são literais numéricos por enquanto.
                ASTNode* rows_node = node->left;
                ASTNode* cols_node = node->right;

                if (rows_node->type != AST_NUMBER || cols_node->type != AST_NUMBER) {
                    fprintf(stderr, "Erro semantico na linha %d: Dimensoes da matriz '%s' devem ser numeros inteiros literais.\n", yylineno, name);
                } else {
                    int rows = (int)rows_node->value.floatVal;
                    int cols = (int)cols_node->value.floatVal;
                    
                    // 3. Adiciona o símbolo à tabela
                    scope_add_symbol(name, TYPE_MATRIX, NULL, rows, cols);
                }
            }
            // Não precisa descer recursivamente, pois já tratamos os filhos
            return;
        }

        case AST_MATRIX_ACCESS: {
            char* name = node->value.strVal;
            Symbol* symbol = scope_lookup(name);

            // 1. Verifica se a variável existe
            if (!symbol) {
                fprintf(stderr, "Erro semantico na linha %d: Matriz '%s' nao foi declarada.\n", yylineno, name);
            } 
            // 2. Verifica se é do tipo matriz
            else if (symbol->type != TYPE_MATRIX) {
                fprintf(stderr, "Erro semantico na linha %d: Variavel '%s' nao e uma matriz.\n", yylineno, name);
            }
            
            // Analisa as expressões de índice
            semantic_traverse(node->left);
            semantic_traverse(node->right);
            return;
        }

        case AST_ASSIGN: {
            ASTNode* lhs = node->left;
            ASTNode* rhs = node->right;
            semantic_traverse(rhs);
            DataType rhs_type = infer_type_from_expression(rhs);
            
            if (lhs->type == AST_IDENTIFIER) {
                Symbol* symbol = scope_lookup(lhs->value.strVal);
                if (!symbol) {
                    scope_add_symbol(lhs->value.strVal, rhs_type, NULL, 0, 0);
                } else if (symbol->type != rhs_type && rhs_type != TYPE_VOID) {
                    fprintf(stderr, "Aviso na linha %d: Atribuindo tipo incompátivel para a variavel '%s'.\n", yylineno, lhs->value.strVal);
                }
            } else if (lhs->type == AST_MATRIX_ACCESS) {
                semantic_traverse(lhs); // Analisa o acesso à matriz
                if (rhs_type != TYPE_FLOAT && rhs_type != TYPE_VOID) {
                    fprintf(stderr, "Aviso na linha %d: Elementos de matriz devem receber valores numericos.\n", yylineno);
                }
            }
            return;
        }

        case AST_IDENTIFIER: {
            // USO DE VARIÁVEL: Verifica se a variável foi declarada.
            if (scope_lookup(node->value.strVal) == NULL) {
                fprintf(stderr, "Erro semantico: Variavel '%s' usada antes de ser declarada.\n", node->value.strVal);
            }
            return; // Folha, não tem filhos para visitar
        }
    }

    // Travessia normal para os outros nós
    semantic_traverse(node->left);
    semantic_traverse(node->right);
    semantic_traverse(node->aux);
}

// Função pública que inicia o processo
void analyze_semantics(ASTNode* root) {
    if (!root) return;
    semantic_traverse(root);
}