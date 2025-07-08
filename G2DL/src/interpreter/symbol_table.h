// symbol_table.h

#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"


// Define o tamanho da tabela hash (um número primo é geralmente bom)
#define HASH_TABLE_SIZE 101

// Estrutura para um nó na lista encadeada (para colisões)
typedef struct Symbol {
    char *name;         // Nome da variável (chave)
    RuntimeValue value; // Valor associado
    struct Symbol *next; // Próximo nó na lista (em caso de colisão)
} Symbol;

// A própria tabela hash (um array de ponteiros para Symbol)
extern Symbol *hash_table[HASH_TABLE_SIZE];

// Protótipos das funções da tabela de símbolos
unsigned int hash(const char *name);
void init_symbol_table();
void insert_symbol(const char *name, RuntimeValue value);
Symbol* lookup_symbol(const char *name);
void free_symbol_table_memory();

#endif // SYMBOL_TABLE_H