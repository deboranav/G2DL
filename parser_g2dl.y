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

char *function_definitions_code = NULL;
char *main_body_code = NULL;

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
%token MATRIX // <-- MUDANÇA: Novo token para a palavra-chave 'function'

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
%type <strVal> declaration matrix_access
%type <strVal> function_definition function_call

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

//A gramática agora é definida por 'source_file_content' que separa funções e o corpo principal.
program:
    source_file_content
    ;

source_file_content:
    /* Vazio: inicializa as strings globais */
    {
        function_definitions_code = strdup("");
        main_body_code = strdup("");
    }
    | source_file_content function_definition {
        // Anexa o código da nova função à string de funções
        char* temp = NULL;
        asprintf(&temp, "%s%s", function_definitions_code, $2);
        free(function_definitions_code);
        free($2);
        function_definitions_code = temp;
    }
    | source_file_content statement {
        // Anexa o código do comando à string do corpo principal
        if ($2) { // Ignora em caso de erro de sintaxe
            char* temp = NULL;
            asprintf(&temp, "%s%s", main_body_code, $2);
            free(main_body_code);
            free($2);
            main_body_code = temp;
        }
    }
    ;

// 'statements' ainda é usado dentro de blocos {}, então sua definição permanece.
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
    function_call ';'       { $$ = $1; } // <-- MUDANÇA: Chamada de função é um comando.
    | declaration ';'         { $$ = $1; } 
    | assignment ';'          { $$ = $1; }
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

//Definição de uma função simples
function_definition:
    FUNCTION ID LEFT_PARENTHESIS RIGHT_PARENTHESIS block {
        if (lookup_symbol($2) != NULL) {
            char error_msg[256];
            sprintf(error_msg, "Erro Semântico: Função '%s' já foi declarada.", $2);
            yyerror(error_msg);
            YYABORT;
        }
        add_symbol($2, TYPE_FUNCTION);
        asprintf(&$$, "void %s() %s\n", $2, $5);
        free($2);
        free($5);
    }
    ;

//Chamada de uma função simples
function_call:
    ID LEFT_PARENTHESIS RIGHT_PARENTHESIS {
        // Futuramente, podemos verificar se $1 é mesmo uma função.
        asprintf(&$$, "    %s();", $1);
        free($1);
    }
    ;

declaration:
    MATRIX ID LEFT_SQUARE_BRACKET INTEGER COMMA INTEGER RIGHT_SQUARE_BRACKET
    {
        if (lookup_symbol($2) != NULL) {
            char error_msg[256];
            sprintf(error_msg, "Erro Semântico: Variável '%s' já foi declarada.", $2);
            yyerror(error_msg);
            YYABORT;
        }
        // add_matrix_symbol($2, $4, $6); 
        asprintf(&$$, "    double %s[%d][%d];\n", $2, $4, $6);
        free($2);
    }
    ;

printf_statement:
    PRINTF LEFT_PARENTHESIS STRING_LITERAL COMMA argument_list_printf RIGHT_PARENTHESIS ';'
    {
        asprintf(&$$, "    printf(%s, %s);\n", $3, $5);
        free($3);
        free($5);
    }
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
        if (lookup_symbol($1) == NULL) {
            add_symbol($1, TYPE_UNKNOWN);
        }
        asprintf(&$$, "    %s = %s;\n", $1, $3);
        free($1);
        free($3);
    }
    | matrix_access ASSIGNMENT expression {
        asprintf(&$$, "    %s = %s;\n", $1, $3);
        free($1);
        free($3);
    }
    | variable PLUS_ASSIGNMENT expression {
        if (lookup_symbol($1) == NULL) {
             char error_msg[256];
            sprintf(error_msg, "Erro Semântico: Variável '%s' não declarada.", $1);
            yyerror(error_msg);
            YYABORT;
        }
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
    | matrix_access             { $$ = $1; } 
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

matrix_access:
    ID LEFT_SQUARE_BRACKET expression COMMA expression RIGHT_SQUARE_BRACKET
    {
        asprintf(&$$, "%s[(int)(%s)][(int)(%s)]", $1, $3, $5);
        free($1); free($3); free($5);
    }
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
    fprintf(file, "    // Variáveis globais e escalares inferidas pelo tradutor\n");
    for (int i = 0; i < get_symbol_count(); i++) {
        Symbol *sym = get_symbol_by_index(i);
        if (sym) {
            // Não declara as funções aqui, pois elas são definidas em outro lugar.
            if (sym->type != TYPE_MATRIX && sym->type != TYPE_FUNCTION) {
                if (sym->type == TYPE_STRING) {
                     fprintf(file, "    char* %s;\n", sym->name);
                } else {
                     fprintf(file, "    double %s;\n", sym->name);
                }
            }
        }
    }
    fprintf(file, "\n");
}

// <-- MUDANÇA: A função main foi completamente reescrita para montar o arquivo final.
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
    
    int result = yyparse(); // Isso preenche as strings globais function_definitions_code e main_body_code

    if (result == 0) {
        FILE* final_output_file = fopen("output.c", "w");
        if (!final_output_file) {
            perror("Não foi possível criar o arquivo de saída output.c");
            if (function_definitions_code) free(function_definitions_code);
            if (main_body_code) free(main_body_code);
            return 1;
        }

        // --- Ordem Correta de Escrita no Arquivo Final ---
        // 1. Cabeçalhos C
        fprintf(final_output_file, "#include <stdio.h>\n#include <stdlib.h>\n#include <string.h>\n#include <math.h>\n\n");
        
        // 2. Funções auxiliares (como runtime_input_c)
        fprintf(final_output_file, "double runtime_input_c() {\n    char buffer[256];\n    if (fgets(buffer, sizeof(buffer), stdin) != NULL) { return atof(buffer); }\n    return 0.0;\n}\n\n");
        
        // 3. Definições de funções traduzidas do código do usuário
        if (function_definitions_code) {
            fprintf(final_output_file, "%s", function_definitions_code);
        }
        
        // 4. Início da função main() do C
        fprintf(final_output_file, "\nint main() {\n");
        
        // 5. Declaração de variáveis globais/escalares
        declare_variables(final_output_file);
        
        // 6. Corpo principal do código (comandos fora de funções)
        if (main_body_code) {
            fprintf(final_output_file, "%s", main_body_code);
        }
        
        // 7. Fechamento da função main()
        fprintf(final_output_file, "\n    return 0;\n}\n");
        
        fclose(final_output_file);
        printf("Tradução concluída com sucesso. Verifique o arquivo output.c\n");

    } else {
        printf("A tradução falhou devido a erros de sintaxe ou semânticos.\n");
    }

    // Libera a memória alocada para as strings de código
    if (function_definitions_code) free(function_definitions_code);
    if (main_body_code) free(main_body_code);
    if (yyin != stdin) fclose(yyin);
    free_symbol_table_memory();

    return result;
}