%{
  #include <stdio.h>  
%}

%%

"if"                                            {printf("IF\n");}
"else if"                                       {printf("ELSE IF\n");}
"else"                                          {printf("ELSE\n");}
"while"                                         {printf("WHILE\n");}
"for"                                           {printf("FOR\n");}
"function"                                      {printf("FUNCTION\n");}
"="                                             {printf("ASSIGNMENT\n");}
"+="                                            {printf("PLUS ASSIGNMENT\n");}
"-="                                            {printf("MINUS ASSIGNMENT\n");}
"*="                                            {printf("MULTIPLY ASSIGNMENT\n");}
"/="                                            {printf("DIVIDE ASSIGNMENT\n");}
"**="                                           {printf("POWER ASSIGNMENT\n");}
"%="                                            {printf("MOD ASSIGNMENT\n");}
"=="                                            {printf("EQUAL\n");}
"!="                                            {printf("NOT EQUAL\n");}
"<"                                             {printf("LESS THAN\n");}
">"                                             {printf("GREATER THAN\n");}
"<="                                            {printf("LESS THAN OR EQUAL TO\n");}
">="                                            {printf("GREATER THAN OR EQUAL TO\n");}
"+"                                             {printf("PLUS\n");}
"-"                                             {printf("MINUS\n");}
"*"                                             {printf("MULTIPLY\n");}
"/"                                             {printf("DIVIDE\n");}
"**"                                            {printf("POWER\n");}
"%"                                             {printf("MOD\n");}
"&&"                                            {printf("AND\n");}
"||"                                            {printf("OR\n");}
"!"                                             {printf("NOT\n");}
"["                                             {printf("LEFT SQUARE BRACKET\n");}
"]"                                             {printf("RIGHT SQUARE BRACKET\n");}
"("                                             {printf("LEFT PARENTHESIS\n");}
")"                                             {printf("RIGHT PARENTHESIS\n");}
"{"                                             {printf("LEFT CURLY BRACKET\n");}
"}"                                             {printf("RIGHT CURLY BRACKET\n");}
"true"                                          {printf("TRUE\n");}
"false"                                         {printf("FALSE\n");}
"return"                                        {printf("RETURN\n");}
"break"                                         {printf("BREAK\n");}
","                                             {printf("COMMA\n");}
":"                                             {printf("COLON\n");}
"int"                                           {printf("INT\n");}
"float"                                         {printf("FLOAT\n");}
"string"                                        {printf("STRING\n");}
[_a-zA-Z][_a-zA-Z0-9]*                          {printf("ID(%s)\n",yytext);}
[0-9]+                                          {printf("INTEGER(%s)\n",yytext);}
[0-9]+"."[0-9]+                                 {printf("FLOAT(%s)\n",yytext);}
(\"([^\\\"]|\\.)*\") | (\'([^\\\']|\\.)*\')     {printf("STRING(%s)\n",yytext);}
"//".*\n                                        {printf("LINE COMMENT(%s)\n",yytext);}
"/*"( [^*] | (\*+[^*/]) )*\*+\/                 {printf("BLOCK COMMENT\n");}
.                                               {printf("Invalid character.\n");}

%%

#ifndef yywrap
   int yywrap (void) {return 1;}
#endif

int main(void)
{
  yylex();  
  return 0;
}