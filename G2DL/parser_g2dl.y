%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdarg.h>

#include "types.h"
#include "symbol_table.h"

int yylex(void);
void yyerror(const char *s);
void my_printf_runtime(char *format_string, ArgumentNode *args_list);
void free_argument_list(ArgumentNode *list);
RuntimeValue runtime_input();

extern int yylineno;
extern FILE *yyin;
%}

%debug

%union {
    int intVal;
    float floatVal;
    char *strVal;
    RuntimeValue runtimeVal;
    ArgumentNode *argList;
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

%type <runtimeVal> expression
%type <strVal> variable
%type <argList> argument_list_printf

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
    statements
    | /* vazio */
    ;

statements:
    statement
    | statements statement
    ;

statement:
    function_decl
    | assignment ';'
    | expression ';'
    | control_structure
    | RETURN expression ';' { printf("Retornando valor (tipo %d): ", $2.type);
                                 if ($2.type == TYPE_INT) printf("%d\n", $2.data.intVal);
                                 else if ($2.type == TYPE_FLOAT) printf("%f\n", $2.data.floatVal);
                                 else if ($2.type == TYPE_STRING) printf("%s\n", $2.data.strVal);
                                 if ($2.type == TYPE_STRING && $2.data.strVal) free($2.data.strVal);
                               }
    | printf_statement
    | block
    | error ';' { fprintf(stderr, "Erro de sintaxe na linha %d. Tentando recuperar em ';'\n", yylineno); yyerrok; }
    ;

printf_statement:
    PRINTF LEFT_PARENTHESIS STRING_LITERAL COMMA argument_list_printf RIGHT_PARENTHESIS ';'
    {
        my_printf_runtime($3, $5);
        free($3);
        free_argument_list($5);
    }
    | PRINTF LEFT_PARENTHESIS STRING_LITERAL RIGHT_PARENTHESIS ';'
    {
        my_printf_runtime($3, NULL);
        free($3);
    }
    | PRINTF LEFT_PARENTHESIS ID RIGHT_PARENTHESIS ';'
    {

        Symbol *sym = lookup_symbol($3);

        if (sym != NULL) {
            char *temp_format = NULL;
            ArgumentNode *arg_list_temp = NULL;

            arg_list_temp = (ArgumentNode*) malloc(sizeof(ArgumentNode));
            if (!arg_list_temp) {
                perror("Erro ao alocar ArgumentNode para printf(ID)");
                exit(EXIT_FAILURE);
            }
            arg_list_temp->value = sym->value; 
            arg_list_temp->next = NULL;

            if (arg_list_temp->value.type == TYPE_STRING && arg_list_temp->value.data.strVal != NULL) {
                arg_list_temp->value.data.strVal = strdup(arg_list_temp->value.data.strVal);
            }

            if (sym->value.type == TYPE_INT) {
                temp_format = strdup("%d\n");
            } else if (sym->value.type == TYPE_FLOAT) {
                temp_format = strdup("%f\n");
            } else if (sym->value.type == TYPE_STRING) {
                temp_format = strdup("%s\n");
            } else {
                fprintf(stderr, "Erro de runtime: printf(ID) com tipo de variável não suportado.\n");
                temp_format = strdup("Tipo desconhecido para ID.\n");
            }

            if (temp_format) {
                my_printf_runtime(temp_format, arg_list_temp);
                free(temp_format);
            }
            free_argument_list(arg_list_temp);
        } else {
            fprintf(stderr, "Erro de runtime: Variável '%s' não definida na linha %d para printf.\n", $3, yylineno);
            yyerror("Variável não definida em printf()");
        }
        free($3);
    }
    ;

argument_list_printf:
    expression { $$ = (ArgumentNode *)malloc(sizeof(ArgumentNode));
                 if (!$$) { perror("malloc"); exit(EXIT_FAILURE); }
                 $$->value = $1;
                 $$->next = NULL;
               }
    | argument_list_printf COMMA expression {
                     ArgumentNode *newNode = (ArgumentNode *)malloc(sizeof(ArgumentNode));
                     if (!newNode) { perror("malloc"); exit(EXIT_FAILURE); }
                     newNode->value = $3;
                     newNode->next = NULL;
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
    ;

parameters:
    /* vazio */
    | parameter_list
    ;

parameter_list:
    ID
    | parameter_list COMMA ID
    ;

block:
    LEFT_CURLY_BRACKET statements RIGHT_CURLY_BRACKET
    ;

assignment:
    variable assignment_operator expression {
        printf("Atribuição para a variável %s. Valor: ", $1);
        if ($3.type == TYPE_INT) printf("%d\n", $3.data.intVal);
        else if ($3.type == TYPE_FLOAT) printf("%f\n", $3.data.floatVal);
        else if ($3.type == TYPE_STRING) printf("%s\n", $3.data.strVal);
        printf("\n");

        insert_symbol($1, $3);

        free($1);
    }
    | array_access assignment_operator expression
    ;

assignment_operator:
    ASSIGNMENT
    | PLUS_ASSIGNMENT
    | MINUS_ASSIGNMENT
    | MULTIPLY_ASSIGNMENT
    | DIVIDE_ASSIGNMENT
    | MOD_ASSIGNMENT
    | POWER_ASSIGNMENT
    ;

expression:
    INTEGER                     { $$ = (RuntimeValue){.type = TYPE_INT, .data.intVal = $1}; }
    | FLOAT_LITERAL             { $$ = (RuntimeValue){.type = TYPE_FLOAT, .data.floatVal = $1}; }
    | STRING_LITERAL            { $$ = (RuntimeValue){.type = TYPE_STRING, .data.strVal = $1}; }
    | variable                  {
        printf("Usando variável %s\n", $1);
        Symbol *sym = lookup_symbol($1);
        if (sym != NULL) {
            $$ = sym->value;
            if ($$.type == TYPE_STRING && $$.data.strVal != NULL) {
                $$.data.strVal = strdup($$.data.strVal);
            }
        } else {
            fprintf(stderr, "Erro de runtime: Variável '%s' não definida na linha %d.\n", $1, yylineno);
            yyerror("Variável não definida");
            $$ = (RuntimeValue){.type = TYPE_INT, .data.intVal = 0};
        }
        free($1);
    }
    | function_call             { $$ = (RuntimeValue){.type = TYPE_FLOAT, .data.floatVal = 0.0}; }
    | array_access              { $$ = (RuntimeValue){.type = TYPE_FLOAT, .data.floatVal = 0.0}; }
    | array_literal             { $$ = (RuntimeValue){.type = TYPE_FLOAT, .data.floatVal = 0.0}; }
    | TRUE                      { $$ = (RuntimeValue){.type = TYPE_INT, .data.intVal = 1}; }
    | FALSE                     { $$ = (RuntimeValue){.type = TYPE_INT, .data.intVal = 0}; }
    | INPUT LEFT_PARENTHESIS RIGHT_PARENTHESIS {
        printf("Chamada de input(). Aguardando entrada...\n");
        $$ = runtime_input();
    }
    | expression PLUS expression          {
        float val1 = ($1.type == TYPE_INT) ? (float)$1.data.intVal : $1.data.floatVal;
        float val2 = ($3.type == TYPE_INT) ? (float)$3.data.intVal : $3.data.floatVal;
        $$ = (RuntimeValue){.type = TYPE_FLOAT, .data.floatVal = val1 + val2};
    }
    | expression MINUS expression         {
        float val1 = ($1.type == TYPE_INT) ? (float)$1.data.intVal : $1.data.floatVal;
        float val2 = ($3.type == TYPE_INT) ? (float)$3.data.intVal : $3.data.floatVal;
        $$ = (RuntimeValue){.type = TYPE_FLOAT, .data.floatVal = val1 - val2};
    }
    | expression MULTIPLY expression      {
        float val1 = ($1.type == TYPE_INT) ? (float)$1.data.intVal : $1.data.floatVal;
        float val2 = ($3.type == TYPE_INT) ? (float)$3.data.intVal : $3.data.floatVal;
        $$ = (RuntimeValue){.type = TYPE_FLOAT, .data.floatVal = val1 * val2};
    }
    | expression DIVIDE expression        {
        float val1 = ($1.type == TYPE_INT) ? (float)$1.data.intVal : $1.data.floatVal;
        float val2 = ($3.type == TYPE_INT) ? (float)$3.data.intVal : $3.data.floatVal;
        if(val2 != 0) $$ = (RuntimeValue){.type = TYPE_FLOAT, .data.floatVal = val1 / val2};
        else { yyerror("Divisão por zero"); $$ = (RuntimeValue){.type = TYPE_FLOAT, .data.floatVal = 0.0}; }
    }
    | expression MOD expression           {
        int val1 = ($1.type == TYPE_FLOAT) ? (int)$1.data.floatVal : $1.data.intVal;
        int val2 = ($3.type == TYPE_FLOAT) ? (int)$3.data.floatVal : $3.data.intVal;
        if(val2 != 0) $$ = (RuntimeValue){.type = TYPE_INT, .data.intVal = val1 % val2};
        else { yyerror("Modulo por zero"); $$ = (RuntimeValue){.type = TYPE_INT, .data.intVal = 0}; }
    }
    | expression POWER expression         {
        float val1 = ($1.type == TYPE_INT) ? (float)$1.data.intVal : $1.data.floatVal;
        float val2 = ($3.type == TYPE_INT) ? (float)$3.data.intVal : $3.data.floatVal;
        $$ = (RuntimeValue){.type = TYPE_FLOAT, .data.floatVal = pow(val1, val2)};
    }
    | expression EQUAL expression         {
        if ($1.type == TYPE_FLOAT || $3.type == TYPE_FLOAT) {
            float val1 = ($1.type == TYPE_INT) ? (float)$1.data.intVal : $1.data.floatVal;
            float val2 = ($3.type == TYPE_INT) ? (float)$3.data.intVal : $3.data.floatVal;
            $$ = (RuntimeValue){.type = TYPE_INT, .data.intVal = (val1 == val2)};
        } else {
            $$ = (RuntimeValue){.type = TYPE_INT, .data.intVal = ($1.data.intVal == $3.data.intVal)};
        }
    }
    | expression NOT_EQUAL expression     {
        if ($1.type == TYPE_FLOAT || $3.type == TYPE_FLOAT) {
            float val1 = ($1.type == TYPE_INT) ? (float)$1.data.intVal : $1.data.floatVal;
            float val2 = ($3.type == TYPE_INT) ? (float)$3.data.intVal : $3.data.floatVal;
            $$ = (RuntimeValue){.type = TYPE_INT, .data.intVal = (val1 != val2)};
        } else {
            $$ = (RuntimeValue){.type = TYPE_INT, .data.intVal = ($1.data.intVal != $3.data.intVal)};
        }
    }
    | expression LESS_THAN expression     {
        float val1 = ($1.type == TYPE_INT) ? (float)$1.data.intVal : $1.data.floatVal;
        float val2 = ($3.type == TYPE_INT) ? (float)$3.data.intVal : $3.data.floatVal;
        $$ = (RuntimeValue){.type = TYPE_INT, .data.intVal = (val1 < val2)};
    }
    | expression GREATER_THAN expression  {
        float val1 = ($1.type == TYPE_INT) ? (float)$1.data.intVal : $1.data.floatVal;
        float val2 = ($3.type == TYPE_INT) ? (float)$3.data.intVal : $3.data.floatVal;
        $$ = (RuntimeValue){.type = TYPE_INT, .data.intVal = (val1 > val2)};
    }
    | expression LESS_THAN_OR_EQUAL expression {
        float val1 = ($1.type == TYPE_INT) ? (float)$1.data.intVal : $1.data.floatVal;
        float val2 = ($3.type == TYPE_INT) ? (float)$3.data.intVal : $3.data.floatVal;
        $$ = (RuntimeValue){.type = TYPE_INT, .data.intVal = (val1 <= val2)};
    }
    | expression GREATER_THAN_OR_EQUAL expression {
        float val1 = ($1.type == TYPE_INT) ? (float)$1.data.intVal : $1.data.floatVal;
        float val2 = ($3.type == TYPE_INT) ? (float)$3.data.intVal : $3.data.floatVal;
        $$ = (RuntimeValue){.type = TYPE_INT, .data.intVal = (val1 >= val2)};
    }
    | expression AND expression           {
        int val1 = ($1.type == TYPE_FLOAT) ? (int)$1.data.floatVal : $1.data.intVal;
        int val2 = ($3.type == TYPE_FLOAT) ? (int)$3.data.floatVal : $3.data.intVal;
        $$ = (RuntimeValue){.type = TYPE_INT, .data.intVal = (val1 && val2)};
    }
    | expression OR expression            {
        int val1 = ($1.type == TYPE_FLOAT) ? (int)$1.data.floatVal : $1.data.intVal;
        int val2 = ($3.type == TYPE_FLOAT) ? (int)$3.data.floatVal : $3.data.intVal;
        $$ = (RuntimeValue){.type = TYPE_INT, .data.intVal = (val1 || val2)};
    }
    | NOT expression                      {
        int val2 = ($2.type == TYPE_FLOAT) ? (int)$2.data.floatVal : $2.data.intVal;
        $$ = (RuntimeValue){.type = TYPE_INT, .data.intVal = !val2};
    }
    | LEFT_PARENTHESIS expression RIGHT_PARENTHESIS { $$ = $2; }
    ;


array_literal:
    LEFT_SQUARE_BRACKET array_elements_non_empty RIGHT_SQUARE_BRACKET
    ;

array_elements_non_empty:
    expression
    | array_elements_non_empty COMMA expression
    ;

variable:
    ID { $$ = $1; }
    ;

array_access:
    ID LEFT_SQUARE_BRACKET expression RIGHT_SQUARE_BRACKET
    ;

function_call:
    ID LEFT_PARENTHESIS argument_list RIGHT_PARENTHESIS
    ;

argument_list:
    /* vazio */
    | argument_list_non_empty
    ;

argument_list_non_empty:
    expression
    | argument_list_non_empty COMMA expression
    ;

control_structure:
    IF expression block %prec THEN
    | IF expression block ELSE block
    | WHILE expression block
    | FOR LEFT_PARENTHESIS INT ID COLON function_call RIGHT_PARENTHESIS block
    ;

%%

void yyerror(const char *msg) {
    fprintf(stderr, "Erro na linha %d: %s\n", yylineno, msg);
}

void my_printf_runtime(char *format_string, ArgumentNode *args_list) {
    char *p = format_string;
    ArgumentNode *current_arg = args_list;

    if (p[0] == '"' || p[0] == '\'') {
        p++;
    }
    size_t len = strlen(format_string);
    char *end_p = format_string + len;
    if (len > 0 && (*(end_p - 1) == '"' || *(end_p - 1) == '\'')) {
        end_p--;
    }


    while (p < end_p && *p != '\0') {
        if (*p == '%' && *(p+1) != '\0') {
            p++;

            if (*p == '%') {
                printf("%%");
                p++;
                continue;
            }

            if (current_arg == NULL) {
                fprintf(stderr, "Erro de runtime: Número insuficiente de argumentos para printf.\n");
                break;
            }

            switch (*p) {
                case 'd':
                    if (current_arg->value.type == TYPE_INT) {
                        printf("%d", current_arg->value.data.intVal);
                    } else if (current_arg->value.type == TYPE_FLOAT) {
                        printf("%d", (int)current_arg->value.data.floatVal);
                    } else {
                        fprintf(stderr, "Erro de runtime: tipo inesperado para %%d (esperado INT/FLOAT, recebido %d).\n", current_arg->value.type);
                        printf("[TIPO_ERRADO]");
                    }
                    break;
                case 'f':
                    if (current_arg->value.type == TYPE_FLOAT) {
                        printf("%f", current_arg->value.data.floatVal);
                    } else if (current_arg->value.type == TYPE_INT) {
                        printf("%f", (float)current_arg->value.data.intVal);
                    }
                    else {
                        fprintf(stderr, "Erro de runtime: tipo inesperado para %%f (esperado FLOAT/INT, recebido %d).\n", current_arg->value.type);
                        printf("[TIPO_ERRADO]");
                    }
                    break;
                case 's':
                    if (current_arg->value.type == TYPE_STRING) {
                        char *temp_str = strdup(current_arg->value.data.strVal);
                        if (temp_str) {
                            if (strlen(temp_str) >= 2 && (temp_str[0] == '"' || temp_str[0] == '\'') && (temp_str[strlen(temp_str)-1] == '"' || temp_str[strlen(temp_str)-1] == '\'')) {
                                memmove(temp_str, temp_str + 1, strlen(temp_str) - 2);
                                temp_str[strlen(temp_str) - 2] = '\0';
                            }
                            printf("%s", temp_str);
                            free(temp_str);
                        } else {
                            printf("[ERRO_STRING]");
                        }
                    } else {
                        fprintf(stderr, "Erro de runtime: tipo inesperado para %%s (esperado STRING, recebido %d).\n", current_arg->value.type);
                        printf("[TIPO_ERRADO]");
                    }
                    break;
                default:
                    fprintf(stderr, "Aviso de runtime: Especificador de formato desconhecido: %c\n", *p);
                    printf("%%%c", *p);
                    break;
            }
            current_arg = current_arg->next;
        } else if (*p == '\\' && *(p+1) != '\0') {
            p++;
            switch (*p) {
                case 'n': printf("\n"); break;
                case 't': printf("\t"); break;
                case '\\': printf("\\"); break;
                case '"': printf("\""); break;
                case '\'': printf("\'"); break;
                default: printf("\\%c", *p); break;
            }
        }
        else {
            printf("%c", *p);
        }
        p++;
    }

    if (current_arg != NULL) {
        fprintf(stderr, "Aviso de runtime: Argumentos extras fornecidos para printf.\n");
    }
}


void free_argument_list(ArgumentNode *list) {
    ArgumentNode *temp;
    while (list != NULL) {
        temp = list;
        if (temp->value.type == TYPE_STRING && temp->value.data.strVal) {
            free(temp->value.data.strVal);
        }
        list = list->next;
        free(temp);
    }
}

RuntimeValue runtime_input() {
    char buffer[256];
    printf("> ");
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        buffer[strcspn(buffer, "\n")] = 0;

        char *endptr;

        long int_candidate = strtol(buffer, &endptr, 10);
        if (*endptr == '\0' && endptr != buffer) {
            return (RuntimeValue){.type = TYPE_INT, .data.intVal = (int)int_candidate};
        }

        float float_candidate = strtof(buffer, &endptr);
        if (*endptr == '\0' && endptr != buffer) {
            return (RuntimeValue){.type = TYPE_FLOAT, .data.floatVal = float_candidate};
        }

        return (RuntimeValue){.type = TYPE_STRING, .data.strVal = strdup(buffer)};
    }

    fprintf(stderr, "Erro ao ler input ou EOF alcançado.\n");
    return (RuntimeValue){.type = TYPE_INT, .data.intVal = 0};
}

int main(int argc, char *argv[]) {
    #if YYDEBUG
        yydebug = 1;
    #endif

    init_symbol_table();

    if (argc > 1) {
        FILE *file = fopen(argv[1], "r");
        if (!file) {
            perror(argv[1]);
            return 1;
        }
        yyin = file;
    } else {
        yyin = stdin;
    }

    if (yyparse() == 0) {
        printf("Análise concluída com sucesso.\n");
        return 0;
    } else {
        printf("Análise falhou.\n");
        return 1;
    }

    free_symbol_table_memory();
    return 0;
}