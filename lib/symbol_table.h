#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"

#define HASH_TABLE_SIZE 101

// --- ESTRUTURAS DE DADOS ---
// A ordem aqui é importante para evitar erros de "tipo desconhecido".

typedef struct Member {
    char *name;
    DataType type;
    struct Member *next;
} Member;

typedef struct UserType {
    char *name;
    Member *members;
    struct UserType *next;
} UserType;

typedef struct Symbol {
    char *name;
    DataType type;
    char *typeName;
    int rows;
    int cols;
    struct Symbol *next;
} Symbol;

typedef struct Scope {
    Symbol* hash_table[HASH_TABLE_SIZE];
    struct Scope* parent;
} Scope;


// --- INTERFACE PÚBLICA DO MÓDULO ---

void scope_init();
void scope_enter();
void scope_leave();

// MUDANÇA: Assinatura da função corrigida para aceitar todos os dados necessários.
void scope_add_symbol(const char *name, DataType type, const char* typeName, int rows, int cols);

Symbol* scope_lookup(const char *name);
Symbol* scope_lookup_current(const char *name);
void free_all_scopes();

// Funções da Tabela de Tipos
UserType* define_type(const char *typeName);
UserType* lookup_type(const char *typeName);
void add_member_to_type(UserType* type, const char *memberName, DataType memberType);
UserType* get_type_table_head();

#endif // SYMBOL_TABLE_H