#include "symbol_table.h" // Inclui o cabeçalho correspondente

// Tabela hash global
Symbol *hash_table[HASH_TABLE_SIZE];

// Estruturas de dados para permitir a iteração ordenada dos símbolos
static Symbol **symbol_list = NULL;       // Array dinâmico de ponteiros para os símbolos
static int symbol_count = 0;              // Número atual de símbolos na lista
static int symbol_list_capacity = 0;      // Capacidade atual do array da lista

// Função de hash (DJB2 - simples e eficaz para strings)
unsigned int hash(const char *name) {
    unsigned long hash_val = 5381;
    int c;
    while ((c = *name++)) {
        hash_val = ((hash_val << 5) + hash_val) + c; // hash * 33 + c
    }
    return hash_val % HASH_TABLE_SIZE;
}

// Inicializa a tabela de símbolos e a lista de iteração
void init_symbol_table() {
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        hash_table[i] = NULL;
    }
    
    symbol_count = 0;
    symbol_list_capacity = 20;
    symbol_list = malloc(symbol_list_capacity * sizeof(Symbol*));
    if (!symbol_list) {
        perror("Falha ao alocar a lista de símbolos");
        exit(EXIT_FAILURE);
    }
}

// Busca um símbolo na tabela hash
Symbol* lookup_symbol(const char *name) {
    unsigned int index = hash(name);
    Symbol *current = hash_table[index];
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

Symbol* add_symbol(const char *name, DataType type) {
    unsigned int index = hash(name);
    Symbol *new_symbol = (Symbol*) malloc(sizeof(Symbol));
    if (!new_symbol) {
        perror("Erro ao alocar novo Symbol");
        exit(EXIT_FAILURE);
    }

    new_symbol->name = strdup(name);
    if (!new_symbol->name) {
        perror("Erro ao alocar nome do Symbol");
        exit(EXIT_FAILURE);
    }
    new_symbol->type = type;
    new_symbol->rows = 0;
    new_symbol->cols = 0;

    new_symbol->next = hash_table[index];
    hash_table[index] = new_symbol;

    if (symbol_count >= symbol_list_capacity) {
        symbol_list_capacity *= 2;
        symbol_list = realloc(symbol_list, symbol_list_capacity * sizeof(Symbol*));
        if (!symbol_list) {
            perror("Falha ao realocar a lista de símbolos");
            exit(EXIT_FAILURE);
        }
    }
    symbol_list[symbol_count] = new_symbol;
    symbol_count++;

    return new_symbol;
}


// FUNÇÃO PARA MATRIZES
Symbol* add_matrix_symbol(const char *name, int rows, int cols) {
    unsigned int index = hash(name);
    Symbol *new_symbol = (Symbol*) malloc(sizeof(Symbol));
    if (!new_symbol) {
        perror("Erro ao alocar novo Symbol para matriz");
        exit(EXIT_FAILURE);
    }

    new_symbol->name = strdup(name);
    if (!new_symbol->name) {
        perror("Erro ao alocar nome do Symbol");
        exit(EXIT_FAILURE);
    }
    
    new_symbol->type = TYPE_MATRIX;
    new_symbol->rows = rows;
    new_symbol->cols = cols;

    new_symbol->next = hash_table[index];
    hash_table[index] = new_symbol;

    if (symbol_count >= symbol_list_capacity) {
        symbol_list_capacity *= 2;
        symbol_list = realloc(symbol_list, symbol_list_capacity * sizeof(Symbol*));
        if (!symbol_list) {
            perror("Falha ao realocar a lista de símbolos");
            exit(EXIT_FAILURE);
        }
    }
    symbol_list[symbol_count] = new_symbol;
    symbol_count++;

    return new_symbol;
}


// Retorna o número total de símbolos únicos
int get_symbol_count() {
    return symbol_count;
}

// Retorna um símbolo pelo seu índice na ordem de inserção
Symbol* get_symbol_by_index(int index) {
    if (index >= 0 && index < symbol_count) {
        return symbol_list[index];
    }
    return NULL;
}

// Libera toda a memória alocada pela tabela e pela lista
void free_symbol_table_memory() {
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        Symbol *current = hash_table[i];
        while (current != NULL) {
            Symbol *temp = current;
            current = current->next;
            free(temp->name);
            free(temp);
        }
        hash_table[i] = NULL;
    }
    
    if (symbol_list != NULL) {
        free(symbol_list);
        symbol_list = NULL;
    }
    symbol_count = 0;
    symbol_list_capacity = 0;
}