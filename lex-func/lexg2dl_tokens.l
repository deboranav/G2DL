%{
#include "y.tab.h"
#include <stdio.h>
#include <stdlib.h>
%}

%option noyywrap

%%

"else if"                  { return ELSE; }
"if"                       { return IF; }
"else"                     { return ELSE; }
"while"                    { return WHILE; }
"for"                      { return FOR; }
"function"                 { return FUNCTION; }
"return"                   { return RETURN; }
"break"                    { return BREAK; }
"true"                     { return TRUE; }
"false"                    { return FALSE; }

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

"int"                      { return INT; }
"float"                    { return FLOAT; }
"string"                   { return STRING; }

[0-9]+\.[0-9]+             { yylval.floatVal = atof(yytext); return FLOAT; }
[0-9]+                     { yylval.intVal = atoi(yytext); return INTEGER; }

\"([^\\\"]|\\.)*\"         { yylval.strVal = strdup(yytext); return STRING_LITERAL; }
\'([^\\\']|\\.)*\'         { yylval.strVal = strdup(yytext); return STRING_LITERAL; }

[_a-zA-Z][_a-zA-Z0-9]*     { yylval.strVal = strdup(yytext); return ID; }

"//".*                     ;  // Ignorar comentário de linha
\/\*([^*]|\*+[^*/])*\*+\/  ;  // Ignorar comentário de bloco

[ \t\r\n]+                 ;  // Ignora espaços e quebras de linha

.                          { printf("Caractere inválido: %s\n", yytext); }

%%

