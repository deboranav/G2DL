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

#ifndef YY_YY_PARSER_G2DL_TAB_H_INCLUDED
# define YY_YY_PARSER_G2DL_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
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
    FLOAT = 269,                   /* FLOAT  */
    ID = 270,                      /* ID  */
    STRING_LITERAL = 271,          /* STRING_LITERAL  */
    INTEGER = 272,                 /* INTEGER  */
    FLOAT_LITERAL = 273,           /* FLOAT_LITERAL  */
    ASSIGNMENT = 274,              /* ASSIGNMENT  */
    PLUS = 275,                    /* PLUS  */
    MINUS = 276,                   /* MINUS  */
    MULTIPLY = 277,                /* MULTIPLY  */
    DIVIDE = 278,                  /* DIVIDE  */
    MOD = 279,                     /* MOD  */
    POWER = 280,                   /* POWER  */
    EQUAL = 281,                   /* EQUAL  */
    NOT_EQUAL = 282,               /* NOT_EQUAL  */
    LESS_THAN = 283,               /* LESS_THAN  */
    GREATER_THAN = 284,            /* GREATER_THAN  */
    LESS_THAN_OR_EQUAL = 285,      /* LESS_THAN_OR_EQUAL  */
    GREATER_THAN_OR_EQUAL = 286,   /* GREATER_THAN_OR_EQUAL  */
    AND = 287,                     /* AND  */
    OR = 288,                      /* OR  */
    NOT = 289,                     /* NOT  */
    PLUS_ASSIGNMENT = 290,         /* PLUS_ASSIGNMENT  */
    MINUS_ASSIGNMENT = 291,        /* MINUS_ASSIGNMENT  */
    MULTIPLY_ASSIGNMENT = 292,     /* MULTIPLY_ASSIGNMENT  */
    DIVIDE_ASSIGNMENT = 293,       /* DIVIDE_ASSIGNMENT  */
    MOD_ASSIGNMENT = 294,          /* MOD_ASSIGNMENT  */
    POWER_ASSIGNMENT = 295,        /* POWER_ASSIGNMENT  */
    LEFT_PARENTHESIS = 296,        /* LEFT_PARENTHESIS  */
    RIGHT_PARENTHESIS = 297,       /* RIGHT_PARENTHESIS  */
    LEFT_CURLY_BRACKET = 298,      /* LEFT_CURLY_BRACKET  */
    RIGHT_CURLY_BRACKET = 299,     /* RIGHT_CURLY_BRACKET  */
    LEFT_SQUARE_BRACKET = 300,     /* LEFT_SQUARE_BRACKET  */
    RIGHT_SQUARE_BRACKET = 301,    /* RIGHT_SQUARE_BRACKET  */
    COMMA = 302,                   /* COMMA  */
    COLON = 303,                   /* COLON  */
    PRINTF = 304,                  /* PRINTF  */
    THEN = 305,                    /* THEN  */
    ARRAY_LITERAL = 306            /* ARRAY_LITERAL  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 16 "parser_g2dl.y"

    int intVal;
    float floatVal;
    char *strVal;

#line 121 "parser_g2dl.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_G2DL_TAB_H_INCLUDED  */
