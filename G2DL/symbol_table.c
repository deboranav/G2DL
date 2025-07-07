// symbol_table.c

#include "symbol_table.h" // Inclui o cabeçalho da tabela de símbolos

// Inicializa a tabela hash global
Symbol *hash_table[HASH_TABLE_SIZE];

// Função de hash (DJB2 - simples e eficaz para strings)
unsigned int hash(const char *name) {
    unsigned long hash_val = 5381;
    int c;
    while ((c = *name++)) {
        hash_val = ((hash_val << 5) + hash_val) + c; // hash * 33 + c
    }
    return hash_val % HASH_TABLE_SIZE;
}

// Inicializa todos os ponteiros da tabela hash para NULL
void init_symbol_table() {
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        hash_table[i] = NULL;
    }
}

// Insere ou atualiza um símbolo na tabela hash
void insert_symbol(const char *name, RuntimeValue value) {
    unsigned int index = hash(name);
    Symbol *current = hash_table[index];

    // Verifica se o símbolo já existe na lista encadeada naquela posição
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            // Símbolo encontrado, atualiza o valor
            // Libera a string antiga se for do tipo STRING
            if (current->value.type == TYPE_STRING && current->value.data.strVal != NULL) {
                free(current->value.data.strVal);
            }
            current->value = value;
            // Duplica a string do novo valor se for do tipo STRING
            if (value.type == TYPE_STRING && value.data.strVal != NULL) {
                current->value.data.strVal = strdup(value.data.strVal);
            }
            return; // Símbolo atualizado
        }
        current = current->next;
    }

    // Símbolo não encontrado, cria um novo nó e o adiciona no início da lista
    Symbol *new_symbol = (Symbol*) malloc(sizeof(Symbol));
    if (!new_symbol) {
        perror("Erro ao alocar novo Symbol");
        exit(EXIT_FAILURE);
    }

    new_symbol->name = strdup(name); // Duplica o nome (chave)
    if (!new_symbol->name) {
        perror("Erro ao alocar nome do Symbol");
        exit(EXIT_FAILURE);
    }

    new_symbol->value = value;
    // Duplica a string do valor se for do tipo STRING
    if (value.type == TYPE_STRING && value.data.strVal != NULL) {
        new_symbol->value.data.strVal = strdup(value.data.strVal);
    }

    new_symbol->next = hash_table[index]; // Adiciona no início da lista
    hash_table[index] = new_symbol;
}

// Busca um símbolo na tabela hash
// Retorna o ponteiro para o Symbol se encontrado, NULL caso contrário
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

// Libera toda a memória alocada pela tabela de símbolos
void free_symbol_table_memory() {
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        Symbol *current = hash_table[i];
        while (current != NULL) {
            Symbol *temp = current;
            current = current->next;
            free(temp->name); // Libera o nome da variável
            if (temp->value.type == TYPE_STRING && temp->value.data.strVal != NULL) {
                free(temp->value.data.strVal); // Libera a string do valor
            }
            free(temp); // Libera o nó do símbolo
        }
        hash_table[i] = NULL; // Garante que o ponteiro na tabela esteja NULL
    }
}