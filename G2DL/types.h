// types.h
#ifndef TYPES_H
#define TYPES_H

// Definição de RuntimeValue
typedef enum {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_STRING,
    TYPE_ARRAY,
    TYPE_VOID // Para funções que não retornam valor
} ValueType;

typedef struct {
    ValueType type;
    union {
        int intVal;
        float floatVal;
        char *strVal;
        // void *arrayVal; // Se você for implementar arrays mais tarde
    } data;
} RuntimeValue;

// Definição de ArgumentNode
typedef struct ArgumentNode {
    RuntimeValue value;
    struct ArgumentNode *next;
} ArgumentNode;

#endif // TYPES_H