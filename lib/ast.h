#ifndef AST_H
#define AST_H

// Enum para todos os tipos de nós possíveis na árvore
typedef enum {
    // Nós Literais e Variáveis
    AST_NUMBER,
    AST_STRING,
    AST_IDENTIFIER,

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
    
    // Nó para sequências de comandos
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
    // Uma abordagem mais robusta usaria uma lista ligada de filhos.
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
void free_ast(ASTNode* node);

#endif // AST_H