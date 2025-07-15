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
%token COMMA COLON SEMICOLON
%token PRINTF
%token INPUT
%token PLUS_ASSIGNMENT MINUS_ASSIGNMENT MULTIPLY_ASSIGNMENT DIVIDE_ASSIGNMENT MOD_ASSIGNMENT POWER_ASSIGNMENT

/* --- Tipos dos Não-Terminais --- */
%type <node> program top_level_declarations top_level_declaration
%type <node> function_declaration type_definition variable_declaration
%type <node> statements statement block
%type <node> expression assignment variable control_structure 
%type <node> printf_statement argument_list function_call
%type <node> matrix_declaration matrix_access
%type <node> type_specifier param_list parameter return_statement

/* --- Precedência e Associatividade --- */
%left OR
%left AND
%left EQUAL NOT_EQUAL
%left LESS_THAN GREATER_THAN LESS_THAN_OR_EQUAL GREATER_THAN_OR_EQUAL
%left PLUS MINUS
%left MULTIPLY DIVIDE MOD
%left DOT
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
    top_level_declarations { global_ast_root = $1; }
    ;

top_level_declarations:
    /* vazio */ { $$ = NULL; }
    | top_level_declarations top_level_declaration {
        if ($1 == NULL) { $$ = $2; }
        else { $$ = new_ast_node(AST_STATEMENT_LIST, $1, $2); }
    }
    ;

top_level_declaration:
    function_declaration { $$ = $1; }
    | type_definition    { $$ = $1; }
    | statement          { $$ = $1; } // Para printf's globais
    ;

/*==================================================================
 * DEFINIÇÕES DE TIPOS E FUNÇÕES
 *==================================================================*/

type_definition:
    TYPE_DEF ID LEFT_CURLY_BRACKET statements RIGHT_CURLY_BRACKET SEMICOLON {
        $$ = new_ast_type_def_node(new_ast_leaf_id($2), $4);
    }
    ;

function_declaration:
    FUNCTION type_specifier ID LEFT_PARENTHESIS param_list RIGHT_PARENTHESIS block {
        $$ = new_ast_func_def_node($2, new_ast_leaf_id($3), $5, $7);
    }
    ;

param_list:
    /* vazio */ { $$ = NULL; }
    | parameter { $$ = $1; }
    | param_list COMMA parameter { $$ = new_ast_node(AST_PARAM_LIST, $1, $3); }
    ;

parameter:
    type_specifier ID { $$ = new_ast_param_node($1, new_ast_leaf_id($2)); }
    ;

/*==================================================================
 * STATEMENTS E BLOCOS
 *==================================================================*/

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
    expression ';'           { $$ = $1; }
    | assignment ';'           { $$ = $1; } 
    | variable_declaration ';' { $$ = $1; }
    | matrix_declaration ';'   { $$ = $1; }
    | printf_statement       { $$ = $1; }
    | return_statement ';'     { $$ = $1; }
    | control_structure      { $$ = $1; }
    | block                  { $$ = $1; }
    | error SEMICOLON        { yyerrok; $$ = NULL; }
    ;

return_statement:
    RETURN expression { $$ = new_ast_node(AST_RETURN, $2, NULL); }
    ;

variable_declaration:
    type_specifier ID { $$ = new_ast_var_decl_node($1, new_ast_leaf_id($2)); }
    ;

type_specifier:
    FLOAT { $$ = new_ast_leaf_type("float"); }
    | ID    { $$ = new_ast_leaf_type($1); } // Para tipos como rational_t
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
    | expression POWER expression                 { $$ = new_ast_node(AST_POW, $1, $3); }
    | expression AND expression                   { $$ = new_ast_node(AST_AND, $1, $3); }
    | expression OR expression                    { $$ = new_ast_node(AST_OR, $1, $3); }
    ;

variable:
    ID { $$ = new_ast_leaf_id($1); }
    | matrix_access { $$ = $1; }
    | variable DOT ID { $$ = new_ast_node(AST_MEMBER_ACCESS, $1, new_ast_leaf_id($3)); }
    ;

matrix_declaration:
    MATRIX ID LEFT_SQUARE_BRACKET expression COMMA expression RIGHT_SQUARE_BRACKET
    {
        $$ = new_ast_matrix_decl_node($2, $4, $6);
    }
    ;

matrix_access:
    ID LEFT_SQUARE_BRACKET expression COMMA expression RIGHT_SQUARE_BRACKET
    {
        $$ = new_ast_matrix_access_node($1, $3, $5);
    }
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
    | expression { $$ = $1; }
    | argument_list COMMA expression { $$ = new_ast_node(AST_ARG_LIST, $1, $3); } 
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
        printf("/* Analise semantica iniciada... */\n");

        //print_ast(global_ast_root); caso necessario
    
        // PASSO 1: Análise Semântica
        analyze_semantics(global_ast_root);
    
        printf("/* Analise semantica concluida. */\n");
        printf("/* Tradução para C iniciada */\n");

        // PASSO 2: Geração de Código
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