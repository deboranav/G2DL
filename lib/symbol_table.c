// lib/symbol_table.c
#include "symbol_table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_TABLE_SIZE 101

/* --- Variáveis Estáticas do Módulo --- */
static Scope* current_scope = NULL;
static UserType *type_table_head = NULL;

/* --- Funções Internas --- */

static unsigned int hash(const char *name) {
    unsigned long hash_val = 5381;
    int c;
    while ((c = *name++)) {
        hash_val = ((hash_val << 5) + hash_val) + c;
    }
    return hash_val % HASH_TABLE_SIZE;
}

// Helper para buscar em um escopo específico
static Symbol* lookup_in_scope(const char *name, Scope* s) {
    if (!s) return NULL;
    unsigned int index = hash(name);
    Symbol *sym = s->hash_table[index];
    while (sym != NULL) {
        if (strcmp(sym->name, name) == 0) return sym;
        sym = sym->next;
    }
    return NULL;
}

static void free_type_table() {
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


/* --- Implementação da Interface Pública --- */

void scope_init() {
    current_scope = NULL;
    type_table_head = NULL;
    scope_enter(); // Entra no escopo global
}

void scope_enter() {
    Scope* new_scope = (Scope*) malloc(sizeof(Scope));
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        new_scope->hash_table[i] = NULL;
    }
    new_scope->parent = current_scope;
    current_scope = new_scope;
}

void scope_leave() {
    if (current_scope == NULL) return;
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        Symbol *current_sym = current_scope->hash_table[i];
        while (current_sym != NULL) {
            Symbol *temp = current_sym;
            current_sym = current_sym->next;
            free(temp->name);
            if (temp->typeName) free(temp->typeName);
            free(temp);
        }
    }
    Scope* parent_scope = current_scope->parent;
    free(current_scope);
    current_scope = parent_scope;
}

void scope_add_symbol(const char *name, DataType type, const char* typeName, int rows, int cols) {
    if (current_scope == NULL) return;
    unsigned int index = hash(name);
    Symbol *new_symbol = (Symbol*) malloc(sizeof(Symbol));
    new_symbol->name = strdup(name);
    new_symbol->type = type;
    new_symbol->typeName = typeName ? strdup(typeName) : NULL;
    new_symbol->rows = rows;
    new_symbol->cols = cols;
    new_symbol->next = current_scope->hash_table[index];
    current_scope->hash_table[index] = new_symbol;
}

Symbol* scope_lookup_current(const char *name) {
    return lookup_in_scope(name, current_scope);
}

// CORREÇÃO DO BUG: Agora busca corretamente nos escopos pais.
Symbol* scope_lookup(const char *name) {
    Scope* scope_to_search = current_scope;
    while (scope_to_search != NULL) {
        Symbol* found = lookup_in_scope(name, scope_to_search);
        if (found) return found;
        scope_to_search = scope_to_search->parent;
    }
    return NULL;
}

void free_all_scopes() {
    free_type_table(); // Também libera a tabela de tipos
    while (current_scope != NULL) {
        scope_leave();
    }
}


// --- Funções da Tabela de Tipos ---

UserType* lookup_type(const char *typeName) {
    UserType *current = type_table_head;
    while (current != NULL) {
        if (strcmp(current->name, typeName) == 0) return current;
        current = current->next;
    }
    return NULL;
}

UserType* define_type(const char *typeName) {
    if (lookup_type(typeName) != NULL) return NULL; 
    UserType *new_type = (UserType*) malloc(sizeof(UserType));
    new_type->name = strdup(typeName);
    new_type->members = NULL;
    new_type->next = type_table_head;
    type_table_head = new_type;
    return new_type;
}

void add_member_to_type(UserType* type, const char *memberName, DataType memberType) {
    if (!type) return;
    Member *new_member = (Member*) malloc(sizeof(Member));
    new_member->name = strdup(memberName);
    new_member->type = memberType;
    new_member->next = type->members;
    type->members = new_member;
}

UserType* get_type_table_head(){
    return type_table_head;
}