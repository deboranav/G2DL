#ifndef AST_H
#define AST_H

// Enum para todos os tipos de nós possíveis na árvore
typedef enum {
    // Nós Literais e Variáveis
    AST_NUMBER,
    AST_STRING,
    AST_IDENTIFIER,
    AST_TYPE_SPECIFIER,

    // Nós de Declaração
    AST_VAR_DECL,        // Para 'rational_t r1;'
    AST_MATRIX_DECL,
    AST_TYPE_DEF,        // Para 'type rational_t { ... }'
    AST_FUNC_DEF,        // Para 'function ...'
    AST_PARAM_LIST,      // Lista de parâmetros
    AST_PARAM,           // Um único parâmetro

    // Nós de Acesso
    AST_MATRIX_ACCESS,
    AST_MEMBER_ACCESS,   // Para 'r1.numerador'

    // Nós de Operações Binárias (ex: a + b)
    AST_ADD,
    AST_SUB,
    AST_MUL,
    AST_DIV,
    AST_EQ,  // ==
    AST_NEQ, // !=
    AST_LT,  // <
    AST_GT,  // >
    AST_LTE, // <=
    AST_GTE, // >=
    AST_AND,
    AST_OR,
    AST_POW, // Exponenciação

    // Nós de Operações Unárias (ex: -a)
    AST_UMINUS, // Negativo unário
    AST_NOT,
    

    // Nós de Comandos
    AST_ASSIGN,
    AST_IF,
    AST_WHILE,
    AST_PRINTF,
    AST_INPUT,
    AST_FUNC_CALL,
    AST_RETURN,
    
    // Nó para sequências de comandos
    AST_ARG_LIST,
    AST_STATEMENT_LIST

} NodeType;

// A estrutura principal de um nó da AST
typedef struct ASTNode {
    NodeType type;
    
    // Usamos uma união para armazenar valores, dependendo do tipo do nó
    union {
        double floatVal;
        char* strVal;
    } value;

    // Filhos do nó. Para simplicidade, usaremos 2 para operações e 3 para if.
    struct ASTNode *left;
    struct ASTNode *right;
    struct ASTNode *aux; // Usado para o "else", ou corpo do while, etc.

} ASTNode;


// --- Funções para criar nós ---
ASTNode* new_ast_node(NodeType type, ASTNode* left, ASTNode* right);
ASTNode* new_ast_leaf_number(double value);
ASTNode* new_ast_leaf_id(char* name);
ASTNode* new_ast_leaf_string(char* str);
ASTNode* new_ast_if_node(ASTNode* condition, ASTNode* if_body, ASTNode* else_body);

// Novas funções para matrizes
ASTNode* new_ast_matrix_decl_node(char* name, ASTNode* rows, ASTNode* cols);
ASTNode* new_ast_matrix_access_node(char* name, ASTNode* row_idx, ASTNode* col_idx);

// Novas funções para tipos e funções
ASTNode* new_ast_leaf_type(char* type_name);
ASTNode* new_ast_var_decl_node(ASTNode* type_spec, ASTNode* var_name);
ASTNode* new_ast_type_def_node(ASTNode* type_name, ASTNode* members);
ASTNode* new_ast_func_def_node(ASTNode* return_type, ASTNode* func_name, ASTNode* params, ASTNode* body);
ASTNode* new_ast_param_node(ASTNode* type_spec, ASTNode* param_name);

// --- Funções de processamento da AST ---
void free_ast(ASTNode* node);
void analyze_semantics(ASTNode* node);
void print_ast(ASTNode* root);

#endif // AST_H