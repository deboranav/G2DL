// symbol_table.h

#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h" // Presume-se que este arquivo define o enum DataType

// Define o tamanho da tabela hash (um número primo é geralmente bom)
#define HASH_TABLE_SIZE 101

// Estrutura para um nó na lista encadeada (para colisões)
// Alterado para as necessidades do tradutor: não armazena mais o valor, apenas o tipo.
typedef struct Symbol {
    char *name;          // Nome da variável (chave)
    DataType type;       // Tipo da variável (ex: TYPE_INT, TYPE_FLOAT)
    struct Symbol *next; // Próximo nó na lista (em caso de colisão)
} Symbol;

// A própria tabela hash (um array de ponteiros para Symbol)
extern Symbol *hash_table[HASH_TABLE_SIZE];

// --- Protótipos das Funções ---

// Função hash interna
unsigned int hash(const char *name);

// Inicializa a tabela de símbolos
void init_symbol_table();

// Adiciona um novo símbolo à tabela. Não adiciona se já existir.
// Retorna o ponteiro para o símbolo (novo ou existente).
Symbol* add_symbol(const char *name, DataType type);

// Procura por um símbolo na tabela pelo nome.
Symbol* lookup_symbol(const char *name);

// Libera toda a memória alocada pela tabela de símbolos.
void free_symbol_table_memory();

// Retorna o número total de símbolos na tabela.
int get_symbol_count();

// Retorna um símbolo pelo seu índice na ordem de inserção.
Symbol* get_symbol_by_index(int index);

#endif // SYMBOL_TABLE_H