%{
  #include <stdio.h>  
%}

%option noyywrap

%%

"else if"                                       {printf("ELSE IF\n");}
"if"                                            {printf("IF\n");}
"else"                                          {printf("ELSE\n");}
"while"                                         {printf("WHILE\n");}
"for"                                           {printf("FOR\n");}
"function"                                      {printf("FUNCTION\n");}
"return"                                        {printf("RETURN\n");}
"break"                                         {printf("BREAK\n");}
"true"                                          {printf("TRUE\n");}
"false"                                         {printf("FALSE\n");}

"\+\="                                          {printf("PLUS ASSIGNMENT\n");}
"\-\="                                          {printf("MINUS ASSIGNMENT\n");}
"\*\*="                                         {printf("POWER ASSIGNMENT\n");}
"\*\="                                          {printf("MULTIPLY ASSIGNMENT\n");}
"\/\="                                          {printf("DIVIDE ASSIGNMENT\n");}
"%="                                            {printf("MOD ASSIGNMENT\n");}

"=="                                            {printf("EQUAL\n");}
"!="                                            {printf("NOT EQUAL\n");}
"<="                                            {printf("LESS THAN OR EQUAL TO\n");}
">="                                            {printf("GREATER THAN OR EQUAL TO\n");}
"="                                             {printf("ASSIGNMENT\n");}
"<"                                             {printf("LESS THAN\n");}
">"                                             {printf("GREATER THAN\n");}

"\*\*"                                          {printf("POWER\n");}
"\+"                                            {printf("PLUS\n");}
"\-"                                            {printf("MINUS\n");}
"\*"                                            {printf("MULTIPLY\n");}
"\/"                                            {printf("DIVIDE\n");}
"%"                                             {printf("MOD\n");}

"&&"                                            {printf("AND\n");}
"\|\|"                                          {printf("OR\n");}
"!"                                             {printf("NOT\n");}

"\["                                            {printf("LEFT SQUARE BRACKET\n");}
"\]"                                            {printf("RIGHT SQUARE BRACKET\n");}
"\("                                            {printf("LEFT PARENTHESIS\n");}
"\)"                                            {printf("RIGHT PARENTHESIS\n");}
"\{"                                            {printf("LEFT CURLY BRACKET\n");}
"\}"                                            {printf("RIGHT CURLY BRACKET\n");}

","                                             {printf("COMMA\n");}
":"                                             {printf("COLON\n");}

"int"                                           {printf("INT\n");}
"float"                                         {printf("FLOAT\n");}
"string"                                        {printf("STRING\n");}

[0-9]+\.[0-9]+                                  {printf("FLOAT(%s)\n",yytext);}
[0-9]+                                          {printf("INTEGER(%s)\n",yytext);}
[_a-zA-Z][_a-zA-Z0-9]*                          {printf("ID(%s)\n",yytext);}

\"([^\\\"]|\\.)*\"                              {printf("STRING(%s)\n",yytext);}
\'([^\\\']|\\.)*\'                              {printf("STRING(%s)\n",yytext);}

"//".*\n                                        {printf("LINE COMMENT (%s)\n", yytext);}
\/\*([^*]|\*+[^*/])*\*+\/                       {printf("BLOCK COMMENT(%s)\n", yytext);}


\n                                              { printf("NEW LINE\n"); }
[ \t\r]+                                      ;  // ignora espaços e quebras de linha
.                                               {printf("Invalid character: %s\n", yytext);}

%%

int main(void)
{
  yylex();  
  return 0;
}
