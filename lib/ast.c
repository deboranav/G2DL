#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbol_table.h"
#include "types.h"
#include "ast.h"

extern int yylineno;

// --- Protótipos ---
void analyze_semantics(ASTNode* node);
static void semantic_traverse(ASTNode* node, Symbol* current_function);
static DataType string_to_type(const char* type_name);
static Member* build_param_list(ASTNode* node);
static void process_member_list(ASTNode* node, UserType* user_type);
static DataType infer_type_from_expression(ASTNode* expr_node);
static void analyze_function_call(ASTNode* node);

// Função genérica para criar um nó
ASTNode* new_ast_node(NodeType type, ASTNode* left, ASTNode* right) {
    ASTNode* node = (ASTNode*) malloc(sizeof(ASTNode));
    if (!node) {
        fprintf(stderr, "Falha ao alocar memória para o nó da AST\n");
        exit(1);
    }
    node->type = type;
    node->left = left;
    node->right = right;
    node->aux = NULL; // Inicializa o ponteiro auxiliar
    node->value.strVal = NULL;
    return node;
}

// Função para criar um nó "folha" para um número
ASTNode* new_ast_leaf_number(double value) {
    ASTNode* node = new_ast_node(AST_NUMBER, NULL, NULL);
    node->value.floatVal = value;
    return node;
}

// Função para criar um nó "folha" para um identificador/variável
ASTNode* new_ast_leaf_id(char* name) {
    ASTNode* node = new_ast_node(AST_IDENTIFIER, NULL, NULL);
    node->value.strVal = name; // strdup(name) é mais seguro se a string original for liberada
    return node;
}

// Função para criar um nó "folha" para uma string literal
ASTNode* new_ast_leaf_string(char* str) {
    ASTNode* node = new_ast_node(AST_STRING, NULL, NULL);
    // Baseado na sua alteração, str já inclui as aspas.
    // Para gerar código C, talvez precisemos processá-lo depois.
    node->value.strVal = str; 
    return node;
}

ASTNode* new_ast_if_node(ASTNode* condition, ASTNode* if_body, ASTNode* else_body) {
    ASTNode* node = new_ast_node(AST_IF, condition, if_body);
    node->aux = else_body;
    return node;
}

ASTNode* new_ast_matrix_decl_node(char* name, ASTNode* rows, ASTNode* cols) {
    ASTNode* node = new_ast_node(AST_MATRIX_DECL, rows, cols);
    node->value.strVal = strdup(name);
    return node;
}

ASTNode* new_ast_matrix_access_node(char* name, ASTNode* row_idx, ASTNode* col_idx) {
    ASTNode* node = new_ast_node(AST_MATRIX_ACCESS, row_idx, col_idx);
    node->value.strVal = strdup(name);
    return node;
}

ASTNode* new_ast_leaf_type(char* type_name) {
    ASTNode* node = new_ast_node(AST_TYPE_SPECIFIER, NULL, NULL);
    node->value.strVal = strdup(type_name);
    return node;
}

ASTNode* new_ast_var_decl_node(ASTNode* type_spec, ASTNode* var_name) {
    // O nome da variável está em var_name->value.strVal
    return new_ast_node(AST_VAR_DECL, type_spec, var_name);
}

ASTNode* new_ast_type_def_node(ASTNode* type_name, ASTNode* members) {
    // O nome do tipo está em type_name->value.strVal
    return new_ast_node(AST_TYPE_DEF, type_name, members);
}

ASTNode* new_ast_param_node(ASTNode* type_spec, ASTNode* param_name) {
    return new_ast_node(AST_PARAM, type_spec, param_name);
}

ASTNode* new_ast_func_def_node(ASTNode* return_type, ASTNode* func_name, ASTNode* params, ASTNode* body) {
    ASTNode* node = new_ast_node(AST_FUNC_DEF, return_type, body);
    node->aux = params;
    node->value.strVal = strdup(func_name->value.strVal);
    return node;
}

// Função recursiva para liberar a memória da árvore
void free_ast(ASTNode* node) {
    if (!node) return;
    free_ast(node->left);
    free_ast(node->right);
    free_ast(node->aux);

    // Libera a string para todos os nós que a utilizam
    switch(node->type) {
        case AST_IDENTIFIER:
        case AST_STRING:
        case AST_TYPE_SPECIFIER:
        case AST_FUNC_DEF:
        case AST_MATRIX_DECL:
        case AST_MATRIX_ACCESS:
        case AST_MEMBER_ACCESS: // Embora o nome do membro seja um ID, o nó principal pode ter uma string
            if(node->value.strVal) free(node->value.strVal);
            break;
        default:
            // Nenhum valor de string para liberar
            break;
    }
    free(node);
}

// Converte o nome de um tipo para o enum DataType
static DataType string_to_type(const char* type_name) {
    if (strcmp(type_name, "float") == 0) return TYPE_FLOAT;
    if (lookup_type(type_name)) return TYPE_USER; // É um tipo definido pelo usuário
    return TYPE_VOID; // Tipo desconhecido
}

// Esta função auxiliar converte um NodeType em uma string legível
const char* nodetype_to_string(NodeType type) {
    switch (type) {
        case AST_NUMBER: return "NUMBER";
        case AST_STRING: return "STRING";
        case AST_IDENTIFIER: return "IDENTIFIER";
        case AST_MATRIX_DECL: return "MATRIX_DECL";
        case AST_MATRIX_ACCESS: return "MATRIX_ACCESS";
        case AST_ADD: return "ADD";
        case AST_SUB: return "SUB";
        case AST_MUL: return "MUL";
        case AST_DIV: return "DIV";
        case AST_EQ: return "EQ";
        case AST_NEQ: return "NEQ";
        case AST_LT: return "LT";
        case AST_GT: return "GT";
        case AST_LTE: return "LTE";
        case AST_GTE: return "GTE";
        case AST_AND: return "AND";
        case AST_OR: return "OR";
        case AST_POW: return "POW";
        case AST_UMINUS: return "UMINUS";
        case AST_NOT: return "NOT";
        case AST_ASSIGN: return "ASSIGN";
        case AST_IF: return "IF";
        case AST_WHILE: return "WHILE";
        case AST_PRINTF: return "PRINTF";
        case AST_INPUT: return "INPUT";
        case AST_FUNC_CALL: return "FUNC_CALL";
        case AST_ARG_LIST: return "ARG_LIST";
        case AST_STATEMENT_LIST: return "STATEMENT_LIST";
        default: return "UNKNOWN_NODE";
    }
}

// Função recursiva que imprime a árvore com indentação
void print_ast_recursive(ASTNode* node, int indent) {
    if (node == NULL) {
        return;
    }

    // Imprime a indentação
    for (int i = 0; i < indent; ++i) {
        printf("  ");
    }

    // Imprime o tipo do nó
    printf("- %s", nodetype_to_string(node->type));

    // Imprime o valor do nó, se for uma folha
    if (node->type == AST_NUMBER) {
        printf(": %f\n", node->value.floatVal);
    } else if (node->type == AST_IDENTIFIER || node->type == AST_STRING || 
               node->type == AST_MATRIX_DECL || node->type == AST_MATRIX_ACCESS) {
        printf(": %s\n", node->value.strVal);
    } else {
        printf("\n");
    }

    // Chama recursivamente para os filhos
    print_ast_recursive(node->left, indent + 1);
    print_ast_recursive(node->right, indent + 1);
    print_ast_recursive(node->aux, indent + 1);
}

// Função principal que inicia a impressão da AST
void print_ast(ASTNode* root) {
    printf("\n\n--- INICIO DA ARVORE SINTATICA (AST) ---\n");
    print_ast_recursive(root, 0);
    printf("--- FIM DA ARVORE SINTATICA (AST) ---\n\n");
}

// Função auxiliar para inferir o tipo de uma expressão
static DataType infer_type_from_expression(ASTNode* expr_node) {
    if (!expr_node) return TYPE_VOID;

    switch(expr_node->type) {
        case AST_NUMBER: return TYPE_FLOAT;
        case AST_STRING: return TYPE_STRING; // Embora não usado neste exemplo
        case AST_INPUT: return TYPE_FLOAT;
        
        case AST_IDENTIFIER: {
            Symbol* s = scope_lookup(expr_node->value.strVal);
            return s ? s->type : TYPE_VOID;
        }
        case AST_MATRIX_ACCESS: return TYPE_FLOAT; // Acesso a elemento de matriz retorna um número
        
        case AST_MEMBER_ACCESS: { // <<< LÓGICA ADICIONADA
            // O tipo de 'var.membro' é o tipo do 'membro'.
            // Primeiro, precisamos descobrir o tipo de 'var'.
            ASTNode* var_node = expr_node->left;
            DataType var_type_enum = infer_type_from_expression(var_node);

            if (var_type_enum == TYPE_USER) {
                Symbol* var_symbol = scope_lookup(var_node->value.strVal);
                UserType* user_type = lookup_type(var_symbol->typeName);
                char* member_name = expr_node->right->value.strVal;

                // Procura o membro na definição do tipo
                Member* m = user_type->members;
                while(m) {
                    if (strcmp(m->name, member_name) == 0) {
                        return m->type; // Encontramos o tipo do membro!
                    }
                    m = m->next;
                }
            }
            return TYPE_VOID; // Não foi possível determinar o tipo
        }
        
        case AST_ADD: case AST_SUB: case AST_MUL: case AST_DIV: case AST_POW: return TYPE_FLOAT;
        default: return TYPE_VOID;
    }
}

static void process_member_list(ASTNode* node, UserType* user_type) {
    if (!node) return;

    if (node->type == AST_STATEMENT_LIST) {
        // Se for uma lista, processa a esquerda e a direita
        process_member_list(node->left, user_type);
        process_member_list(node->right, user_type);
    } else if (node->type == AST_VAR_DECL) {
        // Encontramos um membro (ex: float numerador)
        ASTNode* type_spec_node = node->left;
        ASTNode* member_name_node = node->right;
        
        char* member_name = member_name_node->value.strVal;
        
        // Uma versão mais avançada leria o tipo de type_spec_node.
        add_member_to_type(user_type, member_name, TYPE_FLOAT);
    }
}

// Constrói uma lista de 'Member' a partir de uma AST de parâmetros
static Member* build_param_list(ASTNode* node) {
    if (!node) return NULL;

    if (node->type == AST_PARAM_LIST) {
        Member* head = build_param_list(node->left);
        Member* current = head;
        while (current && current->next) {
            current = current->next;
        }
        if (current) {
            current->next = build_param_list(node->right);
        } else {
            head = build_param_list(node->right);
        }
        return head;
    } else if (node->type == AST_PARAM) {
        Member* param = (Member*) malloc(sizeof(Member));
        param->name = strdup(node->right->value.strVal);
        param->typeName = strdup(node->left->value.strVal);
        param->type = string_to_type(param->typeName);
        param->next = NULL;
        return param;
    }
    return NULL;
}

static void analyze_function_call(ASTNode* node) {
    char* func_name = node->left->value.strVal;
    Symbol* func_symbol = scope_lookup(func_name);

    // 1. Verifica se a função foi declarada
    if (!func_symbol) {
        fprintf(stderr, "Erro semantico na linha %d: Funcao '%s' nao foi declarada.\n", yylineno, func_name);
        return;
    }
    if (func_symbol->type != TYPE_FUNCTION) {
        fprintf(stderr, "Erro semantico na linha %d: Variavel '%s' nao e uma funcao e nao pode ser chamada.\n", yylineno, func_name);
        return;
    }

    // 2. Compara o número de argumentos com o número de parâmetros
    ASTNode* arg_node = node->right;
    Member* param_node = func_symbol->params;
    int arg_count = 0;
    int param_count = 0;

    // Conta os parâmetros esperados
    Member* p = param_node;
    while(p) {
        param_count++;
        p = p->next;
    }
    
    // Conta os argumentos fornecidos
    ASTNode* a = arg_node;
    if (a) {
        if (a->type == AST_ARG_LIST) {
             // Conta recursivamente para listas de argumentos
            ASTNode* current_arg = a;
            while(current_arg && current_arg->type == AST_ARG_LIST) {
                arg_count++;
                current_arg = current_arg->left;
            }
            arg_count++;
        } else {
            arg_count = 1; // Apenas um argumento
        }
    }
    

    if (arg_count != param_count) {
        fprintf(stderr, "Erro semantico na linha %d: Funcao '%s' espera %d argumento(s), mas recebeu %d.\n", yylineno, func_name, param_count, arg_count);
        return;
    }

    // 3. Verifica o tipo de cada argumento (simplificado)
    // Uma verificação completa percorreria as duas listas (argumentos e parâmetros) em paralelo
    // e compararia o tipo de cada um.
    if(arg_node) {
        semantic_traverse(arg_node, func_symbol);
    }
}


// Função principal que percorre a árvore recursivamente
static void semantic_traverse(ASTNode* node, Symbol* current_function) {
    if (!node) return;

    // Ações pré-ordem (acontecem antes de visitar os filhos)
    switch (node->type) {
        case AST_MATRIX_DECL: {
            char* name = node->value.strVal;
            
            // 1. Verifica se o símbolo já existe no escopo atual
            if (scope_lookup_current(name)) {
                fprintf(stderr, "Erro semantico na linha %d: Redeclaracao da matriz '%s'.\n", yylineno, name);
            } else {
                // 2. Extrai as dimensões. Assume que são literais numéricos por enquanto.
                ASTNode* rows_node = node->left;
                ASTNode* cols_node = node->right;

                if (rows_node->type != AST_NUMBER || cols_node->type != AST_NUMBER) {
                    fprintf(stderr, "Erro semantico na linha %d: Dimensoes da matriz '%s' devem ser numeros inteiros literais.\n", yylineno, name);
                } else {
                    int rows = (int)rows_node->value.floatVal;
                    int cols = (int)cols_node->value.floatVal;
                    
                    // 3. Adiciona o símbolo à tabela
                    scope_add_symbol(name, TYPE_MATRIX, NULL, (int)node->left->value.floatVal, (int)node->right->value.floatVal, NULL);
                }
            }
            // Não precisa descer recursivamente, pois já tratamos os filhos
            return;
        }

        case AST_MATRIX_ACCESS: {
            char* name = node->value.strVal;
            Symbol* symbol = scope_lookup(name);

            // 1. Verifica se a variável existe
            if (!symbol) {
                fprintf(stderr, "Erro semantico na linha %d: Matriz '%s' nao foi declarada.\n", yylineno, name);
            } 
            // 2. Verifica se é do tipo matriz
            else if (symbol->type != TYPE_MATRIX) {
                fprintf(stderr, "Erro semantico na linha %d: Variavel '%s' nao e uma matriz.\n", yylineno, name);
            }
            
            // Analisa as expressões de índice
            semantic_traverse(node->left, current_function);
            semantic_traverse(node->right, current_function);
            return;
        }

        case AST_TYPE_DEF: {
            char* type_name = node->left->value.strVal;
            if (lookup_type(type_name)) {
                fprintf(stderr, "Erro semantico na linha %d: Tipo '%s' ja foi definido.\n", yylineno, type_name);
            } else {
                // 1. Cria o novo tipo na tabela de tipos
                UserType* new_type = define_type(type_name);
                // 2. Processa a lista de membros para preencher a struct
                process_member_list(node->right, new_type);
            }
            return; // Já processamos os filhos, podemos retornar
        }

        case AST_FUNC_DEF: {
            char* func_name = node->value.strVal;
            if (scope_lookup_current(func_name)) {
                fprintf(stderr, "Erro semantico na linha %d: Redeclaracao da funcao '%s'.\n", yylineno, func_name);
                return;
            }

            // 1. Constrói a lista de parâmetros
            Member* params = build_param_list(node->aux);
            
            // 2. Adiciona a função ao escopo atual (global)
            scope_add_symbol(func_name, TYPE_FUNCTION, node->left->value.strVal, 0, 0, params);
            
            Symbol* func_symbol = scope_lookup_current(func_name);

            // 3. Entra em um novo escopo para o corpo da função
            scope_enter();

            // 4. Adiciona os parâmetros ao novo escopo
            Member* p = params;
            while(p) {
                scope_add_symbol(p->name, p->type, p->typeName, 0, 0, NULL);
                p = p->next;
            }

            // 5. Analisa o corpo da função
            semantic_traverse(node->right, func_symbol);

            // 6. Sai do escopo da função
            scope_leave();
            return;
        }

        case AST_VAR_DECL: {
            char* type_name = node->left->value.strVal;
            char* var_name = node->right->value.strVal;
                    
            if (scope_lookup_current(var_name)) {
                fprintf(stderr, "Erro semantico na linha %d: Redeclaracao da variavel '%s'.\n", yylineno, var_name);
            } else {
                DataType type = string_to_type(type_name);
                if (type == TYPE_VOID) {
                    fprintf(stderr, "Erro semantico na linha %d: Tipo desconhecido '%s'.\n", yylineno, type_name);
                } else {
                    scope_add_symbol(var_name, type, (type == TYPE_USER ? type_name : NULL), 0, 0, NULL);
                }
            }
            return;
        }

        case AST_MEMBER_ACCESS: {
            ASTNode* var_node = node->left;
            char* member_name = node->right->value.strVal;

            // Analisa a variável à esquerda (ex: 'r1')
            semantic_traverse(var_node, current_function);
            
            Symbol* symbol = scope_lookup(var_node->value.strVal);
            if (symbol && symbol->type == TYPE_USER) {
                UserType* user_type = lookup_type(symbol->typeName);
                // Procura para ver se o membro existe
                Member* m = user_type->members;
                int found = 0;
                while(m) {
                    if (strcmp(m->name, member_name) == 0) {
                        found = 1;
                        break;
                    }
                    m = m->next;
                }
                if (!found) {
                    fprintf(stderr, "Erro semantico na linha %d: Tipo '%s' nao tem membro chamado '%s'.\n", yylineno, user_type->name, member_name);
                }
            } else if (symbol) {
                fprintf(stderr, "Erro semantico na linha %d: Variavel '%s' nao e de um tipo que permite acesso a membros.\n", yylineno, symbol->name);
            }
            return;
        }

        case AST_RETURN: {
            if (!current_function) {
                fprintf(stderr, "Erro semantico na linha %d: 'return' fora de uma funcao.\n", yylineno);
                return;
            }
            
            // Analisa a expressão de retorno para inferir seu tipo
            semantic_traverse(node->left, current_function);
            DataType return_expr_type = infer_type_from_expression(node->left);

            // Pega o tipo de retorno esperado da função
            DataType expected_return_type = string_to_type(current_function->typeName);

            // Compara os tipos
            if (return_expr_type != expected_return_type) {
                fprintf(stderr, "Aviso na linha %d: Tipo de retorno incompativel na funcao '%s'.\n", yylineno, current_function->name);
            }
            return;
        }

        case AST_FUNC_CALL: {
            analyze_function_call(node);
            return;
        }

        case AST_ASSIGN: {
            ASTNode* lhs = node->left;
            ASTNode* rhs = node->right;
            semantic_traverse(rhs, current_function);
            DataType rhs_type = infer_type_from_expression(rhs);
            
            if (lhs->type == AST_IDENTIFIER) {
                Symbol* symbol = scope_lookup(lhs->value.strVal);
                if (!symbol) {
                    scope_add_symbol(lhs->value.strVal, rhs_type, NULL, 0, 0, NULL);
                } else if (symbol->type != rhs_type && rhs_type != TYPE_VOID) {
                    fprintf(stderr, "Aviso na linha %d: Atribuindo tipo incompátivel para a variavel '%s'.\n", yylineno, lhs->value.strVal);
                }
            } else if (lhs->type == AST_MATRIX_ACCESS) {
                semantic_traverse(lhs, current_function);
                if (rhs_type != TYPE_FLOAT && rhs_type != TYPE_VOID) {
                    fprintf(stderr, "Aviso na linha %d: Elementos de matriz devem receber valores numericos.\n", yylineno);
                }
            }
            return;
        }

        case AST_IDENTIFIER: {
            // USO DE VARIÁVEL: Verifica se a variável foi declarada.
            if (scope_lookup(node->value.strVal) == NULL) {
                fprintf(stderr, "Erro semantico: Variavel '%s' usada antes de ser declarada.\n", node->value.strVal);
            }
            return; // Folha, não tem filhos para visitar
        }
    }

    // Travessia normal para os outros nós
    semantic_traverse(node->left, current_function);
    semantic_traverse(node->right, current_function);
    semantic_traverse(node->aux, current_function);
}

// Função pública que inicia o processo
void analyze_semantics(ASTNode* root) {
    if (!root) return;
    semantic_traverse(root, NULL);
}