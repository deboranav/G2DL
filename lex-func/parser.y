%{
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>

  int yylex(void);
  void yyerror(const char *s) {
    fprintf(stderr, "Erro de sintaxe: %s\n", s);
  }
%}

%union {
  int ival;
  float fval;
  char *sval;
}

%token <sval> ID STRING
%token <ival> INTEGER
%token <fval> FLOAT

%token IF ELSE ELSEIF WHILE FOR FUNCTION RETURN BREAK
%token TRUE FALSE
%token INT_TYPE FLOAT_TYPE STRING_TYPE

%token PLUS_ASSIGN MINUS_ASSIGN POWER_ASSIGN MULT_ASSIGN DIV_ASSIGN MOD_ASSIGN
%token EQ NEQ LE GE ASSIGN LT GT
%token POWER PLUS MINUS MULT DIV MOD
%token AND OR NOT
%token LBRACKET RBRACKET LPAREN RPAREN LBRACE RBRACE
%token COMMA COLON
%token NEWLINE
%token ERROR

%start programa

%%

programa:
    lista_comandos
;

lista_comandos:
    lista_comandos comando
  | lista_comandos NEWLINE
  | comando
;

comando:
    atribuicao NEWLINE
  | comando_controle NEWLINE
  | chamada_funcao NEWLINE
  | RETURN expressao NEWLINE
  | BREAK NEWLINE
;

declaracao_funcao:
    FUNCTION ID LPAREN parametros RPAREN LBRACE lista_comandos RBRACE
;

parametros:
    lista_parametros
  | /* vazio */
;

lista_parametros:
    tipo ID
  | lista_parametros COMMA tipo ID
;

tipo:
    INT_TYPE
  | FLOAT_TYPE
  | STRING_TYPE
;

atribuicao:
    ID ASSIGN expressao
  | ID PLUS_ASSIGN expressao
  | ID MINUS_ASSIGN expressao
  | ID MULT_ASSIGN expressao
  | ID DIV_ASSIGN expressao
  | ID POWER_ASSIGN expressao
  | ID MOD_ASSIGN expressao
;

comando_controle:
    IF LPAREN expressao RPAREN LBRACE lista_comandos RBRACE
  | IF LPAREN expressao RPAREN LBRACE lista_comandos RBRACE ELSE LBRACE lista_comandos RBRACE
  | WHILE LPAREN expressao RPAREN LBRACE lista_comandos RBRACE
  | FOR LPAREN atribuicao NEWLINE expressao NEWLINE atribuicao RPAREN LBRACE lista_comandos RBRACE
;

chamada_funcao:
    ID LPAREN argumentos RPAREN NEWLINE
;

argumentos:
    lista_argumentos
  | /* vazio */
;

lista_argumentos:
    expressao
  | lista_argumentos COMMA expressao
;

expressao:
    expressao PLUS expressao
  | expressao MINUS expressao
  | expressao MULT expressao
  | expressao DIV expressao
  | expressao MOD expressao
  | expressao POWER expressao
  | expressao EQ expressao
  | expressao NEQ expressao
  | expressao LT expressao
  | expressao LE
