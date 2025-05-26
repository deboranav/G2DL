%{
  #include <stdio.h>
  #include <string.h>
  #include <stdlib.h>
%}

%option noyywrap
%option yylineno

%%

"else if"                                       { return ELSEIF; }
"if"                                            { return IF; }
"else"                                          { return ELSE; }
"while"                                         { return WHILE; }
"for"                                           { return FOR; }
"function"                                      { return FUNCTION; }
"return"                                        { return RETURN; }
"break"                                         { return BREAK; }
"true"                                          { return TRUE; }
"false"                                         { return FALSE; }

"\+\="                                          { return PLUS_ASSIGN; }
"\-\="                                          { return MINUS_ASSIGN; }
"\*\*="                                         { return POWER_ASSIGN; }
"\*\="                                          { return MULT_ASSIGN; }
"\/\="                                          { return DIV_ASSIGN; }
"%="                                            { return MOD_ASSIGN; }

"=="                                            { return EQ; }
"!="                                            { return NEQ; }
"<="                                            { return LE; }
">="                                            { return GE; }
"="                                             { return ASSIGN; }
"<"                                             { return LT; }
">"                                             { return GT; }

"\*\*"                                          { return POWER; }
"\+"                                            { return PLUS; }
"\-"                                            { return MINUS; }
"\*"                                            { return MULT; }
"\/"                                            { return DIV; }
"%"                                             { return MOD; }

"&&"                                            { return AND; }
"\|\|"                                          { return OR; }
"!"                                             { return NOT; }

"\["                                            { return LBRACKET; }
"\]"                                            { return RBRACKET; }
"\("                                            { return LPAREN; }
"\)"                                            { return RPAREN; }
"\{"                                            { return LBRACE; }
"\}"                                            { return RBRACE; }

","                                             { return COMMA; }
":"                                             { return COLON; }

"int"                                           { return INT_TYPE; }
"float"                                         { return FLOAT_TYPE; }
"string"                                        { return STRING_TYPE; }

[0-9]+\.[0-9]+                                  { yylval.fval = atof(yytext); return FLOAT; }
[0-9]+                                          { yylval.ival = atoi(yytext); return INTEGER; }
[_a-zA-Z][_a-zA-Z0-9]*                          { yylval.sval = strdup(yytext); return ID; }

\"([^\\\"]|\\.)*\"                              { yylval.sval = strdup(yytext); return STRING; }
\'([^\\\']|\\.)*\'                              { yylval.sval = strdup(yytext); return STRING; }

"//".*                                          { /* ignorar comentário de linha */ }
\/\*([^*]|\*+[^*/])*\*+\/                       { /* ignorar comentário de bloco */ }

\n                                              { return NEWLINE; }
[ \t\r]+                                      ;  // ignora espaços e quebras de linha

.                                               { printf("Caractere inválido: %s\n", yytext); return ERROR; }

%%

#ifndef yywrap
   int yywrap (void) {return 1;}
#endif