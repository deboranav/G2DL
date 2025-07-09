// symbol_table.h

#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"

#define HASH_TABLE_SIZE 101

// --- ESTRUTURAS PARA O NOVO SISTEMA DE TIPOS ---

// Representa um membro dentro de uma struct (ex: o campo 'numerador')
typedef struct Member {
    char *name;
    DataType type;
    struct Member *next;
} Member;

// Representa um tipo definido pelo usuário (ex: a struct 'rational_t')
typedef struct UserType {
    char *name;
    Member *members;
    struct UserType *next;
} UserType;

// --- ESTRUTURA UNIFICADA PARA SÍMBOLOS (VARIÁVEIS) ---
typedef struct Symbol {
    char *name;
    DataType type;      // Será TYPE_FLOAT, TYPE_FUNCTION, TYPE_MATRIX, ou TYPE_STRUCT
    char *typeName;     // Se type == TYPE_STRUCT, aqui guardamos o nome do tipo (ex: "rational_t")
    int rows;           // Para matrizes
    int cols;           // Para matrizes
    struct Symbol *next;
} Symbol;

extern Symbol *hash_table[HASH_TABLE_SIZE];


// --- PROTÓTIPOS DE FUNÇÕES ---

// Funções da Tabela de Símbolos (Variáveis)
void init_symbol_table();
Symbol* lookup_symbol(const char *name);
Symbol* add_symbol(const char *name, DataType type); // Para escalares
Symbol* add_matrix_symbol(const char *name, int rows, int cols); // Para matrizes
Symbol* add_struct_variable_symbol(const char *name, const char *typeName); // Para structs
void free_symbol_table_memory();
int get_symbol_count();
Symbol* get_symbol_by_index(int index);

// Funções da Tabela de Tipos (Structs)
void init_type_table();
UserType* define_type(const char *typeName);
void add_member_to_type(UserType* type, const char *memberName, DataType memberType);
UserType* lookup_type(const char *typeName);
void free_type_table_memory();
// Adicione um protótipo para obter a lista de tipos se precisar iterar
UserType* get_type_table_head();


#endif // SYMBOL_TABLE_H