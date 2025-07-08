// types.h - Definições de tipos fundamentais para o interpretador e a AST.
#ifndef TYPES_H
#define TYPES_H

// --- Tipos de Valores em Tempo de Execução (RuntimeValue) ---
// Estes são os tipos de dados que as expressões e variáveis podem ter
// durante a execução do programa.
typedef enum {
    TYPE_INT,       // Tipo inteiro (ex: 1, 100)
    TYPE_FLOAT,     // Tipo ponto flutuante (ex: 3.14, 0.5)
    TYPE_STRING,    // Tipo string (ex: "hello world")
    TYPE_ARRAY,     // Tipo array (coleção de outros valores)
    TYPE_BOOLEAN,   // Tipo booleano (para resultados de comparações e lógicos, 0 ou 1)
    TYPE_VOID,      // Para indicar ausência de valor (ex: retorno de funções sem valor)
    TYPE_NULL,      // Para representar um valor nulo (se sua linguagem suportar)
    TYPE_RETURN_VALUE, // Um tipo especial para sinalizar que um valor é um retorno de função
    TYPE_BREAK_FLOW, // Um tipo especial para sinalizar um `break` no fluxo de controle
    // Adicione outros tipos conforme sua linguagem cresce (ex: FUNCTION_POINTER)
} ValueType;

// Estrutura para representar um valor em tempo de execução.
// A union permite que o mesmo espaço de memória seja usado para diferentes tipos
// de dados, economizando memória. O campo 'type' indica qual membro da union é válido.
typedef struct {
    ValueType type;      // O tipo do valor atualmente armazenado
    ValueType sub_type;  // Usado para TYPE_RETURN_VALUE para indicar o tipo do valor retornado
    union {
        int intVal;        // Para valores inteiros
        float floatVal;    // Para valores de ponto flutuante
        char *strVal;      // Para strings (ponteiro para string alocada dinamicamente)
        void *arrayVal;    // Para arrays (ponteiro para a estrutura do array, se implementada)
        int boolVal;       // Para valores booleanos (0 ou 1)
    } data;
} RuntimeValue;

// --- Tipos de Operadores ---
// Define os diferentes tipos de operações que podem ser realizadas.
typedef enum {
    // Operadores Aritméticos
    OP_PLUS,        // +
    OP_MINUS,       // -
    OP_MULTIPLY,    // *
    OP_DIVIDE,      // /
    OP_MOD,         // % (módulo)
    OP_POWER,       // ^ (potência)

    // Operadores de Comparação
    OP_EQUAL,               // ==
    OP_NOT_EQUAL,           // !=
    OP_LESS_THAN,           // <
    OP_GREATER_THAN,        // >
    OP_LESS_THAN_OR_EQUAL,  // <=
    OP_GREATER_THAN_OR_EQUAL,// >=

    // Operadores Lógicos
    OP_AND,         // AND
    OP_OR,          // OR
    OP_NOT,         // NOT (unário)

    // Operadores de Atribuição
    OP_ASSIGNMENT,          // =
    OP_PLUS_ASSIGNMENT,     // +=
    OP_MINUS_ASSIGNMENT,    // -=
    OP_MULTIPLY_ASSIGNMENT, // *=
    OP_DIVIDE_ASSIGNMENT,   // /=
    OP_MOD_ASSIGNMENT,      // %=
    OP_POWER_ASSIGNMENT,    // ^=

    // Adicione outros operadores conforme necessário
} OperatorType;


// --- Estrutura para Argumentos em Listas de AST ---
// Em um sistema baseado em AST, os argumentos para funções ou PRINTF
// são **expressões** que serão avaliadas posteriormente pelo interpretador.
// Portanto, ArgumentNode agora aponta para um AstNode, não para um RuntimeValue direto.
// A definição completa de 'struct AstNode' está em 'ast.h', então aqui usamos uma declaração forward.
struct AstNode; // Declaração forward para 'struct AstNode'

typedef struct ArgumentNode {
    struct AstNode *node;       // O nó da AST que representa a expressão do argumento
    struct ArgumentNode *next;  // Ponteiro para o próximo argumento na lista encadeada
} ArgumentNode;

#endif // TYPES_H