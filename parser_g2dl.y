%{
#define _GNU_SOURCE 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "lib/types.h"
#include "lib/symbol_table.h"

int yylex(void);
void yyerror(const char *s);

// Variáveis globais que serão preenchidas UMA VEZ no final da análise.
char *struct_definitions_code = NULL;
char *function_definitions_code = NULL;
char *main_body_code = NULL;

UserType* current_type_definition = NULL;

void declare_variables(FILE *file);

extern int yylineno;
extern FILE *yyin;
%}

%debug

%union {
    int         intVal;
    float       floatVal;
    char* strVal;
    CodeBlocks  code_blocks; 
    TypeInfo    type_info;
}

/* --- Tokens --- */
%token FUNCTION RETURN BREAK IF ELSE WHILE FOR TRUE FALSE
%token INT STRING FLOAT 
%token MATRIX 
%token TYPE_DEF DOT

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

/* --- Tipos dos Não-Terminais --- */
%type <code_blocks> source_file_content

%type <strVal> expression assignment variable block statements statement control_structure printf_statement
%type <strVal> argument_list_printf declaration matrix_access function_definition function_call
%type <strVal> return_statement param_list member_list type_definition argument_list

%type <strVal> member_decl param_decl
%type <type_info> type_specifier


/* --- Precedência e Associatividade dos Operadores --- */
%left OR
%left AND
%left EQUAL NOT_EQUAL
%left LESS_THAN GREATER_THAN LESS_THAN_OR_EQUAL GREATER_THAN_OR_EQUAL
%left PLUS MINUS
%left MULTIPLY DIVIDE MOD
%right POWER
%right NOT
%right UMINUS
%nonassoc THEN
%nonassoc ELSE

%start program

%%

/* --- Gramática Principal --- */

program:
    source_file_content 
    {
        struct_definitions_code = $1.structs;
        function_definitions_code = $1.funcs;
        main_body_code = $1.main;
    }
    ;

source_file_content:
    /* Vazio: inicializa a struct com strings vazias */
    {
        $$.structs = strdup("");
        $$.funcs = strdup("");
        $$.main = strdup("");
    }
    | source_file_content type_definition 
    {
        $$.funcs = $1.funcs;
        $$.main = $1.main;
        asprintf(&$$.structs, "%s%s", $1.structs, $2);
        free($1.structs);
        free($2);
    }
    | source_file_content function_definition 
    {
        $$.structs = $1.structs;
        $$.main = $1.main;
        asprintf(&$$.funcs, "%s%s", $1.funcs, $2);
        free($1.funcs);
        free($2);
    }
    | source_file_content statement 
    {
        $$.structs = $1.structs;
        $$.funcs = $1.funcs;
        if ($2) {
            asprintf(&$$.main, "%s%s", $1.main, $2);
            free($1.main);
            free($2);
        } else {
            $$.main = $1.main; 
        }
    }
    ;

statements:
    /* vazio */ { $$ = strdup(""); }
    | statements statement 
    {
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
    declaration ';'         { $$ = $1; }
    | assignment ';'          { $$ = $1; }
    | expression ';'          { asprintf(&$$, "    %s;\n", $1); free($1); }
    | control_structure     { $$ = $1; }
    | printf_statement      { $$ = $1; }
    | block                 { $$ = $1; }
    | return_statement      { $$ = $1; }
    | error ';'             { fprintf(stderr, "Erro de sintaxe na linha %d\n", yylineno); yyerrok; $$ = NULL; }
    ;

return_statement:
    RETURN expression ';' 
    { 
        asprintf(&$$, "    return %s;\n", $2); 
        free($2); 
    }
    ;

/* --- Regras de Definição de Tipos, Funções, etc. --- */

type_specifier:
    FLOAT   { $$.c_typename = strdup("double"); $$.type_enum = TYPE_FLOAT; }
    | INT     { $$.c_typename = strdup("int");    $$.type_enum = TYPE_INT; }
    | STRING  { $$.c_typename = strdup("char*");  $$.type_enum = TYPE_STRING; }
    | ID      
    { 
        if (lookup_type($1) == NULL) { 
            char err[256]; sprintf(err, "Erro Semântico: Tipo '%s' não definido.", $1); yyerror(err); YYABORT; 
        }
        asprintf(&$$.c_typename, "struct %s", $1); 
        $$.type_enum = TYPE_STRUCT;
        free($1);
    }
    ;

type_definition:
    TYPE_DEF ID LEFT_CURLY_BRACKET member_list RIGHT_CURLY_BRACKET ';' 
    {
        if (lookup_type($2) != NULL) { 
            char err[256]; sprintf(err, "Erro Semântico: Tipo '%s' já definido.", $2); yyerror(err); YYABORT; 
        }
        current_type_definition = define_type($2);
        asprintf(&$$, "struct %s {\n%s};\n\n", $2, $4);
        free($2); free($4);
        current_type_definition = NULL;
    }
    ;

member_list:
    /* vazio */ { $$ = strdup(""); }
    | member_list member_decl { asprintf(&$$, "%s%s", $1, $2); free($1); free($2); }
    ;

member_decl:
    type_specifier ID ';' 
    {
        if (current_type_definition != NULL) { add_member_to_type(current_type_definition, $2, $1.type_enum); }
        asprintf(&$$, "    %s %s;\n", $1.c_typename, $2);
        free($1.c_typename); // Libera a string dentro da struct
        free($2);
    }
    ;

declaration:
    type_specifier ID 
    {
        if (lookup_symbol($2) != NULL) { char err[256]; sprintf(err, "Erro Semântico: Variável '%s' já declarada.", $2); yyerror(err); YYABORT; }
        if ($1.type_enum == TYPE_STRUCT) { add_struct_variable_symbol($2, $1.c_typename); } 
        else { add_symbol($2, $1.type_enum); }
        // Não gera mais código C aqui. Retorna uma string vazia.
        $$ = strdup(""); 
        free($1.c_typename); free($2);
    }
    | MATRIX ID LEFT_SQUARE_BRACKET INTEGER COMMA INTEGER RIGHT_SQUARE_BRACKET 
    {
        if (lookup_symbol($2) != NULL) { char err[256]; sprintf(err, "Erro Semântico: Variável '%s' já declarada.", $2); yyerror(err); YYABORT; }
        add_matrix_symbol($2, $4, $6); 
        // Gera a declaração da matriz diretamente, pois é um caso especial.
        asprintf(&$$, "    double %s[%d][%d];\n", $2, $4, $6);
        free($2);
    }
    ;

function_definition:
    FUNCTION type_specifier ID LEFT_PARENTHESIS param_list RIGHT_PARENTHESIS block 
    {
        if (lookup_symbol($3) != NULL) { 
            char err[256]; sprintf(err, "Erro Semântico: Função '%s' já declarada.", $3); yyerror(err); YYABORT; 
        }
        add_symbol($3, TYPE_FUNCTION);
        asprintf(&$$, "%s %s(%s) %s\n", $2.c_typename, $3, $5, $7);
        free($2.c_typename); free($3); free($5); free($7);
    }
    ;

param_list:
    /* vazio */ { $$ = strdup(""); }
    | param_decl { $$ = $1; }
    | param_list COMMA param_decl { asprintf(&$$, "%s, %s", $1, $3); free($1); free($3); }
    ;

param_decl:
    type_specifier ID { 
        asprintf(&$$, "%s %s", $1.c_typename, $2); 
        free($1.c_typename); 
        free($2); 
    }
    ;

function_call:
    ID LEFT_PARENTHESIS argument_list RIGHT_PARENTHESIS 
    { 
        asprintf(&$$, "%s(%s)", $1, $3); 
        free($1); 
        free($3); 
    }
    ;

argument_list:
    /* vazio */ { $$ = strdup(""); }
    | expression { $$ = $1; }
    | argument_list COMMA expression { asprintf(&$$, "%s, %s", $1, $3); free($1); free($3); }
    ;

assignment:
    variable ASSIGNMENT expression 
    { 
        if (lookup_symbol($1) == NULL) { add_symbol($1, TYPE_UNKNOWN); }
        asprintf(&$$, "    %s = %s;\n", $1, $3); 
        free($1); free($3); 
    }
    | matrix_access ASSIGNMENT expression 
    { 
        asprintf(&$$, "    %s = %s;\n", $1, $3); 
        free($1); free($3); 
    }
    | variable DOT ID ASSIGNMENT expression 
    { 
        asprintf(&$$, "    %s.%s = %s;\n", $1, $3, $5); 
        free($1); free($3); free($5); 
    }
    | variable PLUS_ASSIGNMENT expression 
    { 
        if (lookup_symbol($1) == NULL) { 
            char err[256]; sprintf(err, "Erro Semântico: Variável '%s' não declarada.", $1); yyerror(err); YYABORT; 
        } 
        asprintf(&$$, "    %s += %s;\n", $1, $3); 
        free($1); free($3); 
    }
    ;

/* --- Regras de Expressão --- */

expression:
    INTEGER                         { asprintf(&$$, "%d", $1); }
    | FLOAT_LITERAL                   { asprintf(&$$, "%f", $1); }
    | STRING_LITERAL                { $$ = $1; }
    | variable                      { $$ = $1; }
    | matrix_access                 { $$ = $1; } 
    | variable DOT ID                 { asprintf(&$$, "%s.%s", $1, $3); free($1); free($3); }
    | function_call                 { $$ = $1; }
    | TRUE                          { $$ = strdup("1"); }
    | FALSE                         { $$ = strdup("0"); }
    | INPUT LEFT_PARENTHESIS RIGHT_PARENTHESIS { $$ = strdup("runtime_input_c()"); }
    | LEFT_PARENTHESIS expression RIGHT_PARENTHESIS { $$ = $2; }
    | MINUS expression %prec UMINUS     { asprintf(&$$, "(-%s)", $2); free($2); }
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
    
printf_statement:
    PRINTF LEFT_PARENTHESIS STRING_LITERAL COMMA argument_list_printf RIGHT_PARENTHESIS ';' 
    { 
        asprintf(&$$, "    printf(%s, %s);\n", $3, $5); 
        free($3); free($5); 
    }
    | PRINTF LEFT_PARENTHESIS STRING_LITERAL RIGHT_PARENTHESIS ';' 
    { 
        asprintf(&$$, "    printf(%s);\n", $3); 
        free($3); 
    }
    ;

argument_list_printf:
    expression { $$ = $1; }
    | argument_list_printf COMMA expression { asprintf(&$$, "%s, %s", $1, $3); free($1); free($3); }
    ;

block: 
    LEFT_CURLY_BRACKET statements RIGHT_CURLY_BRACKET 
    { 
        asprintf(&$$, "{\n%s    }\n", $2); 
        free($2); 
    }
    ;

control_structure: 
    IF LEFT_PARENTHESIS expression RIGHT_PARENTHESIS block 
    { 
        asprintf(&$$, "    if (%s) %s", $3, $5); 
        free($3); free($5); 
    } 
    | IF LEFT_PARENTHESIS expression RIGHT_PARENTHESIS block ELSE statement 
    { 
        if ($7) { 
            asprintf(&$$, "    if (%s) %s else %s", $3, $5, $7); 
            free($7);
        } else { 
            asprintf(&$$, "    if (%s) %s", $3, $5); 
        } 
        free($3); free($5); 
    } 
    | WHILE LEFT_PARENTHESIS expression RIGHT_PARENTHESIS block 
    { 
        asprintf(&$$, "    while (%s) %s", $3, $5); 
        free($3); free($5); 
    }
    ;

%%

/* --- Seção de Código C Auxiliar --- */

void yyerror(const char *msg) {
    fprintf(stderr, "Erro na linha %d: %s\n", yylineno, msg);
}

void declare_variables(FILE* file) {
    fprintf(file, "    // Variáveis locais da main (escalares)\n");
    for (int i = 0; i < get_symbol_count(); i++) {
        Symbol *sym = get_symbol_by_index(i);
        if (sym) {
            // Não declara variáveis que são de tipos complexos ou funções
            if (sym->type != TYPE_FUNCTION && sym->type != TYPE_MATRIX && sym->type != TYPE_STRUCT) {
                // E também não declara as globais de comunicação
                if (strcmp(sym->name, "arg1_r") != 0 && strcmp(sym->name, "arg2_r") != 0 && 
                    strcmp(sym->name, "retorno_r") != 0 && strcmp(sym->name, "arg_int1") != 0 &&
                    strcmp(sym->name, "arg_int2") != 0 && strcmp(sym->name, "ret_bool") != 0)
                {
                    if (sym->type == TYPE_STRING) {
                         fprintf(file, "    char* %s;\n", sym->name);
                    } else {
                         fprintf(file, "    double %s;\n", sym->name);
                    }
                }
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
        if (!yyin) { perror(argv[1]); return 1; } 
    } else { 
        yyin = stdin; 
    }

    init_symbol_table();
    
    int result = yyparse();

    if (result == 0) {
        FILE* final_output_file = fopen("output.c", "w");
        if (!final_output_file) {
            perror("Não foi possível criar o arquivo de saída output.c");
            if (struct_definitions_code) free(struct_definitions_code);
            if (function_definitions_code) free(function_definitions_code);
            if (main_body_code) free(main_body_code);
            return 1;
        }

        /* --- Ordem Correta de Escrita no Arquivo Final --- */
        fprintf(final_output_file, "#include <stdio.h>\n#include <stdlib.h>\n#include <string.h>\n#include <math.h>\n\n");
        
        if (struct_definitions_code) { 
            fprintf(final_output_file, "%s", struct_definitions_code); 
        }
        
        fprintf(final_output_file, "double runtime_input_c() { char b[256]; if(fgets(b,256,stdin)){return atof(b);} return 0.0; }\n\n");
        
        if (function_definitions_code) { 
            fprintf(final_output_file, "%s", function_definitions_code); 
        }
        
        fprintf(final_output_file, "\nint main() {\n");
        
        declare_variables(final_output_file);
        
        if (main_body_code) { 
            fprintf(final_output_file, "%s", main_body_code); 
        }
        
        fprintf(final_output_file, "\n    return 0;\n}\n");
        
        fclose(final_output_file);
        printf("Tradução concluída com sucesso.\n");

    } else {
        printf("A tradução falhou.\n");
    }

    if (struct_definitions_code) free(struct_definitions_code);
    if (function_definitions_code) free(function_definitions_code);
    if (main_body_code) free(main_body_code);
    if (yyin != stdin) fclose(yyin);
    free_symbol_table_memory();

    return result;
}