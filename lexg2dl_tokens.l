%{
#include "types.h"
#include "symbol_table.h"
#include "parser_g2dl.tab.h" 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
%}

%option yylineno
%option noyywrap

%%

#define YY_USER_ACTION printf("TOKEN: %s\n", yytext);

"if"                       { return IF; }
"else"                     { return ELSE; }
"while"                    { return WHILE; }
"for"                      { return FOR; }
"function"                 { return FUNCTION; }
"return"                   { return RETURN; }
"break"                    { return BREAK; }
"true"                     { return TRUE; }
"false"                    { return FALSE; }
"printf"                   { return PRINTF; }
"input"                    { return INPUT ; }

"+="                       { return PLUS_ASSIGNMENT; }
"-="                       { return MINUS_ASSIGNMENT; }
"**="                      { return POWER_ASSIGNMENT; }
"*="                       { return MULTIPLY_ASSIGNMENT; }
"/="                       { return DIVIDE_ASSIGNMENT; }
"%="                       { return MOD_ASSIGNMENT; }

"=="                       { return EQUAL; }
"!="                       { return NOT_EQUAL; }
"<="                       { return LESS_THAN_OR_EQUAL; }
">="                       { return GREATER_THAN_OR_EQUAL; }
"="                        { return ASSIGNMENT; }
"<"                        { return LESS_THAN; }
">"                        { return GREATER_THAN; }

"**"                       { return POWER; }
"+"                        { return PLUS; }
"-"                        { return MINUS; }
"*"                        { return MULTIPLY; }
"/"                        { return DIVIDE; }
"%"                        { return MOD; }

"&&"                       { return AND; }
"||"                       { return OR; }
"!"                        { return NOT; }

"["                      { return LEFT_SQUARE_BRACKET; }
"]"                      { return RIGHT_SQUARE_BRACKET; }
"("                      { return LEFT_PARENTHESIS; }
")"                      { return RIGHT_PARENTHESIS; }
"{"                      { return LEFT_CURLY_BRACKET; }
"}"                      { return RIGHT_CURLY_BRACKET; }

","                        { return COMMA; }
":"                        { return COLON; }
";"                        { return ';'; }


"int"                      { return INT; }
"float"                    { return FLOAT; }
"string"                   { return STRING; }

[0-9]+\.[0-9]+             { yylval.floatVal = atof(yytext); return FLOAT_LITERAL; }
[0-9]+                     { yylval.intVal = atoi(yytext); return INTEGER; }

\"([^\\\"]|\\.)*\"         { yylval.strVal = strdup(yytext); return STRING_LITERAL; }
\'([^\\\']|\\.)*\'         { yylval.strVal = strdup(yytext); return STRING_LITERAL; }

[_a-zA-Z][_a-zA-Z0-9]*     { yylval.strVal = strdup(yytext); return ID; }

"//".*                     ;  // Ignorar comentário de linha
\/\*([^*]|\*+[^*/])*\*+\/  ;  // Ignorar comentário de bloco

[ \t\r\n]+                 ;  // Ignora espaços e quebras de linha

.                          { printf("Caractere inválido: %s\n", yytext); }

%%

