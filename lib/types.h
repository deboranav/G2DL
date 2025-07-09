// types.h
#ifndef TYPES_H
#define TYPES_H

// Enum para identificar o tipo de dado de uma variável na tabela de símbolos.
typedef enum {
    TYPE_UNKNOWN, // Usado para quando o tipo ainda não foi inferido.
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_STRING
    // Você pode adicionar outros tipos aqui no futuro, como TYPE_ARRAY.
} DataType;

/*
 * As estruturas 'RuntimeValue' e 'ArgumentNode' foram removidas
 * pois eram específicas da lógica do interpretador e não são
 * utilizadas pelo tradutor de código.
 */

#endif // TYPES_H