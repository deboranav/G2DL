#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbol_table.h"
#include "types.h"
#include "ast.h"

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

// Função recursiva para liberar a memória da árvore
void free_ast(ASTNode* node) {
    if (!node) return;
    free_ast(node->left);
    free_ast(node->right);
    free_ast(node->aux);

    // Libera a string se ela existir (em nós ID ou STRING)
    if (node->type == AST_IDENTIFIER || node->type == AST_STRING) {
        free(node->value.strVal);
    }
    free(node);
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
        // Para expressões como (a + b), o tipo depende dos operandos.
        // Por simplicidade, vamos assumir float para operações aritméticas.
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
        case AST_ASSIGN: {
            ASTNode* var_node = node->left;
            ASTNode* expr_node = node->right;
            char* var_name = var_node->value.strVal;

            // Primeiro, analisa a expressão à direita para resolver os tipos dela
            semantic_traverse(expr_node);

            // Agora, lida com a variável
            Symbol* symbol = scope_lookup(var_name);
            if (!symbol) {
                // DECLARAÇÃO IMPLÍCITA: Variável não existe, vamos criá-la.
                DataType new_type = infer_type_from_expression(expr_node);
                if (new_type != TYPE_VOID) {
                    scope_add_symbol(var_name, new_type, NULL, 0, 0);
                } else {
                    fprintf(stderr, "Erro semantico: Nao foi possivel inferir o tipo para a variavel '%s'.\n", var_name);
                }
            } else {
                // REATRIBUIÇÃO: Variável já existe. Checar se os tipos são compatíveis.
                DataType expr_type = infer_type_from_expression(expr_node);
                if (symbol->type != expr_type && expr_type != TYPE_VOID) {
                    fprintf(stderr, "Aviso: Atribuindo tipo incompátivel para a variavel '%s'.\n", var_name);
                }
            }
            return; // Já visitamos o filho direito, não precisa descer mais
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