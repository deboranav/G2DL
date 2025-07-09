// types.h
#ifndef TYPES_H
#define TYPES_H

// Enum para identificar o tipo de dado de uma variável na tabela de símbolos.
typedef enum {
    TYPE_UNKNOWN,
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_STRING,
    TYPE_MATRIX
} DataType;

#endif // TYPES_H