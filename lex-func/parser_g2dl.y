%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Protótipos
int yylex(void);
void yyerror(const char *s);

// Variáveis globais do Flex
extern int yylineno;
extern FILE *yyin; // <<-- CORREÇÃO: Declarar yyin aqui

%}

%debug

%union {
    int intVal;
    float floatVal;
    char *strVal;
}

%token FUNCTION RETURN BREAK IF ELSE ELSE_IF WHILE FOR TRUE FALSE
%token INT STRING FLOAT
%token <strVal> ID STRING_LITERAL
%token <intVal> INTEGER
%token <floatVal> FLOAT_LITERAL
%token ASSIGNMENT PLUS MINUS MULTIPLY DIVIDE MOD POWER
%token EQUAL NOT_EQUAL LESS_THAN GREATER_THAN LESS_THAN_OR_EQUAL GREATER_THAN_OR_EQUAL
%token AND OR NOT
%token PLUS_ASSIGNMENT MINUS_ASSIGNMENT MULTIPLY_ASSIGNMENT DIVIDE_ASSIGNMENT MOD_ASSIGNMENT POWER_ASSIGNMENT
%token LEFT_PARENTHESIS RIGHT_PARENTHESIS LEFT_CURLY_BRACKET RIGHT_CURLY_BRACKET
%token LEFT_SQUARE_BRACKET RIGHT_SQUARE_BRACKET
%token COMMA COLON
%token PRINTF

%type <floatVal> expression
%type <strVal> variable

%nonassoc THEN
%nonassoc ELSE
%right ASSIGNMENT
%left OR
%left AND
%left EQUAL NOT_EQUAL
%left LESS_THAN GREATER_THAN LESS_THAN_OR_EQUAL GREATER_THAN_OR_EQUAL
%left PLUS MINUS
%left MULTIPLY DIVIDE MOD
%right POWER
%right NOT

%start program

%%

program:
    statements
    | /* um programa pode ser vazio */
    ;

statements:
    statement
    | statements statement
    ;

statement:
    function_decl
    | assignment ';'
    | expression ';'    { printf("Resultado da expressão: %f\n", $1); }
    | control_structure
    | RETURN expression ';' { printf("Retornando valor %f\n", $2); }
    | function_call ';'
    | printf_statement
    | block
    | error ';' { fprintf(stderr, "Erro de sintaxe. Tentando recuperar em ';'\n"); yyerrok; }
    ;

printf_statement:
    PRINTF LEFT_PARENTHESIS argument_list RIGHT_PARENTHESIS ';'
    ;

function_decl:
    FUNCTION ID LEFT_PARENTHESIS parameters RIGHT_PARENTHESIS block
    ;

parameters:
    /* vazio */
    | parameter_list
    ;

parameter_list:
    ID
    | parameter_list COMMA ID
    ;

block:
    LEFT_CURLY_BRACKET statements RIGHT_CURLY_BRACKET
    ;

assignment:
    variable ASSIGNMENT expression { printf("Atribuição para a variável %s\n", $1); free($1); }
    | array_access ASSIGNMENT expression
    ;

expression:
    INTEGER                     { $$ = $1; }
    | FLOAT_LITERAL             { $$ = $1; }
    | variable                  { /* Busca na tabela de símbolos */ printf("Usando variável %s\n", $1); free($1); $$ = 0.0; }
    | function_call             { $$ = 0.0; }
    | array_access              { $$ = 0.0; }
    | TRUE                      { $$ = 1.0; }
    | FALSE                     { $$ = 0.0; }
    | expression PLUS expression        { $$ = $1 + $3; }
    | expression MINUS expression       { $$ = $1 - $3; }
    | expression MULTIPLY expression    { $$ = $1 * $3; }
    | expression DIVIDE expression      { if($3 != 0) $$ = $1 / $3; else yyerror("Divisão por zero"); }
    | expression MOD expression         { $$ = (float)((int)$1 % (int)$3); }
    | expression POWER expression       { $$ = pow($1, $3); }
    | expression EQUAL expression       { $$ = ($1 == $3); }
    | expression NOT_EQUAL expression   { $$ = ($1 != $3); }
    | expression LESS_THAN expression   { $$ = ($1 < $3); }
    | expression GREATER_THAN expression { $$ = ($1 > $3); }
    | expression LESS_THAN_OR_EQUAL expression { $$ = ($1 <= $3); }
    | expression GREATER_THAN_OR_EQUAL expression { $$ = ($1 >= $3); }
    | expression AND expression         { $$ = ($1 && $3); }
    | expression OR expression          { $$ = ($1 || $3); }
    | NOT expression                    { $$ = !$2; }
    | LEFT_PARENTHESIS expression RIGHT_PARENTHESIS { $$ = $2; }
    ;

variable:
    ID { $$ = $1; }
    ;

array_access:
    ID LEFT_SQUARE_BRACKET expression RIGHT_SQUARE_BRACKET
    ;

function_call:
    ID LEFT_PARENTHESIS argument_list RIGHT_PARENTHESIS
    ;


argument_list:
    /* vazio */
    | arguments
    ;

arguments:
    expression
    | arguments COMMA expression
    ;

control_structure:
    IF expression block %prec THEN
    | IF expression block ELSE block
    | ELSE_IF expression block
    | WHILE expression block
    | FOR LEFT_PARENTHESIS INT ID COLON function_call RIGHT_PARENTHESIS block
    ;

%%

void yyerror(const char *msg) {
    fprintf(stderr, "Erro na linha %d: %s\n", yylineno, msg);
}

int main(int argc, char *argv[]) {
    #if YYDEBUG
        yydebug = 1;
    #endif

    if (argc > 1) {
        FILE *file = fopen(argv[1], "r");
        if (!file) {
            perror(argv[1]);
            return 1;
        }
        yyin = file;
    } else {
        yyin = stdin;
    }

    if (yyparse() == 0) {
        printf("Análise concluída com sucesso.\n");
        return 0;
    } else {
        printf("Análise falhou.\n");
        return 1;
    }
}