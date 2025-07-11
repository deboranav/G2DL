%{
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "lib/types.h"
#include "lib/symbol_table.h"
#include "lib/ast.h"

int yylex(void);
void yyerror(const char *s);

// A raiz da nossa AST, preenchida pelo parser.
ASTNode* global_ast_root = NULL;

extern int yylineno;
extern FILE *yyin;
%}

%debug

%union {
    int       intVal;
    float     floatVal;
    char* strVal;     // Para tokens (ID, STRING_LITERAL)
    ASTNode* node;       // Para não-terminais da gramática
    TypeInfo* type_info;
}

/* --- Tokens --- */
%token FUNCTION RETURN BREAK IF ELSE WHILE FOR TRUE FALSE
%token INT STRING FLOAT 
%token MATRIX 
%token TYPE_DEF DOT
%token <strVal> ID STRING_LITERAL
%token <intVal> INTEGER
%token <floatVal> FLOAT_LITERAL
%token ASSIGNMENT PLUS MINUS MULTIPLY DIVIDE MOD POWER
%token EQUAL NOT_EQUAL LESS_THAN GREATER_THAN LESS_THAN_OR_EQUAL GREATER_THAN_OR_EQUAL
%token AND OR NOT
%token LEFT_PARENTHESIS RIGHT_PARENTHESIS LEFT_CURLY_BRACKET RIGHT_CURLY_BRACKET
%token LEFT_SQUARE_BRACKET RIGHT_SQUARE_BRACKET
%token COMMA COLON
%token PRINTF
%token INPUT
%token PLUS_ASSIGNMENT MINUS_ASSIGNMENT MULTIPLY_ASSIGNMENT DIVIDE_ASSIGNMENT MOD_ASSIGNMENT POWER_ASSIGNMENT

/* --- Tipos dos Não-Terminais --- */
%type <node> program statements statement block
%type <node> expression assignment variable control_structure 
%type <node> printf_statement argument_list function_call

/* --- Precedência e Associatividade --- */
%left OR
%left AND
%left EQUAL NOT_EQUAL
%left LESS_THAN GREATER_THAN LESS_THAN_OR_EQUAL GREATER_THAN_OR_EQUAL
%left PLUS MINUS
%left MULTIPLY DIVIDE MOD
%right POWER
%right NOT
%right UMINUS
%nonassoc THEN
%nonassoc ELSE

%start program

%%

/*==================================================================
 * GRAMÁTICA PRINCIPAL - CONSTRÓI A AST
 *==================================================================*/

program:
    statements { global_ast_root = $1; }
    ;

statements:
    /* vazio */ { $$ = NULL; }
    | statements statement { 
        if ($1 == NULL) {
            $$ = $2;
        } else if ($2 != NULL) {
            $$ = new_ast_node(AST_STATEMENT_LIST, $1, $2); 
        } else {
            $$ = $1;
        }
    }
    ;

statement:
    assignment ';'      { $$ = $1; }
    | expression ';'      { $$ = $1; } /* Uma expressão pode ser um statement, como uma chamada de função */
    | control_structure { $$ = $1; }
    | printf_statement  { $$ = $1; }
    | block             { $$ = $1; }
    | error ';'         { yyerrok; $$ = NULL; }
    ;

block:
    LEFT_CURLY_BRACKET { scope_enter(); } statements RIGHT_CURLY_BRACKET { scope_leave(); $$ = $3; }
    ;

/*==================================================================
 * ESTRUTURAS DE CONTROLE
 *==================================================================*/

control_structure:
    IF LEFT_PARENTHESIS expression RIGHT_PARENTHESIS block
    {
        $$ = new_ast_if_node($3, $5, NULL); /* else é NULL */
    }
    | IF LEFT_PARENTHESIS expression RIGHT_PARENTHESIS block ELSE statement
    {
        $$ = new_ast_if_node($3, $5, $7);
    }
    | WHILE LEFT_PARENTHESIS expression RIGHT_PARENTHESIS block
    {
        $$ = new_ast_node(AST_WHILE, $3, $5);
    }
    ;

/*==================================================================
 * ATRIBUIÇÕES E EXPRESSÕES
 *==================================================================*/

assignment:
    variable ASSIGNMENT expression
    {
        // A variável é um nó de identificador. Precisamos do seu nome.
        if (scope_lookup($1->value.strVal) == NULL) {
            scope_add_symbol($1->value.strVal, TYPE_FLOAT, NULL, 0, 0);
        }
        $$ = new_ast_node(AST_ASSIGN, $1, $3);
    }
    ;

expression:
    INTEGER              { $$ = new_ast_leaf_number((double)$1); }
    | FLOAT_LITERAL      { $$ = new_ast_leaf_number($1); }
    | STRING_LITERAL     { $$ = new_ast_leaf_string($1); }
    | variable           { $$ = $1; }
    | function_call      { $$ = $1; }
    | TRUE               { $$ = new_ast_leaf_number(1.0); }
    | FALSE              { $$ = new_ast_leaf_number(0.0); }
    | INPUT LEFT_PARENTHESIS RIGHT_PARENTHESIS { $$ = new_ast_node(AST_INPUT, NULL, NULL); }
    | LEFT_PARENTHESIS expression RIGHT_PARENTHESIS { $$ = $2; }
    | MINUS expression %prec UMINUS               { $$ = new_ast_node(AST_UMINUS, $2, NULL); }
    | NOT expression                              { $$ = new_ast_node(AST_NOT, $2, NULL); }
    | expression PLUS expression                  { $$ = new_ast_node(AST_ADD, $1, $3); }
    | expression MINUS expression                 { $$ = new_ast_node(AST_SUB, $1, $3); }
    | expression MULTIPLY expression              { $$ = new_ast_node(AST_MUL, $1, $3); }
    | expression DIVIDE expression                { $$ = new_ast_node(AST_DIV, $1, $3); }
    | expression EQUAL expression                 { $$ = new_ast_node(AST_EQ, $1, $3); }
    | expression NOT_EQUAL expression             { $$ = new_ast_node(AST_NEQ, $1, $3); }
    | expression LESS_THAN expression             { $$ = new_ast_node(AST_LT, $1, $3); }
    | expression GREATER_THAN expression          { $$ = new_ast_node(AST_GT, $1, $3); }
    | expression LESS_THAN_OR_EQUAL expression    { $$ = new_ast_node(AST_LTE, $1, $3); }
    | expression GREATER_THAN_OR_EQUAL expression { $$ = new_ast_node(AST_GTE, $1, $3); }
    | expression AND expression                   { $$ = new_ast_node(AST_AND, $1, $3); }
    | expression OR expression                    { $$ = new_ast_node(AST_OR, $1, $3); }
    ;

variable:
    ID { $$ = new_ast_leaf_id($1); }
    ;

/*==================================================================
 * FUNÇÕES E CHAMADAS
 *==================================================================*/

printf_statement:
    PRINTF LEFT_PARENTHESIS STRING_LITERAL RIGHT_PARENTHESIS ';'
    {
        $$ = new_ast_node(AST_PRINTF, new_ast_leaf_string($3), NULL);
    }
    | PRINTF LEFT_PARENTHESIS STRING_LITERAL COMMA argument_list RIGHT_PARENTHESIS ';'
    {
        $$ = new_ast_node(AST_PRINTF, new_ast_leaf_string($3), $5);
    }
    ;
    
function_call:
    ID LEFT_PARENTHESIS argument_list RIGHT_PARENTHESIS
    {
        // O ID vira um nó folha, e a lista de argumentos é o filho direito
        $$ = new_ast_node(AST_FUNC_CALL, new_ast_leaf_id($1), $3);
    }
    ;

argument_list:
    /* vazio */ { $$ = NULL; }
    | expression { $$ = $1; } /* Uma lista de 1 argumento é só o próprio nó */
    | argument_list COMMA expression { $$ = new_ast_node(AST_STATEMENT_LIST, $1, $3); } /* Reutilizando o nó de lista */
    ;

%%

/*==================================================================
 * SEÇÃO DE CÓDIGO C AUXILIAR
 *==================================================================*/

// Função de Geração de Código (a ser criada em codegen.c)
void generate_code(ASTNode* node); 

void yyerror(const char *msg) {
    fprintf(stderr, "Erro na linha %d: %s\n", yylineno, msg);
}

int main(int argc, char *argv[]) {
    #if YYDEBUG
        yydebug = 1;
    #endif

    if (argc > 1) { 
        yyin = fopen(argv[1], "r"); 
        if (!yyin) { perror(argv[1]); return 1; } 
    } else { 
        yyin = stdin; 
    }

    scope_init();
    
    int result = yyparse();

    if (result == 0 && global_ast_root != NULL) {
        printf("/* Tradução para C iniciada */\n");
        
        // A mágica acontece aqui: A AST é passada para o gerador de código
        generate_code(global_ast_root);
        
        printf("/* Tradução concluída com sucesso. */\n");

        free_ast(global_ast_root); // Libera a memória da AST

    } else {
        printf("A tradução falhou devido a erros de sintaxe.\n");
    }

    if (yyin != stdin) fclose(yyin);
    free_all_scopes();

    return result;
}