#include "interpreter.h" // Inclui a definição da função execute_ast
#include "ast.h"
#include "symbol_table.h" // Para acessar a tabela de símbolos
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> // Para pow()

// Variáveis externas do lexer/parser
extern int yylineno; // Para mensagens de erro de runtime
void yyerror(const char *msg); // Função de erro do parser (ou runtime, se centralizada)

// Implementação da função principal do interpretador
RuntimeValue execute_ast(AstNode *node) {
    if (!node) {
        return (RuntimeValue){.type = TYPE_VOID}; // Retorna um tipo "vazio" para nós nulos
    }

    RuntimeValue result; // Para armazenar o resultado da execução de um nó
    result.type = TYPE_VOID; // Valor padrão, pode ser sobrescrito

    switch (node->type) {
        case NODE_TYPE_INT_LITERAL: {
            IntLiteralNode *int_node = (IntLiteralNode*)node;
            return (RuntimeValue){.type = TYPE_INT, .data.intVal = int_node->value};
        }
        case NODE_TYPE_FLOAT_LITERAL: {
            FloatLiteralNode *float_node = (FloatLiteralNode*)node;
            return (RuntimeValue){.type = TYPE_FLOAT, .data.floatVal = float_node->value};
        }
        case NODE_TYPE_STRING_LITERAL: {
            StringLiteralNode *string_node = (StringLiteralNode*)node;
            // Retorna uma cópia da string para que o literal original não seja modificado ou liberado prematuramente
            return (RuntimeValue){.type = TYPE_STRING, .data.strVal = strdup(string_node->value)};
        }
        case NODE_TYPE_VARIABLE_ACCESS: {
            IdentifierNode *id_node = (IdentifierNode*)node;
            Symbol *sym = lookup_symbol(id_node->name);
            if (sym != NULL) {
                // Retorna uma cópia da string se for string, para evitar problemas de memória
                if (sym->value.type == TYPE_STRING && sym->value.data.strVal) {
                    return (RuntimeValue){.type = TYPE_STRING, .data.strVal = strdup(sym->value.data.strVal)};
                }
                return sym->value;
            } else {
                fprintf(stderr, "Erro de runtime na linha %d: Variável '%s' não definida.\n", yylineno, id_node->name);
                exit(EXIT_FAILURE);
            }
        }
        case NODE_TYPE_ASSIGNMENT: {
            AssignmentNode *assign_node = (AssignmentNode*)node;
            RuntimeValue expr_val = execute_ast(assign_node->expression);

            // Se for uma string, garanta que a tabela de símbolos receba uma cópia
            if (expr_val.type == TYPE_STRING && expr_val.data.strVal) {
                 // insert_symbol irá fazer strdup internamente, então liberamos a cópia temporária
                insert_symbol(assign_node->variable_name, expr_val);
                free(expr_val.data.strVal); // Libera a cópia temporária feita por execute_ast do literal/variável
            } else {
                insert_symbol(assign_node->variable_name, expr_val);
            }
            // Para operadores de atribuição compostos (+=, -=, etc.), você precisaria
            // primeiro buscar o valor atual da variável, aplicar a operação
            // e depois chamar insert_symbol com o novo valor.
            // Para simplificar, esta implementação assume apenas '='.

            return (RuntimeValue){.type = TYPE_VOID}; // Atribuições geralmente não retornam valor
        }
        case NODE_TYPE_BINARY_OP: {
            BinaryOpNode *bin_op_node = (BinaryOpNode*)node;
            RuntimeValue left_val = execute_ast(bin_op_node->left);
            RuntimeValue right_val = execute_ast(bin_op_node->right);

            // Lógica de concatenação de strings (apenas para '+')
            if (bin_op_node->op_type == OP_PLUS &&
                (left_val.type == TYPE_STRING || right_val.type == TYPE_STRING)) {
                if (left_val.type == TYPE_STRING && right_val.type == TYPE_STRING) {
                    char *new_str = malloc(strlen(left_val.data.strVal) + strlen(right_val.data.strVal) + 1);
                    if (!new_str) { perror("malloc"); exit(EXIT_FAILURE); }
                    strcpy(new_str, left_val.data.strVal);
                    strcat(new_str, right_val.data.strVal);
                    // Liberar as strings temporárias dos operandos
                    if (left_val.data.strVal) free(left_val.data.strVal);
                    if (right_val.data.strVal) free(right_val.data.strVal);
                    return (RuntimeValue){.type = TYPE_STRING, .data.strVal = new_str};
                } else {
                    fprintf(stderr, "Erro de runtime na linha %d: Concatenação de string exige dois operandos do tipo STRING.\n", yylineno);
                    // Libere quaisquer strings temporárias antes de sair
                    if (left_val.type == TYPE_STRING && left_val.data.strVal) free(left_val.data.strVal);
                    if (right_val.type == TYPE_STRING && right_val.data.strVal) free(right_val.data.strVal);
                    exit(EXIT_FAILURE);
                }
            }

            // Para operações numéricas, promove para float se um dos operandos for float
            float val1 = (left_val.type == TYPE_INT) ? (float)left_val.data.intVal : left_val.data.floatVal;
            float val2 = (right_val.type == TYPE_INT) ? (float)right_val.data.intVal : right_val.data.floatVal;

            // Libera strings se não foram usadas na concatenação (evita memory leaks)
            if (left_val.type == TYPE_STRING && left_val.data.strVal) free(left_val.data.strVal);
            if (right_val.type == TYPE_STRING && right_val.data.strVal) free(right_val.data.strVal);

            switch (bin_op_node->op_type) {
                case OP_PLUS:       return (RuntimeValue){.type = TYPE_FLOAT, .data.floatVal = val1 + val2};
                case OP_MINUS:      return (RuntimeValue){.type = TYPE_FLOAT, .data.floatVal = val1 - val2};
                case OP_MULTIPLY:   return (RuntimeValue){.type = TYPE_FLOAT, .data.floatVal = val1 * val2};
                case OP_DIVIDE:
                    if (val2 == 0.0f) {
                        fprintf(stderr, "Erro de runtime na linha %d: Divisão por zero.\n", yylineno);
                        exit(EXIT_FAILURE);
                    }
                    return (RuntimeValue){.type = TYPE_FLOAT, .data.floatVal = val1 / val2};
                case OP_MOD: { // Módulo opera apenas em inteiros
                    int i_val1 = (int)val1;
                    int i_val2 = (int)val2;
                    if (i_val2 == 0) {
                        fprintf(stderr, "Erro de runtime na linha %d: Módulo por zero.\n", yylineno);
                        exit(EXIT_FAILURE);
                    }
                    return (RuntimeValue){.type = TYPE_INT, .data.intVal = i_val1 % i_val2};
                }
                case OP_POWER:      return (RuntimeValue){.type = TYPE_FLOAT, .data.floatVal = pow(val1, val2)};

                // Operações de comparação (retornam INT como booleano)
                case OP_EQUAL:              return (RuntimeValue){.type = TYPE_INT, .data.intVal = (val1 == val2)};
                case OP_NOT_EQUAL:          return (RuntimeValue){.type = TYPE_INT, .data.intVal = (val1 != val2)};
                case OP_LESS_THAN:          return (RuntimeValue){.type = TYPE_INT, .data.intVal = (val1 < val2)};
                case OP_GREATER_THAN:       return (RuntimeValue){.type = TYPE_INT, .data.intVal = (val1 > val2)};
                case OP_LESS_THAN_OR_EQUAL: return (RuntimeValue){.type = TYPE_INT, .data.intVal = (val1 <= val2)};
                case OP_GREATER_THAN_OR_EQUAL: return (RuntimeValue){.type = TYPE_INT, .data.intVal = (val1 >= val2)};

                // Operações lógicas (operam em inteiros, 0 é falso, !=0 é verdadeiro)
                case OP_AND: return (RuntimeValue){.type = TYPE_INT, .data.intVal = ((int)val1 && (int)val2)};
                case OP_OR:  return (RuntimeValue){.type = TYPE_INT, .data.intVal = ((int)val1 || (int)val2)};

                default:
                    fprintf(stderr, "Erro de runtime na linha %d: Operador binário desconhecido na AST: %d.\n", yylineno, bin_op_node->op_type);
                    exit(EXIT_FAILURE);
            }
        }
        case NODE_TYPE_UNARY_OP: {
            UnaryOpNode *un_op_node = (UnaryOpNode*)node;
            RuntimeValue operand_val = execute_ast(un_op_node->operand);

            int val = 0;
            if (operand_val.type == TYPE_INT) {
                val = operand_val.data.intVal;
            } else if (operand_val.type == TYPE_FLOAT) {
                val = (int)operand_val.data.floatVal;
            } else {
                fprintf(stderr, "Erro de runtime na linha %d: Operador unário esperado INT/FLOAT, recebido tipo %d.\n", yylineno, operand_val.type);
                // Libere strings temporárias se houver
                if (operand_val.type == TYPE_STRING && operand_val.data.strVal) free(operand_val.data.strVal);
                exit(EXIT_FAILURE);
            }

            if (operand_val.type == TYPE_STRING && operand_val.data.strVal) free(operand_val.data.strVal);

            switch (un_op_node->op_type) {
                case OP_NOT: return (RuntimeValue){.type = TYPE_INT, .data.intVal = !val};
                default:
                    fprintf(stderr, "Erro de runtime na linha %d: Operador unário desconhecido na AST: %d.\n", yylineno, un_op_node->op_type);
                    exit(EXIT_FAILURE);
            }
        }
        case NODE_TYPE_BLOCK: {
            BlockNode *block_node = (BlockNode*)node;
            for (int i = 0; i < block_node->num_statements; i++) {
                RuntimeValue stmt_result = execute_ast(block_node->statements[i]);
                // Se um statement dentro do bloco retornou um valor, propaga esse retorno
                // (útil para `return` em funções ou `break` em loops)
                if (stmt_result.type == TYPE_RETURN_VALUE || stmt_result.type == TYPE_BREAK) {
                    return stmt_result; // Propaga o sinal de retorno/break
                }
                // Libera strings retornadas por expressões que não são armazenadas
                if (stmt_result.type == TYPE_STRING && stmt_result.data.strVal) {
                    free(stmt_result.data.strVal);
                }
            }
            return (RuntimeValue){.type = TYPE_VOID};
        }
        case NODE_TYPE_WHILE: {
            WhileNode *while_node = (WhileNode*)node;
            while (1) {
                RuntimeValue cond_val = execute_ast(while_node->condition);

                int condition_true = 0;
                if (cond_val.type == TYPE_INT) {
                    condition_true = cond_val.data.intVal != 0;
                } else if (cond_val.type == TYPE_FLOAT) {
                    condition_true = cond_val.data.floatVal != 0.0f;
                } else {
                    fprintf(stderr, "Erro de runtime na linha %d: Condição do WHILE não é booleana (INT/FLOAT).\n", yylineno);
                    // Libera strings temporárias se houver
                    if (cond_val.type == TYPE_STRING && cond_val.data.strVal) free(cond_val.data.strVal);
                    exit(EXIT_FAILURE);
                }
                // Libera o valor da condição se for uma string (ou qualquer valor temporário)
                if (cond_val.type == TYPE_STRING && cond_val.data.strVal) free(cond_val.data.strVal);

                if (!condition_true) {
                    break; // Sai do loop WHILE
                }

                RuntimeValue body_result = execute_ast(while_node->body);
                // Lidar com `break` ou `return` dentro do loop
                if (body_result.type == TYPE_BREAK) { // Supondo que você define TYPE_BREAK em types.h
                    if (body_result.type == TYPE_STRING && body_result.data.strVal) free(body_result.data.strVal);
                    break;
                }
                if (body_result.type == TYPE_RETURN_VALUE) {
                    return body_result; // Propaga o retorno
                }
                // Libera strings temporárias do resultado do corpo
                if (body_result.type == TYPE_STRING && body_result.data.strVal) free(body_result.data.strVal);
            }
            return (RuntimeValue){.type = TYPE_VOID};
        }
        case NODE_TYPE_IF: {
            IfNode *if_node = (IfNode*)node;
            RuntimeValue cond_val = execute_ast(if_node->condition);

            int condition_true = 0;
            if (cond_val.type == TYPE_INT) {
                condition_true = cond_val.data.intVal != 0;
            } else if (cond_val.type == TYPE_FLOAT) {
                condition_true = cond_val.data.floatVal != 0.0f;
            } else {
                fprintf(stderr, "Erro de runtime na linha %d: Condição do IF não é booleana (INT/FLOAT).\n", yylineno);
                if (cond_val.type == TYPE_STRING && cond_val.data.strVal) free(cond_val.data.strVal);
                exit(EXIT_FAILURE);
            }
            if (cond_val.type == TYPE_STRING && cond_val.data.strVal) free(cond_val.data.strVal);


            if (condition_true) {
                result = execute_ast(if_node->then_block);
            } else if (if_node->else_block) {
                result = execute_ast(if_node->else_block);
            }
            // Propaga qualquer return/break vindo dos blocos IF/ELSE
            if (result.type == TYPE_RETURN_VALUE || result.type == TYPE_BREAK) {
                return result;
            }
            if (result.type == TYPE_STRING && result.data.strVal) free(result.data.strVal);
            return (RuntimeValue){.type = TYPE_VOID};
        }
        case NODE_TYPE_RETURN: {
            ReturnNode *ret_node = (ReturnNode*)node;
            RuntimeValue ret_val = execute_ast(ret_node->expression);
            // Retorna um tipo especial para sinalizar um "return" e o valor associado
            return (RuntimeValue){.type = TYPE_RETURN_VALUE, .data = ret_val.data, .sub_type = ret_val.type};
        }
        case NODE_TYPE_PRINTF: {
            PrintfNode *printf_node = (PrintfNode*)node;
            // Executa cada expressão na lista de argumentos para obter seus valores de runtime
            ArgumentNode *current_arg_ast_node = printf_node->args;
            ArgumentNode *runtime_args_list_head = NULL;
            ArgumentNode *runtime_args_list_tail = NULL;

            while (current_arg_ast_node != NULL) {
                // A estrutura ArgumentNode armazena um AstNode* no campo value.data.nodeVal
                // (você precisará ajustar o `ArgumentNode` em `types.h` para isso,
                // ou o parser.y para criar diretamente RuntimeValues aqui)
                // A suposição é que ArgumentNode.value.data.nodeVal é um AstNode*
                // e que ArgumentNode.value.type é TYPE_AST_NODE.
                // Se seu parser já avalia expressões para printf diretamente,
                // você pode simplificar essa parte.

                // Assumindo que o `argument_list_printf` no `.y` já avalia as expressões e as coloca em `ArgumentNode`:
                // Se não, você precisaria: `RuntimeValue arg_val = execute_ast(current_arg_ast_node->value.data.nodeVal);`
                // e então copiar `arg_val` para um novo `ArgumentNode`.
                // A maneira como seu `.y` está agora, ele já coloca `RuntimeValue` diretamente.
                // Então, podemos pegar o valor diretamente, mas precisamos COPIAR strings.

                ArgumentNode *new_runtime_arg = (ArgumentNode*)malloc(sizeof(ArgumentNode));
                if (!new_runtime_arg) { perror("malloc"); exit(EXIT_FAILURE); }
                new_runtime_arg->next = NULL;

                RuntimeValue source_val = current_arg_ast_node->value; // Valor já avaliado pelo parser
                if (source_val.type == TYPE_STRING && source_val.data.strVal) {
                    new_runtime_arg->value = (RuntimeValue){.type = TYPE_STRING, .data.strVal = strdup(source_val.data.strVal)};
                } else {
                    new_runtime_arg->value = source_val;
                }

                if (runtime_args_list_head == NULL) {
                    runtime_args_list_head = new_runtime_arg;
                    runtime_args_list_tail = new_runtime_arg;
                } else {
                    runtime_args_list_tail->next = new_runtime_arg;
                    runtime_args_list_tail = new_runtime_arg;
                }
                current_arg_ast_node = current_arg_ast_node->next;
            }

            my_printf_runtime(printf_node->format_string, runtime_args_list_head);
            free_argument_list(runtime_args_list_head); // Libera a lista temporária de argumentos

            // O formato string do printf_node deve ser liberado pela função free_ast
            // assim como o próprio printf_node.
            return (RuntimeValue){.type = TYPE_VOID};
        }
        case NODE_TYPE_PRINTF_ID: {
            PrintfIdNode *printf_id_node = (PrintfIdNode*)node;
            Symbol *sym = lookup_symbol(printf_id_node->id_name);
            if (sym != NULL) {
                char *temp_format = NULL;
                ArgumentNode *arg_list_temp = (ArgumentNode*)malloc(sizeof(ArgumentNode));
                if (!arg_list_temp) { perror("malloc"); exit(EXIT_FAILURE); }
                arg_list_temp->next = NULL;

                RuntimeValue sym_val_copy;
                if (sym->value.type == TYPE_STRING && sym->value.data.strVal) {
                    sym_val_copy = (RuntimeValue){.type = TYPE_STRING, .data.strVal = strdup(sym->value.data.strVal)};
                } else {
                    sym_val_copy = sym->value;
                }
                arg_list_temp->value = sym_val_copy;

                if (sym_val_copy.type == TYPE_INT) {
                    temp_format = strdup("%d\n");
                } else if (sym_val_copy.type == TYPE_FLOAT) {
                    temp_format = strdup("%f\n");
                } else if (sym_val_copy.type == TYPE_STRING) {
                    temp_format = strdup("%s\n");
                } else {
                    fprintf(stderr, "Erro de runtime na linha %d: printf(ID) com tipo de variável não suportado: %d.\n", yylineno, sym_val_copy.type);
                    temp_format = strdup("Tipo desconhecido para ID.\n"); // Fallback
                }

                if (temp_format) {
                    my_printf_runtime(temp_format, arg_list_temp);
                    free(temp_format);
                }
                free_argument_list(arg_list_temp); // Libera a lista e a cópia da string dentro dela
            } else {
                fprintf(stderr, "Erro de runtime na linha %d: Variável '%s' não definida para printf.\n", yylineno, printf_id_node->id_name);
                exit(EXIT_FAILURE);
            }
            return (RuntimeValue){.type = TYPE_VOID};
        }
        case NODE_TYPE_INPUT: {
            return runtime_input();
        }
        case NODE_TYPE_EXPRESSION_STATEMENT: {
            ExpressionStatementNode *expr_stmt_node = (ExpressionStatementNode*)node;
            RuntimeValue expr_val = execute_ast(expr_stmt_node->expression);
            // Libera qualquer string temporária retornada pela expressão, já que não está sendo usada
            if (expr_val.type == TYPE_STRING && expr_val.data.strVal) {
                free(expr_val.data.strVal);
            }
            return (RuntimeValue){.type = TYPE_VOID};
        }
        // ... adicione outros casos para FOR, FUNCTION_DECL, FUNCTION_CALL, ARRAY_ACCESS, etc.
        // Se você tiver um "break" statement, ele retornaria um tipo especial `TYPE_BREAK`.

        default:
            fprintf(stderr, "Erro de runtime na linha %d: Tipo de nó AST desconhecido ou não implementado: %d.\n", yylineno, node->type);
            exit(EXIT_FAILURE);
    }
}

// --- Funções de Runtime (originalmente do seu .y) ---

void my_printf_runtime(char *format_string, ArgumentNode *args_list) {
    char *p = format_string;
    ArgumentNode *current_arg = args_list;

    // Remove aspas de strings