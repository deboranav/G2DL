/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    FUNCTION = 258,                /* FUNCTION  */
    RETURN = 259,                  /* RETURN  */
    BREAK = 260,                   /* BREAK  */
    IF = 261,                      /* IF  */
    ELSE = 262,                    /* ELSE  */
    WHILE = 263,                   /* WHILE  */
    FOR = 264,                     /* FOR  */
    TRUE = 265,                    /* TRUE  */
    FALSE = 266,                   /* FALSE  */
    INT = 267,                     /* INT  */
    STRING = 268,                  /* STRING  */
    ID = 269,                      /* ID  */
    STRING_LITERAL = 270,          /* STRING_LITERAL  */
    INTEGER = 271,                 /* INTEGER  */
    FLOAT = 272,                   /* FLOAT  */
    ASSIGNMENT = 273,              /* ASSIGNMENT  */
    PLUS = 274,                    /* PLUS  */
    MINUS = 275,                   /* MINUS  */
    MULTIPLY = 276,                /* MULTIPLY  */
    DIVIDE = 277,                  /* DIVIDE  */
    MOD = 278,                     /* MOD  */
    POWER = 279,                   /* POWER  */
    EQUAL = 280,                   /* EQUAL  */
    NOT_EQUAL = 281,               /* NOT_EQUAL  */
    LESS_THAN = 282,               /* LESS_THAN  */
    GREATER_THAN = 283,            /* GREATER_THAN  */
    LESS_THAN_OR_EQUAL = 284,      /* LESS_THAN_OR_EQUAL  */
    GREATER_THAN_OR_EQUAL = 285,   /* GREATER_THAN_OR_EQUAL  */
    AND = 286,                     /* AND  */
    OR = 287,                      /* OR  */
    NOT = 288,                     /* NOT  */
    PLUS_ASSIGNMENT = 289,         /* PLUS_ASSIGNMENT  */
    MINUS_ASSIGNMENT = 290,        /* MINUS_ASSIGNMENT  */
    MULTIPLY_ASSIGNMENT = 291,     /* MULTIPLY_ASSIGNMENT  */
    DIVIDE_ASSIGNMENT = 292,       /* DIVIDE_ASSIGNMENT  */
    MOD_ASSIGNMENT = 293,          /* MOD_ASSIGNMENT  */
    POWER_ASSIGNMENT = 294,        /* POWER_ASSIGNMENT  */
    LEFT_PARENTHESIS = 295,        /* LEFT_PARENTHESIS  */
    RIGHT_PARENTHESIS = 296,       /* RIGHT_PARENTHESIS  */
    LEFT_CURLY_BRACKET = 297,      /* LEFT_CURLY_BRACKET  */
    RIGHT_CURLY_BRACKET = 298,     /* RIGHT_CURLY_BRACKET  */
    LEFT_SQUARE_BRACKET = 299,     /* LEFT_SQUARE_BRACKET  */
    RIGHT_SQUARE_BRACKET = 300,    /* RIGHT_SQUARE_BRACKET  */
    COMMA = 301,                   /* COMMA  */
    COLON = 302                    /* COLON  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define FUNCTION 258
#define RETURN 259
#define BREAK 260
#define IF 261
#define ELSE 262
#define WHILE 263
#define FOR 264
#define TRUE 265
#define FALSE 266
#define INT 267
#define STRING 268
#define ID 269
#define STRING_LITERAL 270
#define INTEGER 271
#define FLOAT 272
#define ASSIGNMENT 273
#define PLUS 274
#define MINUS 275
#define MULTIPLY 276
#define DIVIDE 277
#define MOD 278
#define POWER 279
#define EQUAL 280
#define NOT_EQUAL 281
#define LESS_THAN 282
#define GREATER_THAN 283
#define LESS_THAN_OR_EQUAL 284
#define GREATER_THAN_OR_EQUAL 285
#define AND 286
#define OR 287
#define NOT 288
#define PLUS_ASSIGNMENT 289
#define MINUS_ASSIGNMENT 290
#define MULTIPLY_ASSIGNMENT 291
#define DIVIDE_ASSIGNMENT 292
#define MOD_ASSIGNMENT 293
#define POWER_ASSIGNMENT 294
#define LEFT_PARENTHESIS 295
#define RIGHT_PARENTHESIS 296
#define LEFT_CURLY_BRACKET 297
#define RIGHT_CURLY_BRACKET 298
#define LEFT_SQUARE_BRACKET 299
#define RIGHT_SQUARE_BRACKET 300
#define COMMA 301
#define COLON 302

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 9 "parser.y"

    int intVal;
    float floatVal;
    char *strVal;

#line 167 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
