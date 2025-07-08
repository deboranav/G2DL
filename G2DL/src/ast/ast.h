// ast.h - Define a ESTRUTURA do código antes da execução.
#ifndef AST_H
#define AST_H

#include "utils/types.h" // Caminho a partir de 'src/' // A AST pode precisar conhecer os tipos de valores para nós literais e RuntimeValue

// --- Definição dos Tipos de Nós ---
// Estes enums representam os diferentes tipos de operações ou estruturas
// que um nó na sua Árvore de Sintaxe Abstrata pode representar.
typedef enum {
    // Literais
    NODE_TYPE_INT_LITERAL,      // Inteiro literal (ex: 10, 0, -5)
    NODE_TYPE_FLOAT_LITERAL,    // Float literal (ex: 3.14, 0.5)
    NODE_TYPE_STRING_LITERAL,   // String literal (ex: "hello", 'world')

    // Variáveis e Atribuições
    NODE_TYPE_IDENTIFIER,       // Acesso a um identificador/variável (ex: x, myVar)
    NODE_TYPE_ASSIGNMENT,       // Atribuição de valor (ex: x = 10, y += 5)
    NODE_TYPE_ARRAY_ACCESS,     // Acesso a um elemento de array (ex: arr[0])
    NODE_TYPE_ARRAY_LITERAL,    // Criação de um array literal (ex: [1, 2, 3])
    NODE_TYPE_ARRAY_ASSIGNMENT, // Atribuição a um elemento de array (ex: arr[0] = 5)

    // Operações
    NODE_TYPE_BINARY_OP,        // Operações binárias (ex: a + b, x == y, 5 < 10)
    NODE_TYPE_UNARY_OP,         // Operações unárias (ex: !true, -5)
    NODE_TYPE_INPUT,            // Chamada da função INPUT()

    // Estruturas de Controle
    NODE_TYPE_BLOCK,            // Um bloco de código ({ ... })
    NODE_TYPE_IF_STATEMENT,     // Declaração IF (com ou sem ELSE)
    NODE_TYPE_WHILE_LOOP,       // Loop WHILE
    NODE_TYPE_FOR_LOOP,         // Loop FOR

    // Funções
    NODE_TYPE_FUNCTION_DECL,    // Declaração de função (function myFunc(...) { ... })
    NODE_TYPE_FUNCTION_CALL,    // Chamada de função (myFunc(arg1, arg2))
    NODE_TYPE_RETURN_STATEMENT, // Declaração RETURN

    // Print
    NODE_TYPE_PRINTF_STATEMENT, // Chamada de PRINTF com formato e argumentos
    NODE_TYPE_PRINTF_ID,        // Chamada de PRINTF com ID (ex: printf(myVar))

    // Controle de Fluxo
    NODE_TYPE_BREAK_STATEMENT,  // Declaração BREAK

    // Statement que é apenas uma expressão (ex: `a + b;` sem atribuição)
    NODE_TYPE_EXPRESSION_STATEMENT,

    // Nós para listar statements ou expressões dentro de outros nós (como BlockNode ou ArrayLiteralNode)
    NODE_TYPE_NODE_LIST,

} AstNodeType;

// --- Estrutura Base para Todos os Nós da AST ---
// Todos os nós da AST começarão com esses campos comuns.
// Isso permite que tratemos qualquer nó como um 'AstNode*' genericamente.
typedef struct AstNode {
    AstNodeType type;    // O tipo específico deste nó (um dos enums acima)
    int line_number;     // Número da linha no código fonte para depuração/erros
} AstNode;

// --- Estruturas Concretas para Diferentes Tipos de Nós ---

// Nó para literais inteiros
typedef struct IntLiteralNode {
    AstNode base; // Herda campos base (type, line_number)
    int value;
} IntLiteralNode;

// Nó para literais float
typedef struct FloatLiteralNode {
    AstNode base; // Herda campos base
    float value;
} FloatLiteralNode;

// Nó para literais string
typedef struct StringLiteralNode {
    AstNode base; // Herda campos base
    char *value;  // A string, deve ser duplicada (strdup)
} StringLiteralNode;

// Nó para acesso a variáveis (identificadores)
typedef struct IdentifierNode {
    AstNode base; // Herda campos base
    char *name;   // O nome da variável, deve ser duplicado
} IdentifierNode;

// Nó para atribuições (ex: x = 10, y += 5)
typedef struct AssignmentNode {
    AstNode base; // Herda campos base
    AstNode *target;     // O nó que está sendo atribuído (IdentifierNode, ArrayAccessNode)
    OperatorType op_type; // Tipo de operador de atribuição (ASSIGNMENT, PLUS_ASSIGNMENT, etc.)
    AstNode *expression; // O valor ou expressão a ser atribuída
} AssignmentNode;

// Nó para operações binárias (ex: a + b, x == y)
typedef struct BinaryOpNode {
    AstNode base; // Herda campos base
    AstNode *left;
    OperatorType op_type; // Tipo de operador (PLUS, MINUS, EQUAL, etc.)
    AstNode *right;
} BinaryOpNode;

// Nó para operações unárias (ex: !true, -x)
typedef struct UnaryOpNode {
    AstNode base; // Herda campos base
    OperatorType op_type; // Tipo de operador (NOT)
    AstNode *operand;
} UnaryOpNode;

// Nó para um bloco de código (lista de statements)
// Usamos uma lista genérica para os statements dentro do bloco.
typedef struct BlockNode {
    AstNode base; // Herda campos base
    struct AstNodeList *statements; // Lista de AstNodes (statements)
} BlockNode;

// Nó para um loop while
typedef struct WhileNode {
    AstNode base; // Herda campos base
    AstNode *condition; // Expressão que define a condição do loop
    AstNode *body;      // Corpo do loop (geralmente um BlockNode ou outro statement)
} WhileNode;

// Nó para um loop for
typedef struct ForNode {
    AstNode base; // Herda campos base
    AstNode *initializer; // Statement de inicialização (ex: i = 0;)
    AstNode *condition;   // Expressão de condição (ex: i < 10)
    AstNode *increment;   // Statement de incremento (ex: i += 1;)
    AstNode *body;        // Corpo do loop (BlockNode ou outro statement)
} ForNode;

// Nó para a estrutura condicional IF
typedef struct IfStatementNode {
    AstNode base; // Herda campos base
    AstNode *condition; // Expressão que define a condição
    AstNode *then_branch; // Bloco de código para o IF (true)
    AstNode *else_branch; // Bloco de código para o ELSE (false), pode ser NULL
} IfStatementNode;

// Nó para o statement RETURN
typedef struct ReturnStatementNode {
    AstNode base; // Herda campos base
    AstNode *expression; // A expressão cujo valor será retornado
} ReturnStatementNode;

// Nó para o statement BREAK
typedef struct BreakStatementNode {
    AstNode base; // Herda campos base
    // Não tem campos adicionais, apenas o tipo
} BreakStatementNode;

// Nó para chamada da função PRINTF
typedef struct PrintfNode {
    AstNode base; // Herda campos base
    char *format_string; // A string de formato literal (ex: "%d %s\n")
    struct ArgumentNode *args; // Lista de argumentos, cada um é um AstNode*
} PrintfNode;

// Nó para printf(ID)
typedef struct PrintfIdNode {
    AstNode base; // Herda campos base
    char *id_name; // Nome do ID (variável) para imprimir
} PrintfIdNode;

// Nó para a chamada INPUT()
typedef struct InputNode {
    AstNode base; // Herda campos base
    // Não tem campos adicionais, apenas o tipo
} InputNode;

// Nó para um statement que é apenas uma expressão (ex: `a + b;`)
typedef struct ExpressionStatementNode {
    AstNode base; // Herda campos base
    AstNode *expression; // A expressão
} ExpressionStatementNode;

// Nó para literais de array (ex: [1, "hello", 3.14])
typedef struct ArrayLiteralNode {
    AstNode base; // Herda campos base
    struct AstNodeList *elements; // Lista de AstNodes (expressões que são os elementos do array)
} ArrayLiteralNode;

// Nó para acesso a elementos de array (ex: myArr[index])
typedef struct ArrayAccessNode {
    AstNode base; // Herda campos base
    AstNode *array_name;   // O identificador do array (IdentifierNode)
    AstNode *index_expression; // A expressão que avalia para o índice
} ArrayAccessNode;

// Nó para declaração de função
typedef struct FunctionDeclarationNode {
    AstNode base;
    char *name; // Nome da função
    // TODO: Adicionar lista de parâmetros
    AstNode *body; // Corpo da função (BlockNode)
} FunctionDeclarationNode;

// Nó para chamada de função
typedef struct FunctionCallNode {
    AstNode base;
    char *name; // Nome da função a ser chamada
    struct ArgumentNode *args; // Lista de argumentos passados, cada um é um AstNode*
} FunctionCallNode;


// --- Estruturas Auxiliares ---

// Lista genérica de nós da AST (usada em BlockNode, ArrayLiteralNode, etc.)
typedef struct AstNodeList {
    AstNode **nodes; // Array de ponteiros para AstNode
    int count;       // Número atual de nós na lista
    int capacity;    // Capacidade alocada do array
} AstNodeList;

// Nó para argumentos de chamadas de função ou printf (dentro da AST)
// Este nó serve como um elemento de uma lista encadeada para argumentos.
typedef struct ArgumentNode {
    AstNode *node;              // O nó da AST que representa a expressão do argumento
    struct ArgumentNode *next;  // Próximo argumento na lista
} ArgumentNode;


// --- Declarações das Funções Construtoras da AST ---
// Essas funções alocam memória para os nós e os inicializam.

AstNode* create_int_literal_node(int value);
AstNode* create_float_literal_node(float value);
AstNode* create_string_literal_node(char *value);
AstNode* create_identifier_node(char *name);
AstNode* create_assignment_node(AstNode *target, OperatorType op_type, AstNode *expression);
AstNode* create_binary_op_node(AstNode *left, OperatorType op_type, AstNode *right);
AstNode* create_unary_op_node(OperatorType op_type, AstNode *operand);
AstNode* create_block_node(AstNodeList *statements);
AstNode* create_while_node(AstNode* condition, AstNode* body);
AstNode* create_for_node(AstNode *initializer, AstNode *condition, AstNode *increment, AstNode *body);
AstNode* create_if_statement_node(AstNode *condition, AstNode *then_branch, AstNode *else_branch);
AstNode* create_return_statement_node(AstNode *expression);
AstNode* create_break_statement_node();
AstNode* create_printf_node(char *format_string, ArgumentNode *args);
AstNode* create_printf_id_node(char *id_name);
AstNode* create_input_node();
AstNode* create_expression_statement_node(AstNode *expression);
AstNode* create_array_literal_node(AstNodeList *elements);
AstNode* create_array_access_node(AstNode *array_name, AstNode *index_expression);
AstNode* create_array_assignment_node(AstNode *array_access_node, AstNode *expression);
AstNode* create_function_declaration_node(char *name, AstNode *body); // TODO: Adicionar parâmetros
AstNode* create_function_call_node(char *name, ArgumentNode *args);


// --- Funções para manipulação de AstNodeList e ArgumentNode ---
AstNodeList* create_ast_node_list_from_node(AstNode *node);
AstNodeList* append_to_ast_node_list(AstNodeList *list, AstNode *node);
ArgumentNode* create_argument_node(AstNode *arg_ast_node);
void free_argument_list(ArgumentNode *list); // Para liberar ArgumentNodes

// --- Função para Liberação de Memória da AST ---
// Crucial para evitar vazamentos de memória após a execução.
void free_ast(AstNode *node);

#endif // AST_H