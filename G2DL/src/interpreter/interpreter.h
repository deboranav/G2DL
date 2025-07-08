#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "ast/ast.h"
#include "utils/types.h"

// Declara a função principal do interpretador.
// Ela recebe o nó raiz da AST e inicia a execução.
RuntimeValue execute_ast(AstNode *node);

// Declara as funções de runtime que estavam embutidas no .y
// ou que são chamadas pela execução da AST.
void my_printf_runtime(char *format_string, ArgumentNode *args_list);
void free_argument_list(ArgumentNode *list);
RuntimeValue runtime_input();

#endif // INTERPRETER_H