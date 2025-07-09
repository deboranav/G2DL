%{
#define _GNU_SOURCE // Ativa extensões GNU, como asprintf
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "lib/types.h"
#include "lib/symbol_table.h"

int yylex(void);
void yyerror(const char *s);

// Variável global para armazenar o corpo do código C gerado
char *generated_code_body = NULL; 

void declare_variables(FILE *file);

extern int yylineno;
extern FILE *yyin;
%}

%debug

%union {
    int intVal;
    float floatVal;
    char *strVal;
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

%type <strVal> expression assignment variable block statements statement control_structure printf_statement
%type <strVal> argument_list_printf

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

// A gramática inteira agora constrói uma única string.
program:
    statements { generated_code_body = $1; }
    ;

statements:
    /* vazio */ { $$ = strdup(""); }
    | statements statement {
        if ($2) {
            asprintf(&$$, "%s%s", $1, $2);
            free($1);
            free($2);
        } else {
            $$ = $1; 
        }
    }
    ;

statement:
    assignment ';'          { $$ = $1; }
    | expression ';'          { asprintf(&$$, "    %s;\n", $1); free($1); }
    | control_structure     { $$ = $1; }
    | printf_statement      { $$ = $1; }
    | block                 { $$ = $1; }
    | error ';'             { 
                              fprintf(stderr, "Erro de sintaxe na linha %d. Tentando recuperar em ';'\n", yylineno);
                              yyerrok;
                              $$ = NULL; 
                            }
    ;

// Regras de 'printf' corrigidas para gerar C válido
printf_statement:
    // Caso: printf("string literal", args...)
    PRINTF LEFT_PARENTHESIS STRING_LITERAL COMMA argument_list_printf RIGHT_PARENTHESIS ';'
    {
        asprintf(&$$, "    printf(%s, %s);\n", $3, $5);
        free($3);
        free($5);
    }
    // Caso: printf("string literal")
    | PRINTF LEFT_PARENTHESIS STRING_LITERAL RIGHT_PARENTHESIS ';'
    {
        asprintf(&$$, "    printf(%s);\n", $3);
        free($3);
    }
    ;

argument_list_printf:
    expression { $$ = $1; }
    | argument_list_printf COMMA expression {
        asprintf(&$$, "%s, %s", $1, $3);
        free($1);
        free($3);
    }
    ;

block:
    LEFT_CURLY_BRACKET statements RIGHT_CURLY_BRACKET
    {
        asprintf(&$$, "{\n%s    }\n", $2);
        free($2);
    }
    ;

assignment:
    variable ASSIGNMENT expression {
        add_symbol($1, TYPE_UNKNOWN);
        asprintf(&$$, "    %s = %s;\n", $1, $3);
        free($1);
        free($3);
    }
    | variable PLUS_ASSIGNMENT expression {
        add_symbol($1, TYPE_UNKNOWN);
        asprintf(&$$, "    %s += %s;\n", $1, $3);
        free($1);
        free($3);
    }
    ;

expression:
    INTEGER                     { asprintf(&$$, "%d", $1); }
    | FLOAT_LITERAL             { asprintf(&$$, "%f", $1); }
    | STRING_LITERAL            { $$ = $1; }
    | variable                  { $$ = $1; }
    | TRUE                      { $$ = strdup("1"); }
    | FALSE                     { $$ = strdup("0"); }
    | INPUT LEFT_PARENTHESIS RIGHT_PARENTHESIS {
        $$ = strdup("runtime_input_c()");
    }
    | expression PLUS expression          { asprintf(&$$, "(%s + %s)", $1, $3); free($1); free($3); }
    | expression MINUS expression         { asprintf(&$$, "(%s - %s)", $1, $3); free($1); free($3); }
    | expression MULTIPLY expression      { asprintf(&$$, "(%s * %s)", $1, $3); free($1); free($3); }
    | expression DIVIDE expression        { asprintf(&$$, "(%s / %s)", $1, $3); free($1); free($3); }
    | expression MOD expression           { asprintf(&$$, "((int)%s %% (int)%s)", $1, $3); free($1); free($3); }
    | expression POWER expression         { asprintf(&$$, "pow(%s, %s)", $1, $3); free($1); free($3); }
    | expression EQUAL expression         { asprintf(&$$, "(%s == %s)", $1, $3); free($1); free($3); }
    | expression NOT_EQUAL expression     { asprintf(&$$, "(%s != %s)", $1, $3); free($1); free($3); }
    | expression LESS_THAN expression     { asprintf(&$$, "(%s < %s)", $1, $3); free($1); free($3); }
    | expression GREATER_THAN expression  { asprintf(&$$, "(%s > %s)", $1, $3); free($1); free($3); }
    | expression LESS_THAN_OR_EQUAL expression { asprintf(&$$, "(%s <= %s)", $1, $3); free($1); free($3); }
    | expression GREATER_THAN_OR_EQUAL expression { asprintf(&$$, "(%s >= %s)", $1, $3); free($1); free($3); }
    | expression AND expression           { asprintf(&$$, "(%s && %s)", $1, $3); free($1); free($3); }
    | expression OR expression            { asprintf(&$$, "(%s || %s)", $1, $3); free($1); free($3); }
    | NOT expression                      { asprintf(&$$, "(!%s)", $2); free($2); }
    | LEFT_PARENTHESIS expression RIGHT_PARENTHESIS { $$ = $2; }
    ;

variable:
    ID { $$ = $1; }
    ;

control_structure:
    IF LEFT_PARENTHESIS expression RIGHT_PARENTHESIS block {
        asprintf(&$$, "    if (%s) %s", $3, $5);
        free($3); free($5);
    }
    | IF LEFT_PARENTHESIS expression RIGHT_PARENTHESIS block ELSE statement {
        if ($7) {
            asprintf(&$$, "    if (%s) %s else %s", $3, $5, $7);
            free($7);
        } else {
            asprintf(&$$, "    if (%s) %s", $3, $5);
        }
        free($3); free($5);
    }
    | WHILE LEFT_PARENTHESIS expression RIGHT_PARENTHESIS block {
        asprintf(&$$, "    while (%s) %s", $3, $5);
        free($3); free($5);
    }
    ;

%%

void yyerror(const char *msg) {
    fprintf(stderr, "Erro na linha %d: %s\n", yylineno, msg);
}

void declare_variables(FILE* file) {
    fprintf(file, "    // Variáveis inferidas pelo tradutor\n");
    for (int i = 0; i < get_symbol_count(); i++) {
        Symbol *sym = get_symbol_by_index(i);
        if (sym) {
            if (sym->type == TYPE_STRING) {
                 fprintf(file, "    char* %s = NULL;\n", sym->name);
            } else {
                 fprintf(file, "    double %s;\n", sym->name);
            }
        }
    }
    fprintf(file, "\n");
}

int main(int argc, char *argv[]) {
    #if YYDEBUG
        yydebug = 1;
    #endif

    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        if (!yyin) {
            perror(argv[1]);
            return 1;
        }
    } else {
        yyin = stdin;
    }

    init_symbol_table();
    
    int result = yyparse();

    if (result == 0 && generated_code_body != NULL) {
        FILE* final_output_file = fopen("output.c", "w");
        if (!final_output_file) {
            perror("Não foi possível criar o arquivo de saída output.c");
            if (generated_code_body) free(generated_code_body);
            return 1;
        }

        // Ordem correta de escrita no arquivo final:
        // 1. Cabeçalhos
        fprintf(final_output_file, "#include <stdio.h>\n");
        fprintf(final_output_file, "#include <stdlib.h>\n");
        fprintf(final_output_file, "#include <string.h>\n");
        fprintf(final_output_file, "#include <math.h>\n\n");
        
        // 2. Definição da função de input auxiliar
        fprintf(final_output_file, "double runtime_input_c() {\n");
        fprintf(final_output_file, "    char buffer[256];\n");
        fprintf(final_output_file, "    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {\n");
        fprintf(final_output_file, "        return atof(buffer);\n");
        fprintf(final_output_file, "    }\n");
        fprintf(final_output_file, "    return 0.0;\n}\n\n");
        
        fprintf(final_output_file, "int main() {\n");
        
        // 3. Declarações de variáveis (no topo do main)
        declare_variables(final_output_file);
        
        // 4. Corpo do código traduzido
        fprintf(final_output_file, "%s", generated_code_body);
        
        // 5. Fechamento do main
        fprintf(final_output_file, "\n    return 0;\n}\n");
        
        fclose(final_output_file);
        printf("Tradução concluída com sucesso. Verifique o arquivo output.c\n");

    } else {
        printf("A tradução falhou devido a erros de sintaxe ou código vazio.\n");
    }

    if (generated_code_body) free(generated_code_body);
    if (yyin != stdin) fclose(yyin);
    free_symbol_table_memory();

    return result;
}