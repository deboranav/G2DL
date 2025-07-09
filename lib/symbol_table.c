#include "symbol_table.h"

// --- GLOBAIS PARA TABELA DE SÍMBOLOS (VARIÁVEIS) ---
Symbol *hash_table[HASH_TABLE_SIZE];
static Symbol **symbol_list = NULL;
static int symbol_count = 0;
static int symbol_list_capacity = 0;

// --- GLOBAIS PARA TABELA DE TIPOS (STRUCTS) ---
static UserType *type_table_head = NULL;


// Função de hash (a mesma para ambos os tipos de tabelas)
unsigned int hash(const char *name) {
    unsigned long hash_val = 5381;
    int c;
    while ((c = *name++)) {
        hash_val = ((hash_val << 5) + hash_val) + c;
    }
    return hash_val % HASH_TABLE_SIZE;
}


// --- INICIALIZAÇÃO ---

void init_type_table() {
    type_table_head = NULL;
}

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
    // Inicializa a tabela de tipos também
    init_type_table();
}


// --- FUNÇÕES DA TABELA DE TIPOS (STRUCTS) ---

UserType* lookup_type(const char *typeName) {
    UserType *current = type_table_head;
    while (current != NULL) {
        if (strcmp(current->name, typeName) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

UserType* define_type(const char *typeName) {
    if (lookup_type(typeName) != NULL) {
        // Erro semântico: tipo já definido
        return NULL; 
    }
    UserType *new_type = (UserType*) malloc(sizeof(UserType));
    new_type->name = strdup(typeName);
    new_type->members = NULL;
    new_type->next = type_table_head; // Adiciona no início da lista
    type_table_head = new_type;
    return new_type;
}

void add_member_to_type(UserType* type, const char *memberName, DataType memberType) {
    if (!type) return;
    Member *new_member = (Member*) malloc(sizeof(Member));
    new_member->name = strdup(memberName);
    new_member->type = memberType;
    new_member->next = type->members; // Adiciona no início da lista de membros
    type->members = new_member;
}

UserType* get_type_table_head() {
    return type_table_head;
}


// --- FUNÇÕES DA TABELA DE SÍMBOLOS (VARIÁVEIS) ---

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

// Função auxiliar interna para adicionar qualquer novo símbolo
static Symbol* _add_new_symbol_to_list(Symbol* new_symbol) {
    unsigned int index = hash(new_symbol->name);
    new_symbol->next = hash_table[index];
    hash_table[index] = new_symbol;

    if (symbol_count >= symbol_list_capacity) {
        symbol_list_capacity *= 2;
        symbol_list = realloc(symbol_list, symbol_list_capacity * sizeof(Symbol*));
    }
    symbol_list[symbol_count] = new_symbol;
    symbol_count++;
    return new_symbol;
}

Symbol* add_symbol(const char *name, DataType type) {
    Symbol *new_symbol = (Symbol*) malloc(sizeof(Symbol));
    new_symbol->name = strdup(name);
    new_symbol->type = type;
    new_symbol->typeName = NULL; // <-- Importante: inicializa como NULL para escalares
    new_symbol->rows = 0;
    new_symbol->cols = 0;
    return _add_new_symbol_to_list(new_symbol);
}

Symbol* add_matrix_symbol(const char *name, int rows, int cols) {
    Symbol *new_symbol = (Symbol*) malloc(sizeof(Symbol));
    new_symbol->name = strdup(name);
    new_symbol->type = TYPE_MATRIX;
    new_symbol->typeName = NULL; // <-- Importante: inicializa como NULL
    new_symbol->rows = rows;
    new_symbol->cols = cols;
    return _add_new_symbol_to_list(new_symbol);
}

// <-- NOVA FUNÇÃO para adicionar variáveis de um tipo struct
Symbol* add_struct_variable_symbol(const char *name, const char *typeName) {
    Symbol *new_symbol = (Symbol*) malloc(sizeof(Symbol));
    new_symbol->name = strdup(name);
    new_symbol->type = TYPE_STRUCT;
    new_symbol->typeName = strdup(typeName); // <-- Armazena o nome do tipo
    new_symbol->rows = 0;
    new_symbol->cols = 0;
    return _add_new_symbol_to_list(new_symbol);
}

int get_symbol_count() {
    return symbol_count;
}

Symbol* get_symbol_by_index(int index) {
    if (index >= 0 && index < symbol_count) {
        return symbol_list[index];
    }
    return NULL;
}


// --- LIBERAÇÃO DE MEMÓRIA ---

void free_type_table_memory() {
    UserType *current_type = type_table_head;
    while (current_type != NULL) {
        UserType *temp_type = current_type;
        current_type = current_type->next;

        Member *current_member = temp_type->members;
        while (current_member != NULL) {
            Member *temp_member = current_member;
            current_member = current_member->next;
            free(temp_member->name);
            free(temp_member);
        }
        free(temp_type->name);
        free(temp_type);
    }
}

void free_symbol_table_memory() {
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        Symbol *current = hash_table[i];
        while (current != NULL) {
            Symbol *temp = current;
            current = current->next;
            free(temp->name);
            if (temp->typeName) { // <-- Importante: libera o typeName se existir
                free(temp->typeName);
            }
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

    // Libera a tabela de tipos também
    free_type_table_memory();
}