%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "utils/types.h"
#include "ast/ast.h"
#include "interpreter/symbol_table.h"

extern int yylex(void);
extern int yylineno;
extern FILE *yyin;

AstNode *program_root_ast_node = NULL;

void yyerror(const char *s);
%}

%debug

%union {
    int intVal;
    float floatVal;
    char *strVal;
    RuntimeValue runtimeVal;
    ArgumentNode *argList;
    struct AstNode *node;
    struct AstNodeList *nodeList;
}

%token FUNCTION RETURN BREAK IF ELSE WHILE FOR TRUE FALSE
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
%token INPUT

%type <node> expression_node
%type <node> statement
%type <nodeList> statements
%type <node> block
%type <node> control_structure
%type <node> assignment
%type <node> printf_statement
%type <node> return_statement
%type <argList> argument_list_printf_ast
%type <node> variable_access_node
%type <node> function_call_node
%type <node> array_access_node
%type <node> array_literal_node

%left OR
%left AND
%left EQUAL NOT_EQUAL
%left LESS_THAN GREATER_THAN LESS_THAN_OR_EQUAL GREATER_THAN_OR_EQUAL
%left PLUS MINUS
%left MULTIPLY DIVIDE MOD
%right POWER
%right NOT
%nonassoc THEN
%nonassoc ELSE

%start program

%%

program:
    statements { program_root_ast_node = create_block_node($1); }
    | /* vazio */ { program_root_ast_node = create_block_node(NULL); }
    ;

statements:
    statement { $$ = create_ast_node_list_from_node($1); }
    | statements statement { $$ = append_to_ast_node_list($1, $2); }
    ;

statement:
    function_decl
    | assignment ';' { $$ = $1; }
    | expression_node ';' { $$ = create_expression_statement_node($1); }
    | control_structure { $$ = $1; }
    | return_statement { $$ = $1; }
    | printf_statement { $$ = $1; }
    | block { $$ = $1; }
    | BREAK ';' { $$ = create_break_statement_node(); }
    | error ';' { fprintf(stderr, "Erro de sintaxe na linha %d: Token inesperado. Tentando recuperar em ';'\n", yylineno); yyerrok; $$ = NULL; }
    ;

printf_statement:
    PRINTF LEFT_PARENTHESIS STRING_LITERAL COMMA argument_list_printf_ast RIGHT_PARENTHESIS ';'
    {
        $$ = create_printf_node($3, $5);
    }
    | PRINTF LEFT_PARENTHESIS STRING_LITERAL RIGHT_PARENTHESIS ';'
    {
        $$ = create_printf_node($3, NULL);
    }
    | PRINTF LEFT_PARENTHESIS ID RIGHT_PARENTHESIS ';'
    {
        $$ = create_printf_id_node($3);
    }
    ;

argument_list_printf_ast:
    expression_node { $$ = create_argument_node($1); }
    | argument_list_printf_ast COMMA expression_node {
        ArgumentNode *newNode = create_argument_node($3);
        ArgumentNode *current = $1;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
        $$ = $1;
    }
    ;

function_decl:
    FUNCTION ID LEFT_PARENTHESIS parameters RIGHT_PARENTHESIS block
    {
        $$ = create_function_declaration_node($2, $6);
    }
    ;

parameters:
    /* vazio */ { $$ = NULL; }
    | parameter_list { }
    ;

parameter_list:
    ID { }
    | parameter_list COMMA ID { }
    ;

block:
    LEFT_CURLY_BRACKET statements RIGHT_CURLY_BRACKET { $$ = create_block_node($2); }
    | LEFT_CURLY_BRACKET RIGHT_CURLY_BRACKET { $$ = create_block_node(NULL); }
    ;

assignment:
    variable_access_node ASSIGNMENT expression_node {
        $$ = create_assignment_node($1, OP_ASSIGNMENT, $3);
    }
    | variable_access_node PLUS_ASSIGNMENT expression_node { $$ = create_assignment_node($1, OP_PLUS_ASSIGNMENT, $3); }
    | variable_access_node MINUS_ASSIGNMENT expression_node { $$ = create_assignment_node($1, OP_MINUS_ASSIGNMENT, $3); }
    | variable_access_node MULTIPLY_ASSIGNMENT expression_node { $$ = create_assignment_node($1, OP_MULTIPLY_ASSIGNMENT, $3); }
    | variable_access_node DIVIDE_ASSIGNMENT expression_node { $$ = create_assignment_node($1, OP_DIVIDE_ASSIGNMENT, $3); }
    | variable_access_node MOD_ASSIGNMENT expression_node { $$ = create_assignment_node($1, OP_MOD_ASSIGNMENT, $3); }
    | variable_access_node POWER_ASSIGNMENT expression_node { $$ = create_assignment_node($1, OP_POWER_ASSIGNMENT, $3); }
    | array_access_node ASSIGNMENT expression_node {
        $$ = create_array_assignment_node($1, $3);
    }
    ;

expression_node:
    INTEGER { $$ = create_int_literal_node($1); }
    | FLOAT_LITERAL { $$ = create_float_literal_node($1); }
    | STRING_LITERAL { $$ = create_string_literal_node($1); }
    | variable_access_node { $$ = $1; }
    | function_call_node { $$ = $1; }
    | array_access_node { $$ = $1; }
    | array_literal_node { $$ = $1; }
    | TRUE { $$ = create_int_literal_node(1); }
    | FALSE { $$ = create_int_literal_node(0); }
    | INPUT LEFT_PARENTHESIS RIGHT_PARENTHESIS {
        $$ = create_input_node();
    }
    | expression_node PLUS expression_node { $$ = create_binary_op_node($1, OP_PLUS, $3); }
    | expression_node MINUS expression_node { $$ = create_binary_op_node($1, OP_MINUS, $3); }
    | expression_node MULTIPLY expression_node { $$ = create_binary_op_node($1, OP_MULTIPLY, $3); }
    | expression_node DIVIDE expression_node { $$ = create_binary_op_node($1, OP_DIVIDE, $3); }
    | expression_node MOD expression_node { $$ = create_binary_op_node($1, OP_MOD, $3); }
    | expression_node POWER expression_node { $$ = create_binary_op_node($1, OP_POWER, $3); }
    | expression_node EQUAL expression_node { $$ = create_binary_op_node($1, OP_EQUAL, $3); }
    | expression_node NOT_EQUAL expression_node { $$ = create_binary_op_node($1, OP_NOT_EQUAL, $3); }
    | expression_node LESS_THAN expression_node { $$ = create_binary_op_node($1, OP_LESS_THAN, $3); }
    | expression_node GREATER_THAN expression_node { $$ = create_binary_op_node($1, OP_GREATER_THAN, $3); }
    | expression_node LESS_THAN_OR_EQUAL expression_node { $$ = create_binary_op_node($1, OP_LESS_THAN_OR_EQUAL, $3); }
    | expression_node GREATER_THAN_OR_EQUAL expression_node { $$ = create_binary_op_node($1, OP_GREATER_THAN_OR_EQUAL, $3); }
    | expression_node AND expression_node { $$ = create_binary_op_node($1, OP_AND, $3); }
    | expression_node OR expression_node { $$ = create_binary_op_node($1, OP_OR, $3); }
    | NOT expression_node { $$ = create_unary_op_node(OP_NOT, $2); }
    | LEFT_PARENTHESIS expression_node RIGHT_PARENTHESIS { $$ = $2; }
    ;

array_literal_node:
    LEFT_SQUARE_BRACKET array_elements_non_empty RIGHT_SQUARE_BRACKET { $$ = create_array_literal_node($2); }
    | LEFT_SQUARE_BRACKET RIGHT_SQUARE_BRACKET { $$ = create_array_literal_node(NULL); }
    ;

array_elements_non_empty:
    expression_node { $$ = create_ast_node_list_from_node($1); }
    | array_elements_non_empty COMMA expression_node { $$ = append_to_ast_node_list($1, $3); }
    ;

variable_access_node:
    ID { $$ = create_identifier_node($1); }
    ;

array_access_node:
    ID LEFT_SQUARE_BRACKET expression_node RIGHT_SQUARE_BRACKET { $$ = create_array_access_node(create_identifier_node($1), $3); }
    ;

function_call_node:
    ID LEFT_PARENTHESIS argument_list RIGHT_PARENTHESIS { $$ = create_function_call_node($1, $3); }
    ;

argument_list:
    /* vazio */ { $$ = NULL; }
    | argument_list_non_empty { $$ = $1; }
    ;

argument_list_non_empty:
    expression_node { $$ = create_argument_node($1); }
    | argument_list_non_empty COMMA expression_node {
        ArgumentNode *newNode = create_argument_node($3);
        ArgumentNode *current = $1;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
        $$ = $1;
    }
    ;

control_structure:
    IF expression_node block %prec THEN { $$ = create_if_statement_node($1, $2, NULL); }
    | IF expression_node block ELSE block { $$ = create_if_statement_node($1, $2, $4); }
    | WHILE expression_node block { $$ = create_while_node($1, $2); }
    | FOR LEFT_PARENTHESIS assignment ';' expression_node ';' assignment RIGHT_PARENTHESIS block
    {
        $$ = create_for_node($3, $5, $7, $9);
    }
    ;

return_statement:
    RETURN expression_node ';' { $$ = create_return_statement_node($2); }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Erro de sintaxe na linha %d: %s\n", yylineno, s);
}