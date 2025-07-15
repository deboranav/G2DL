// types.h
#ifndef TYPES_H
#define TYPES_H

// Enum para identificar o tipo de dado de uma variável na tabela de símbolos.
typedef enum {
    TYPE_UNKNOWN,
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_STRING,
    TYPE_MATRIX,
    TYPE_FUNCTION,
    TYPE_STRUCT,
    TYPE_VOID,
    TYPE_USER,
} DataType;
// Struct interna do parser para passar os blocos de código de forma limpa.
typedef struct CodeBlocks {
    char* structs;
    char* funcs;
    char* main;
} CodeBlocks;

typedef struct TypeInfo {
    char* c_typename;
    DataType type_enum;
} TypeInfo;

#endif // TYPES_H