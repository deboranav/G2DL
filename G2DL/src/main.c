// src/main.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Para strdup, etc.
#include <math.h>   // Se precisar de funções matemáticas em tempo de execução
#include <stdarg.h> // Para printf personalizado, se necessário

// Inclua os cabeçalhos das suas próprias bibliotecas/módulos
#include "utils/types.h"          // Para RuntimeValue, OperatorType, etc.
#include "ast/ast.h"            // Para AstNode, funções de criação, free_ast
#include "interpreter/symbol_table.h" // Para a tabela de símbolos (presumindo essa localização)
#include "interpreter/interpreter.h" // Para execute_ast (presumindo essa localização)
// Para o parser, que contém yyparse() e o lexer, que contém yylex()
// O arquivo gerado pelo Bison normalmente é chamado de parser.tab.h ou parser.h
// Você deve incluir o .h que Bison gera para as definições de token e yysymbol_kind_t
#include "parser/parser.h"      // Inclui parser.h (gerado por Bison)
// O lexer.h se você tiver protótipos de funções do lexer lá, mas yylex já é externo.
// #include "lexer/lexer.h"

// --- Variáveis Externas (definidas pelo Flex/Bison) ---
extern int yylex(void);       // Função do lexer (definida em lexer.c)
extern void yyerror(const char *s); // Função de erro do parser (você a implementa)
extern int yylineno;          // Número da linha atual (definida pelo Flex)
extern FILE *yyin;            // Ponteiro para o arquivo de entrada (definido pelo Flex)

// --- Variáveis Globais (se necessário para a AST) ---
// Esta variável global será preenchida pelo parser.y
// Certifique-se de que yyparse() preencha esta variável global quando a AST for construída.
// No seu .y, você já tem: AstNode *program_root_ast_node = NULL;
// Declare-a aqui como 'extern' para que main.c possa acessá-la.
extern AstNode *program_root_ast_node;

// --- Função Principal ---
int main(int argc, char *argv[]) {
    // Habilita o modo debug do Bison, se a macro YYDEBUG estiver definida (ex: em Makefile)
    #if YYDEBUG
        yydebug = 1;
    #endif

    // Inicializa a tabela de símbolos (assumindo que esta função está em symbol_table.c)
    init_symbol_table();

    // --- Leitura do Arquivo de Entrada ---
    if (argc > 1) {
        FILE *file = fopen(argv[1], "r");
        if (!file) {
            perror(argv[1]); // Imprime erro se o arquivo não puder ser aberto
            return 1; // Retorna com código de erro
        }
        yyin = file; // Redireciona a entrada do lexer para o arquivo
    } else {
        yyin = stdin; // Se nenhum arquivo for fornecido, lê da entrada padrão
    }

    // --- Análise Sintática (Parsing) ---
    // Chama a função yyparse() gerada pelo Bison
    printf("Iniciando análise sintática...\n");
    if (yyparse() == 0) { // yyparse() retorna 0 em caso de sucesso
        printf("Análise sintática concluída com sucesso. AST construída.\n");

        // --- Execução da AST ---
        if (program_root_ast_node) {
            printf("\nIniciando execução da AST...\n");
            // A função execute_ast() deve ser implementada em interpreter.c
            // Ela percorre a AST e executa as operações
            RuntimeValue final_result = execute_ast(program_root_ast_node);
            printf("Execução da AST finalizada.\n");

            // --- Exemplo de Impressão do Resultado Final (Opcional) ---
            // Se o seu programa principal puder "retornar" um valor, você pode imprimi-lo.
            // Lembre-se de que a liberação de RuntimeValue.data.strVal é importante!
            if (final_result.type != TYPE_VOID && final_result.type != TYPE_NULL) {
                printf("Resultado final do programa: ");
                switch (final_result.type) {
                    case TYPE_INT:
                        printf("%d\n", final_result.data.intVal);
                        break;
                    case TYPE_FLOAT:
                        printf("%f\n", final_result.data.floatVal);
                        break;
                    case TYPE_STRING:
                        if (final_result.data.strVal) {
                            printf("%s\n", final_result.data.strVal);
                            free(final_result.data.strVal); // Libere a string se ela foi alocada dinamicamente
                        } else {
                            printf("(string nula)\n");
                        }
                        break;
                    case TYPE_BOOLEAN:
                        printf("%s\n", final_result.data.boolVal ? "true" : "false");
                        break;
                    // TODO: Adicionar casos para TYPE_ARRAY, etc., se você quiser imprimir o resultado de um programa que retorna um array.
                    default:
                        printf("(Tipo de resultado final não imprimível)\n");
                        break;
                }
            }
            // --- Liberação da Memória da AST ---
            // É crucial liberar a AST após a execução para evitar vazamentos de memória.
            free_ast(program_root_ast_node);
        } else {
            printf("Nenhuma AST foi construída (programa vazio ou erro inicial).\n");
        }
        
        // Se abriu um arquivo, feche-o
        if (yyin != stdin) {
            fclose(yyin);
        }
        return 0; // Saída bem-sucedida
    } else {
        printf("Análise sintática falhou. Não foi possível construir ou executar a AST.\n");
        // Se a análise falhou, a AST pode estar incompleta ou inválida,
        // então não tentamos executá-la ou liberá-la.
        
        // Se abriu um arquivo, feche-o
        if (yyin != stdin) {
            fclose(yyin);
        }
        return 1; // Saída com erro
    }

    // Libera a memória da tabela de símbolos (assumindo que esta função está em symbol_table.c)
    // Coloque esta chamada aqui para garantir que a tabela seja liberada,
    // mesmo que a execução da AST não aconteça (e.g., por erro de parsing).
    free_symbol_table_memory(); 

    // Este return não será alcançado, pois os branches acima já retornam.
    return 0;
}

// --- Implementação da Função de Erro do Parser ---
// Esta função é chamada pelo Bison quando um erro de sintaxe é encontrado.
// É importante para dar feedback ao usuário sobre o erro.
void yyerror(const char *msg) {
    fprintf(stderr, "Erro de sintaxe na linha %d: %s\n", yylineno, msg);
}