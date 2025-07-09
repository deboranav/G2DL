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
    
    // Inicializa a lista para iteração
    symbol_count = 0;
    symbol_list_capacity = 20; // Define uma capacidade inicial
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
            return current; // Símbolo encontrado
        }
        current = current->next;
    }
    return NULL; // Símbolo não encontrado
}

// Adiciona um novo símbolo à tabela (se ele ainda não existir)
Symbol* add_symbol(const char *name, DataType type) {
    Symbol *existing_symbol = lookup_symbol(name);
    if (existing_symbol != NULL) {
        // Se o símbolo já existe, apenas retorna o ponteiro para ele.
        // Não fazemos nada, pois só precisamos do registro do nome e tipo.
        return existing_symbol;
    }

    // Se não existe, cria um novo símbolo
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

    // Adiciona o novo símbolo no início da lista encadeada (bucket)
    new_symbol->next = hash_table[index];
    hash_table[index] = new_symbol;

    // Adiciona o ponteiro para o novo símbolo na nossa lista de iteração
    if (symbol_count >= symbol_list_capacity) {
        // Dobra a capacidade se a lista estiver cheia
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
    return NULL; // Índice fora dos limites
}

// Libera toda a memória alocada pela tabela e pela lista
void free_symbol_table_memory() {
    // Libera a memória da tabela hash
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        Symbol *current = hash_table[i];
        while (current != NULL) {
            Symbol *temp = current;
            current = current->next;
            free(temp->name); // Libera a string do nome
            free(temp);       // Libera o nó do símbolo
        }
        hash_table[i] = NULL;
    }
    
    // Libera a memória da lista de iteração
    if (symbol_list != NULL) {
        free(symbol_list);
        symbol_list = NULL;
    }
    symbol_count = 0;
    symbol_list_capacity = 0;
}