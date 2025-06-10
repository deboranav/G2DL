%{
#include <stdio.h>
#include <stdlib.h>

int yylex();
void yyerror(const char *msg) { fprintf(stderr, "Erro: %s\n", msg); }
%}

%union {
    int intVal;
    float floatVal;
    char *strVal;
}

%token FUNCTION RETURN BREAK IF ELSE WHILE FOR TRUE FALSE
%token INT STRING
%token <strVal> ID STRING_LITERAL
%token <intVal> INTEGER
%token <floatVal> FLOAT
%token ASSIGNMENT PLUS MINUS MULTIPLY DIVIDE MOD POWER
%token EQUAL NOT_EQUAL LESS_THAN GREATER_THAN LESS_THAN_OR_EQUAL GREATER_THAN_OR_EQUAL
%token AND OR NOT
%token PLUS_ASSIGNMENT MINUS_ASSIGNMENT MULTIPLY_ASSIGNMENT DIVIDE_ASSIGNMENT MOD_ASSIGNMENT POWER_ASSIGNMENT
%token LEFT_PARENTHESIS RIGHT_PARENTHESIS LEFT_CURLY_BRACKET RIGHT_CURLY_BRACKET
%token LEFT_SQUARE_BRACKET RIGHT_SQUARE_BRACKET
%token COMMA COLON

%left OR
%left AND
%left EQUAL NOT_EQUAL
%left LESS_THAN GREATER_THAN LESS_THAN_OR_EQUAL GREATER_THAN_OR_EQUAL
%left PLUS MINUS
%left MULTIPLY DIVIDE MOD
%right POWER
%right NOT

%%

program:
    statements
    ;

statements:
    statements statement
    | /* vazio */
    ;

statement:
    function_decl
    | assignment
    | expression
    | control_structure
    | RETURN expression
    | function_call
    ;

function_decl:
    FUNCTION ID LEFT_PARENTHESIS parameters RIGHT_PARENTHESIS block
    ;

parameters:
    parameter_list
    | /* vazio */
    ;

parameter_list:
    parameter
    | parameter_list COMMA parameter
    ;

parameter:
    ID
    ;

block:
    LEFT_CURLY_BRACKET statements RIGHT_CURLY_BRACKET
    ;

assignment:
    ID ASSIGNMENT expression
    | array_access ASSIGNMENT expression
    ;

expression:
    expression PLUS expression
    | expression MINUS expression
    | expression MULTIPLY expression
    | expression DIVIDE expression
    | expression MOD expression
    | expression POWER expression
    | expression EQUAL expression
    | expression NOT_EQUAL expression
    | expression LESS_THAN expression
    | expression GREATER_THAN expression
    | expression LESS_THAN_OR_EQUAL expression
    | expression GREATER_THAN_OR_EQUAL expression
    | expression AND expression
    | expression OR expression
    | NOT expression
    | atom
    ;

atom:
      literal
    | variable
    | array_access
    | grouped_expression
    ;

grouped_expression:
    LEFT_PARENTHESIS expression RIGHT_PARENTHESIS
    ;

literal:
      INTEGER
    | FLOAT
    | STRING_LITERAL
    | TRUE
    | FALSE
    ;

variable:
    ID
    ;

array_access:
    ID LEFT_SQUARE_BRACKET expression RIGHT_SQUARE_BRACKET
    ;

function_call:
    ID LEFT_PARENTHESIS argument_list RIGHT_PARENTHESIS
    ;

argument_list:
    arguments
    | /* vazio */
    ;

arguments:
    expression
    | arguments COMMA expression
    ;

control_structure:
    IF expression block
    | IF expression block ELSE block
    | WHILE expression block
    | FOR LEFT_PARENTHESIS INT ID COLON function_call RIGHT_PARENTHESIS block
    ;

%%

int yydebug = 1;

int main() {
    return yyparse();
}
