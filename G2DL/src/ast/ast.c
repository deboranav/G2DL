// ast.c - Implementa as funções para criar e manipular os nós da AST.

#include "ast.h"    // Inclui as definições das estruturas e protótipos
#include <stdlib.h> // Para malloc, free, realloc
#include <string.h> // Para strdup
#include <stdio.h>  // Para perror, fprintf, NULL

// Variável externa para obter o número da linha atual do lexer/parser
extern int yylineno;

// --- Função Auxiliar para Criar a Base de um Nó AST ---
// Esta função é usada internamente por todas as funções 'create_X_node'
// para inicializar os campos comuns de `AstNode`.
static AstNode* create_base_node(AstNodeType type, size_t size) {
    AstNode* node = (AstNode*)malloc(size);
    if (!node) {
        perror("Erro de alocação de memória para nó AST");
        exit(EXIT_FAILURE); // Em caso de falha crítica na alocação
    }
    node->type = type;
    node->line_number = yylineno; // Atribui o número da linha atual
    return node;
}

// --- Implementações das Funções Construtoras de Nós da AST ---

AstNode* create_int_literal_node(int value) {
    IntLiteralNode* node = (IntLiteralNode*)create_base_node(NODE_TYPE_INT_LITERAL, sizeof(IntLiteralNode));
    node->value = value;
    return (AstNode*)node;
}

AstNode* create_float_literal_node(float value) {
    FloatLiteralNode* node = (FloatLiteralNode*)create_base_node(NODE_TYPE_FLOAT_LITERAL, sizeof(FloatLiteralNode));
    node->value = value;
    return (AstNode*)node;
}

AstNode* create_string_literal_node(char *value) {
    StringLiteralNode* node = (StringLiteralNode*)create_base_node(NODE_TYPE_STRING_LITERAL, sizeof(StringLiteralNode));
    node->value = strdup(value); // Duplica a string para que o nó tenha sua própria cópia
    if (!node->value) {
        perror("Erro ao duplicar string para StringLiteralNode");
        exit(EXIT_FAILURE);
    }
    return (AstNode*)node;
}

AstNode* create_identifier_node(char *name) {
    IdentifierNode* node = (IdentifierNode*)create_base_node(NODE_TYPE_IDENTIFIER, sizeof(IdentifierNode));
    node->name = strdup(name); // Duplica o nome do identificador
    if (!node->name) {
        perror("Erro ao duplicar nome para IdentifierNode");
        exit(EXIT_FAILURE);
    }
    return (AstNode*)node;
}

AstNode* create_assignment_node(AstNode *target, OperatorType op_type, AstNode *expression) {
    AssignmentNode* node = (AssignmentNode*)create_base_node(NODE_TYPE_ASSIGNMENT, sizeof(AssignmentNode));
    node->target = target;
    node->op_type = op_type;
    node->expression = expression;
    return (AstNode*)node;
}

AstNode* create_binary_op_node(AstNode *left, OperatorType op_type, AstNode *right) {
    BinaryOpNode* node = (BinaryOpNode*)create_base_node(NODE_TYPE_BINARY_OP, sizeof(BinaryOpNode));
    node->left = left;
    node->op_type = op_type;
    node->right = right;
    return (AstNode*)node;
}

AstNode* create_unary_op_node(OperatorType op_type, AstNode *operand) {
    UnaryOpNode* node = (UnaryOpNode*)create_base_node(NODE_TYPE_UNARY_OP, sizeof(UnaryOpNode));
    node->op_type = op_type;
    node->operand = operand;
    return (AstNode*)node;
}

AstNode* create_block_node(AstNodeList *statements) {
    BlockNode* node = (BlockNode*)create_base_node(NODE_TYPE_BLOCK, sizeof(BlockNode));
    node->statements = statements;
    return (AstNode*)node;
}

AstNode* create_while_node(AstNode* condition, AstNode* body) {
    WhileNode* node = (WhileNode*)create_base_node(NODE_TYPE_WHILE_LOOP, sizeof(WhileNode));
    node->condition = condition;
    node->body = body;
    return (AstNode*)node;
}

AstNode* create_for_node(AstNode *initializer, AstNode *condition, AstNode *increment, AstNode *body) {
    ForNode* node = (ForNode*)create_base_node(NODE_TYPE_FOR_LOOP, sizeof(ForNode));
    node->initializer = initializer;
    node->condition = condition;
    node->increment = increment;
    node->body = body;
    return (AstNode*)node;
}

AstNode* create_if_statement_node(AstNode *condition, AstNode *then_branch, AstNode *else_branch) {
    IfStatementNode* node = (IfStatementNode*)create_base_node(NODE_TYPE_IF_STATEMENT, sizeof(IfStatementNode));
    node->condition = condition;
    node->then_branch = then_branch;
    node->else_branch = else_branch;
    return (AstNode*)node;
}

AstNode* create_return_statement_node(AstNode *expression) {
    ReturnStatementNode* node = (ReturnStatementNode*)create_base_node(NODE_TYPE_RETURN_STATEMENT, sizeof(ReturnStatementNode));
    node->expression = expression;
    return (AstNode*)node;
}

AstNode* create_break_statement_node() {
    BreakStatementNode* node = (BreakStatementNode*)create_base_node(NODE_TYPE_BREAK_STATEMENT, sizeof(BreakStatementNode));
    return (AstNode*)node;
}

AstNode* create_printf_node(char *format_string, ArgumentNode *args) {
    PrintfNode* node = (PrintfNode*)create_base_node(NODE_TYPE_PRINTF_STATEMENT, sizeof(PrintfNode));
    node->format_string = strdup(format_string);
    if (!node->format_string) {
        perror("Erro ao duplicar format_string para PrintfNode");
        exit(EXIT_FAILURE);
    }
    node->args = args;
    return (AstNode*)node;
}

AstNode* create_printf_id_node(char *id_name) {
    PrintfIdNode* node = (PrintfIdNode*)create_base_node(NODE_TYPE_PRINTF_ID, sizeof(PrintfIdNode));
    node->id_name = strdup(id_name);
    if (!node->id_name) {
        perror("Erro ao duplicar id_name para PrintfIdNode");
        exit(EXIT_FAILURE);
    }
    return (AstNode*)node;
}

AstNode* create_input_node() {
    InputNode* node = (InputNode*)create_base_node(NODE_TYPE_INPUT, sizeof(InputNode));
    return (AstNode*)node;
}

AstNode* create_expression_statement_node(AstNode *expression) {
    ExpressionStatementNode* node = (ExpressionStatementNode*)create_base_node(NODE_TYPE_EXPRESSION_STATEMENT, sizeof(ExpressionStatementNode));
    node->expression = expression;
    return (AstNode*)node;
}

AstNode* create_array_literal_node(AstNodeList *elements) {
    ArrayLiteralNode* node = (ArrayLiteralNode*)create_base_node(NODE_TYPE_ARRAY_LITERAL, sizeof(ArrayLiteralNode));
    node->elements = elements;
    return (AstNode*)node;
}

AstNode* create_array_access_node(AstNode *array_name, AstNode *index_expression) {
    ArrayAccessNode* node = (ArrayAccessNode*)create_base_node(NODE_TYPE_ARRAY_ACCESS, sizeof(ArrayAccessNode));
    node->array_name = array_name;
    node->index_expression = index_expression;
    return (AstNode*)node;
}

AstNode* create_array_assignment_node(AstNode *array_access_node, AstNode *expression) {
    // Reutiliza o tipo AssignmentNode para atribuição a array,
    // pois o 'target' pode ser um ArrayAccessNode.
    AssignmentNode* node = (AssignmentNode*)create_base_node(NODE_TYPE_ASSIGNMENT, sizeof(AssignmentNode));
    node->target = array_access_node;
    node->op_type = OP_ASSIGNMENT; // Por padrão, atribuição simples para array
    node->expression = expression;
    return (AstNode*)node;
}

AstNode* create_function_declaration_node(char *name, AstNode *body) {
    FunctionDeclarationNode* node = (FunctionDeclarationNode*)create_base_node(NODE_TYPE_FUNCTION_DECL, sizeof(FunctionDeclarationNode));
    node->name = strdup(name);
    if (!node->name) {
        perror("Erro ao duplicar nome para FunctionDeclarationNode");
        exit(EXIT_FAILURE);
    }
    node->body = body;
    // TODO: Adicionar lógica para parâmetros aqui se forem mais complexos que apenas o nome.
    return (AstNode*)node;
}

AstNode* create_function_call_node(char *name, ArgumentNode *args) {
    FunctionCallNode* node = (FunctionCallNode*)create_base_node(NODE_TYPE_FUNCTION_CALL, sizeof(FunctionCallNode));
    node->name = strdup(name);
    if (!node->name) {
        perror("Erro ao duplicar nome para FunctionCallNode");
        exit(EXIT_FAILURE);
    }
    node->args = args;
    return (AstNode*)node;
}


// --- Funções para Manipulação de AstNodeList ---

AstNodeList* create_ast_node_list_from_node(AstNode *node) {
    AstNodeList* list = (AstNodeList*)malloc(sizeof(AstNodeList));
    if (!list) {
        perror("Erro de alocação de memória para AstNodeList");
        exit(EXIT_FAILURE);
    }
    list->count = 0;
    list->capacity = 4; // Capacidade inicial razoável
    list->nodes = (AstNode**)malloc(sizeof(AstNode*) * list->capacity);
    if (!list->nodes) {
        perror("Erro de alocação de memória para AstNodeList->nodes");
        free(list);
        exit(EXIT_FAILURE);
    }
    if (node) { // Adiciona o primeiro nó se fornecido
        list->nodes[list->count++] = node;
    }
    return list;
}

AstNodeList* append_to_ast_node_list(AstNodeList *list, AstNode *node) {
    if (!list) { // Se a lista for nula, cria uma nova com o nó
        return create_ast_node_list_from_node(node);
    }

    if (list->count == list->capacity) {
        // Redimensiona a lista se a capacidade for atingida
        list->capacity *= 2;
        list->nodes = (AstNode**)realloc(list->nodes, sizeof(AstNode*) * list->capacity);
        if (!list->nodes) {
            perror("Erro de realloc para AstNodeList->nodes");
            exit(EXIT_FAILURE);
        }
    }
    list->nodes[list->count++] = node; // Adiciona o nó e incrementa a contagem
    return list;
}

// --- Funções para Manipulação de ArgumentNode ---

ArgumentNode* create_argument_node(AstNode *arg_ast_node) {
    ArgumentNode* arg_node = (ArgumentNode*)malloc(sizeof(ArgumentNode));
    if (!arg_node) {
        perror("Erro de alocação de memória para ArgumentNode");
        exit(EXIT_FAILURE);
    }
    arg_node->node = arg_ast_node;
    arg_node->next = NULL;
    return arg_node;
}

void free_argument_list(ArgumentNode *list) {
    ArgumentNode *temp;
    while (list != NULL) {
        temp = list;
        // O nó da AST contido no ArgumentNode será liberado por free_ast()
        // quando o nó pai que contem a lista de argumentos for liberado.
        // Aqui, apenas liberamos o ArgumentNode em si.
        list = list->next;
        free(temp);
    }
}

// --- Função para Liberação de Memória da AST ---
// Esta função percorre a AST recursivamente e libera toda a memória alocada.
void free_ast(AstNode *node) {
    if (!node) return;

    // Acessa o tipo do nó através do campo 'base.type'
    switch (node->type) {
        case NODE_TYPE_INT_LITERAL:
        case NODE_TYPE_FLOAT_LITERAL:
        case NODE_TYPE_INPUT:
        case NODE_TYPE_BREAK_STATEMENT:
            // Esses nós não possuem sub-nós ou strings alocadas dinamicamente
            break; // Apenas liberamos o nó base no final
        case NODE_TYPE_STRING_LITERAL:
            free(((StringLiteralNode*)node)->value);
            break;
        case NODE_TYPE_IDENTIFIER:
            free(((IdentifierNode*)node)->name);
            break;
        case NODE_TYPE_ASSIGNMENT: {
            AssignmentNode* n = (AssignmentNode*)node;
            free_ast(n->target);
            free_ast(n->expression);
            break;
        }
        case NODE_TYPE_BINARY_OP: {
            BinaryOpNode* n = (BinaryOpNode*)node;
            free_ast(n->left);
            free_ast(n->right);
            break;
        }
        case NODE_TYPE_UNARY_OP: {
            UnaryOpNode* n = (UnaryOpNode*)node;
            free_ast(n->operand);
            break;
        }
        case NODE_TYPE_BLOCK: {
            BlockNode* n = (BlockNode*)node;
            if (n->statements) {
                for (int i = 0; i < n->statements->count; i++) {
                    free_ast(n->statements->nodes[i]); // Libera cada statement no bloco
                }
                free(n->statements->nodes); // Libera o array de ponteiros
                free(n->statements);        // Libera a estrutura AstNodeList
            }
            break;
        }
        case NODE_TYPE_WHILE_LOOP: {
            WhileNode* n = (WhileNode*)node;
            free_ast(n->condition);
            free_ast(n->body);
            break;
        }
        case NODE_TYPE_FOR_LOOP: {
            ForNode* n = (ForNode*)node;
            free_ast(n->initializer);
            free_ast(n->condition);
            free_ast(n->increment);
            free_ast(n->body);
            break;
        }
        case NODE_TYPE_IF_STATEMENT: {
            IfStatementNode* n = (IfStatementNode*)node;
            free_ast(n->condition);
            free_ast(n->then_branch);
            if (n->else_branch) { // else_branch é opcional
                free_ast(n->else_branch);
            }
            break;
        }
        case NODE_TYPE_RETURN_STATEMENT: {
            ReturnStatementNode* n = (ReturnStatementNode*)node;
            free_ast(n->expression);
            break;
        }
        case NODE_TYPE_PRINTF_STATEMENT: {
            PrintfNode* n = (PrintfNode*)node;
            free(n->format_string);
            // ArgumentNodes contêm AstNodes que devem ser liberados
            ArgumentNode *current_arg = n->args;
            while (current_arg) {
                ArgumentNode *temp_arg = current_arg;
                free_ast(temp_arg->node); // Libera o nó da AST do argumento
                current_arg = current_arg->next;
                free(temp_arg); // Libera a estrutura ArgumentNode
            }
            break;
        }
        case NODE_TYPE_PRINTF_ID: {
            PrintfIdNode* n = (PrintfIdNode*)node;
            free(n->id_name);
            break;
        }
        case NODE_TYPE_EXPRESSION_STATEMENT: {
            ExpressionStatementNode* n = (ExpressionStatementNode*)node;
            free_ast(n->expression);
            break;
        }
        case NODE_TYPE_ARRAY_LITERAL: {
            ArrayLiteralNode* n = (ArrayLiteralNode*)node;
            if (n->elements) {
                for (int i = 0; i < n->elements->count; i++) {
                    free_ast(n->elements->nodes[i]); // Libera cada elemento do array
                }
                free(n->elements->nodes);
                free(n->elements);
            }
            break;
        }
        case NODE_TYPE_ARRAY_ACCESS: {
            ArrayAccessNode* n = (ArrayAccessNode*)node;
            free_ast(n->array_name);
            free_ast(n->index_expression);
            break;
        }
        case NODE_TYPE_FUNCTION_DECL: {
            FunctionDeclarationNode* n = (FunctionDeclarationNode*)node;
            free(n->name);
            free_ast(n->body);
            // TODO: Liberar lista de parâmetros, se implementada
            break;
        }
        case NODE_TYPE_FUNCTION_CALL: {
            FunctionCallNode* n = (FunctionCallNode*)node;
            free(n->name);
            // ArgumentNodes contêm AstNodes que devem ser liberados
            ArgumentNode *current_arg = n->args;
            while (current_arg) {
                ArgumentNode *temp_arg = current_arg;
                free_ast(temp_arg->node); // Libera o nó da AST do argumento
                current_arg = current_arg->next;
                free(temp_arg); // Libera a estrutura ArgumentNode
            }
            break;
        }
        default:
            // Este caso de erro deve ser tratado: nó desconhecido
            fprintf(stderr, "Erro: free_ast não implementado para o tipo de nó desconhecido: %d (linha %d)\n", node->type, node->line_number);
            break;
    }
    free(node); // Libera a memória do próprio nó
}