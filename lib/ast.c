#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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