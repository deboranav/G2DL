/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser_g2dl.y"

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

#line 91 "parser_g2dl.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser_g2dl.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_FUNCTION = 3,                   /* FUNCTION  */
  YYSYMBOL_RETURN = 4,                     /* RETURN  */
  YYSYMBOL_BREAK = 5,                      /* BREAK  */
  YYSYMBOL_IF = 6,                         /* IF  */
  YYSYMBOL_ELSE = 7,                       /* ELSE  */
  YYSYMBOL_WHILE = 8,                      /* WHILE  */
  YYSYMBOL_FOR = 9,                        /* FOR  */
  YYSYMBOL_TRUE = 10,                      /* TRUE  */
  YYSYMBOL_FALSE = 11,                     /* FALSE  */
  YYSYMBOL_INT = 12,                       /* INT  */
  YYSYMBOL_STRING = 13,                    /* STRING  */
  YYSYMBOL_FLOAT = 14,                     /* FLOAT  */
  YYSYMBOL_ID = 15,                        /* ID  */
  YYSYMBOL_STRING_LITERAL = 16,            /* STRING_LITERAL  */
  YYSYMBOL_INTEGER = 17,                   /* INTEGER  */
  YYSYMBOL_FLOAT_LITERAL = 18,             /* FLOAT_LITERAL  */
  YYSYMBOL_ASSIGNMENT = 19,                /* ASSIGNMENT  */
  YYSYMBOL_PLUS = 20,                      /* PLUS  */
  YYSYMBOL_MINUS = 21,                     /* MINUS  */
  YYSYMBOL_MULTIPLY = 22,                  /* MULTIPLY  */
  YYSYMBOL_DIVIDE = 23,                    /* DIVIDE  */
  YYSYMBOL_MOD = 24,                       /* MOD  */
  YYSYMBOL_POWER = 25,                     /* POWER  */
  YYSYMBOL_EQUAL = 26,                     /* EQUAL  */
  YYSYMBOL_NOT_EQUAL = 27,                 /* NOT_EQUAL  */
  YYSYMBOL_LESS_THAN = 28,                 /* LESS_THAN  */
  YYSYMBOL_GREATER_THAN = 29,              /* GREATER_THAN  */
  YYSYMBOL_LESS_THAN_OR_EQUAL = 30,        /* LESS_THAN_OR_EQUAL  */
  YYSYMBOL_GREATER_THAN_OR_EQUAL = 31,     /* GREATER_THAN_OR_EQUAL  */
  YYSYMBOL_AND = 32,                       /* AND  */
  YYSYMBOL_OR = 33,                        /* OR  */
  YYSYMBOL_NOT = 34,                       /* NOT  */
  YYSYMBOL_PLUS_ASSIGNMENT = 35,           /* PLUS_ASSIGNMENT  */
  YYSYMBOL_MINUS_ASSIGNMENT = 36,          /* MINUS_ASSIGNMENT  */
  YYSYMBOL_MULTIPLY_ASSIGNMENT = 37,       /* MULTIPLY_ASSIGNMENT  */
  YYSYMBOL_DIVIDE_ASSIGNMENT = 38,         /* DIVIDE_ASSIGNMENT  */
  YYSYMBOL_MOD_ASSIGNMENT = 39,            /* MOD_ASSIGNMENT  */
  YYSYMBOL_POWER_ASSIGNMENT = 40,          /* POWER_ASSIGNMENT  */
  YYSYMBOL_LEFT_PARENTHESIS = 41,          /* LEFT_PARENTHESIS  */
  YYSYMBOL_RIGHT_PARENTHESIS = 42,         /* RIGHT_PARENTHESIS  */
  YYSYMBOL_LEFT_CURLY_BRACKET = 43,        /* LEFT_CURLY_BRACKET  */
  YYSYMBOL_RIGHT_CURLY_BRACKET = 44,       /* RIGHT_CURLY_BRACKET  */
  YYSYMBOL_LEFT_SQUARE_BRACKET = 45,       /* LEFT_SQUARE_BRACKET  */
  YYSYMBOL_RIGHT_SQUARE_BRACKET = 46,      /* RIGHT_SQUARE_BRACKET  */
  YYSYMBOL_COMMA = 47,                     /* COMMA  */
  YYSYMBOL_COLON = 48,                     /* COLON  */
  YYSYMBOL_PRINTF = 49,                    /* PRINTF  */
  YYSYMBOL_INPUT = 50,                     /* INPUT  */
  YYSYMBOL_THEN = 51,                      /* THEN  */
  YYSYMBOL_52_ = 52,                       /* ';'  */
  YYSYMBOL_YYACCEPT = 53,                  /* $accept  */
  YYSYMBOL_program = 54,                   /* program  */
  YYSYMBOL_statements = 55,                /* statements  */
  YYSYMBOL_statement = 56,                 /* statement  */
  YYSYMBOL_printf_statement = 57,          /* printf_statement  */
  YYSYMBOL_argument_list_printf = 58,      /* argument_list_printf  */
  YYSYMBOL_function_decl = 59,             /* function_decl  */
  YYSYMBOL_parameters = 60,                /* parameters  */
  YYSYMBOL_parameter_list = 61,            /* parameter_list  */
  YYSYMBOL_block = 62,                     /* block  */
  YYSYMBOL_assignment = 63,                /* assignment  */
  YYSYMBOL_assignment_operator = 64,       /* assignment_operator  */
  YYSYMBOL_expression = 65,                /* expression  */
  YYSYMBOL_array_literal = 66,             /* array_literal  */
  YYSYMBOL_array_elements_non_empty = 67,  /* array_elements_non_empty  */
  YYSYMBOL_variable = 68,                  /* variable  */
  YYSYMBOL_array_access = 69,              /* array_access  */
  YYSYMBOL_function_call = 70,             /* function_call  */
  YYSYMBOL_argument_list = 71,             /* argument_list  */
  YYSYMBOL_argument_list_non_empty = 72,   /* argument_list_non_empty  */
  YYSYMBOL_control_structure = 73          /* control_structure  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  49
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   385

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  53
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  21
/* YYNRULES -- Number of rules.  */
#define YYNRULES  73
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  139

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   306


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    52,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    66,    66,    67,    71,    72,    76,    77,    78,    79,
      80,    86,    87,    88,    92,    98,   103,   149,   154,   169,
     172,   174,   178,   179,   183,   187,   198,   202,   203,   204,
     205,   206,   207,   208,   212,   213,   214,   215,   230,   231,
     232,   233,   234,   235,   239,   244,   249,   254,   260,   266,
     271,   280,   289,   294,   299,   304,   309,   314,   319,   323,
     328,   332,   333,   337,   341,   345,   348,   350,   354,   355,
     359,   360,   361,   362
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "FUNCTION", "RETURN",
  "BREAK", "IF", "ELSE", "WHILE", "FOR", "TRUE", "FALSE", "INT", "STRING",
  "FLOAT", "ID", "STRING_LITERAL", "INTEGER", "FLOAT_LITERAL",
  "ASSIGNMENT", "PLUS", "MINUS", "MULTIPLY", "DIVIDE", "MOD", "POWER",
  "EQUAL", "NOT_EQUAL", "LESS_THAN", "GREATER_THAN", "LESS_THAN_OR_EQUAL",
  "GREATER_THAN_OR_EQUAL", "AND", "OR", "NOT", "PLUS_ASSIGNMENT",
  "MINUS_ASSIGNMENT", "MULTIPLY_ASSIGNMENT", "DIVIDE_ASSIGNMENT",
  "MOD_ASSIGNMENT", "POWER_ASSIGNMENT", "LEFT_PARENTHESIS",
  "RIGHT_PARENTHESIS", "LEFT_CURLY_BRACKET", "RIGHT_CURLY_BRACKET",
  "LEFT_SQUARE_BRACKET", "RIGHT_SQUARE_BRACKET", "COMMA", "COLON",
  "PRINTF", "INPUT", "THEN", "';'", "$accept", "program", "statements",
  "statement", "printf_statement", "argument_list_printf", "function_decl",
  "parameters", "parameter_list", "block", "assignment",
  "assignment_operator", "expression", "array_literal",
  "array_elements_non_empty", "variable", "array_access", "function_call",
  "argument_list", "argument_list_non_empty", "control_structure", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-45)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-4)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      87,   -44,     3,   200,   200,   200,    -5,   -45,   -45,   -24,
     -45,   -45,   -45,   200,   200,   179,   200,    37,    38,    28,
     109,   -45,   -45,   -45,   -45,    29,   231,   -45,   -13,   -13,
     -45,   -45,   -45,    39,   245,   -45,   -45,   305,   305,    70,
     200,   200,   -45,   329,   159,   352,   -31,    32,    41,   -45,
     -45,   -45,   200,   200,   200,   200,   200,   200,   200,   200,
     200,   200,   200,   200,   200,   200,   -45,   -45,   -45,   -45,
     -45,   -45,   -45,   -45,   200,   200,    69,   -45,    82,   -45,
      77,   352,    52,    53,   278,   -45,   -45,   -45,   200,    57,
     -35,   -45,     8,     8,    81,    81,    81,    81,    45,    45,
      21,    21,    21,    21,   292,   264,   352,   352,   -45,    65,
      61,    71,    74,   -45,   200,   -45,   352,    83,    86,   200,
      71,   108,   -45,   114,   352,   -45,   -45,   -33,   352,   -45,
     -45,    92,    97,    88,   200,    71,   -45,   352,   -45
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,    41,    42,    63,
      36,    34,    35,     0,     0,     0,     0,     0,     0,     0,
       0,     4,    11,     6,    12,     0,     0,    40,    37,    39,
      38,     9,    13,     0,     0,    37,    39,     0,     0,     0,
      66,     0,    58,     0,     0,    61,     0,     0,     0,     1,
       5,     7,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     8,    27,    28,    29,
      30,    31,    32,    33,     0,     0,    20,    10,    70,    72,
       0,    68,     0,    67,     0,    59,    24,    60,     0,     0,
       0,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    25,    26,    22,     0,
      21,     0,     0,    65,     0,    64,    62,     0,     0,     0,
       0,     0,    71,     0,    69,    16,    15,     0,    17,    19,
      23,     0,     0,     0,     0,     0,    14,    18,    73
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -45,   -45,   119,   -15,   -45,   -45,   -45,   -45,   -45,   -34,
     -45,   112,    -3,   -45,   -45,    19,    20,    22,   -45,   -45,
     -45
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,    19,    20,    21,    22,   127,    23,   109,   110,    24,
      25,    74,    26,    27,    46,    35,    36,    30,    82,    83,
      31
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      34,    37,    38,    78,    79,    50,    67,   118,    32,   133,
      42,    43,   119,    45,   134,    87,    88,    40,    33,    28,
      29,    41,    68,    69,    70,    71,    72,    73,    49,    50,
      54,    55,    56,    57,    28,    29,    39,    81,    84,    28,
      29,    52,    53,    54,    55,    56,    57,    89,    90,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,    28,    29,    52,    53,    54,    55,    56,
      57,   106,   107,    60,    61,    62,    63,   122,    47,    48,
      76,    51,    80,    91,   108,   116,   129,    -3,     1,   111,
       2,     3,   112,     4,   113,     5,     6,     7,     8,   117,
     114,   138,     9,    10,    11,    12,    57,   120,   121,    -2,
       1,   124,     2,     3,    15,     4,   128,     5,     6,     7,
       8,    13,   123,   130,     9,    10,    11,    12,    14,   131,
      15,   137,    16,    40,    44,   125,    17,    18,   126,   135,
     136,    75,     0,    13,     0,   132,     0,     0,     0,     0,
      14,     0,    15,     0,    16,     0,     0,     0,    17,    18,
       1,     0,     2,     3,     0,     4,     0,     5,     6,     7,
       8,     0,     0,     0,     9,    10,    11,    12,     0,     0,
       1,     0,     2,     3,     0,     4,     0,     5,     6,     7,
       8,     0,     0,    13,     9,    10,    11,    12,     0,     0,
      14,     0,    15,    86,    16,     0,     0,     0,    17,    18,
       7,     8,     0,    13,     0,     9,    10,    11,    12,     0,
      14,     0,    15,     0,    16,     0,     0,     0,    17,    18,
       0,     0,     0,     0,    13,     0,     0,     0,     0,     0,
       0,    14,     0,     0,     0,    16,     0,     0,     0,     0,
      18,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,     0,
       0,     0,     0,    66,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    77,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,   115,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    15,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,     0,     0,     0,     0,     0,     0,     0,
       0,    85,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65
};

static const yytype_int16 yycheck[] =
{
       3,     4,     5,    37,    38,    20,    19,    42,    52,    42,
      13,    14,    47,    16,    47,    46,    47,    41,    15,     0,
       0,    45,    35,    36,    37,    38,    39,    40,     0,    44,
      22,    23,    24,    25,    15,    15,    41,    40,    41,    20,
      20,    20,    21,    22,    23,    24,    25,    15,    16,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    44,    44,    20,    21,    22,    23,    24,
      25,    74,    75,    28,    29,    30,    31,   111,    41,    41,
      41,    52,    12,    42,    15,    88,   120,     0,     1,     7,
       3,     4,    15,     6,    42,     8,     9,    10,    11,    42,
      47,   135,    15,    16,    17,    18,    25,    42,    47,     0,
       1,   114,     3,     4,    43,     6,   119,     8,     9,    10,
      11,    34,    48,    15,    15,    16,    17,    18,    41,    15,
      43,   134,    45,    41,    15,    52,    49,    50,    52,    42,
      52,    29,    -1,    34,    -1,   123,    -1,    -1,    -1,    -1,
      41,    -1,    43,    -1,    45,    -1,    -1,    -1,    49,    50,
       1,    -1,     3,     4,    -1,     6,    -1,     8,     9,    10,
      11,    -1,    -1,    -1,    15,    16,    17,    18,    -1,    -1,
       1,    -1,     3,     4,    -1,     6,    -1,     8,     9,    10,
      11,    -1,    -1,    34,    15,    16,    17,    18,    -1,    -1,
      41,    -1,    43,    44,    45,    -1,    -1,    -1,    49,    50,
      10,    11,    -1,    34,    -1,    15,    16,    17,    18,    -1,
      41,    -1,    43,    -1,    45,    -1,    -1,    -1,    49,    50,
      -1,    -1,    -1,    -1,    34,    -1,    -1,    -1,    -1,    -1,
      -1,    41,    -1,    -1,    -1,    45,    -1,    -1,    -1,    -1,
      50,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    -1,
      -1,    -1,    -1,    52,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    52,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    46,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    42,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     1,     3,     4,     6,     8,     9,    10,    11,    15,
      16,    17,    18,    34,    41,    43,    45,    49,    50,    54,
      55,    56,    57,    59,    62,    63,    65,    66,    68,    69,
      70,    73,    52,    15,    65,    68,    69,    65,    65,    41,
      41,    45,    65,    65,    55,    65,    67,    41,    41,     0,
      56,    52,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    52,    19,    35,    36,
      37,    38,    39,    40,    64,    64,    41,    52,    62,    62,
      12,    65,    71,    72,    65,    42,    44,    46,    47,    15,
      16,    42,    65,    65,    65,    65,    65,    65,    65,    65,
      65,    65,    65,    65,    65,    65,    65,    65,    15,    60,
      61,     7,    15,    42,    47,    46,    65,    42,    42,    47,
      42,    47,    62,    48,    65,    52,    52,    58,    65,    62,
      15,    15,    70,    42,    47,    42,    52,    65,    62
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    53,    54,    54,    55,    55,    56,    56,    56,    56,
      56,    56,    56,    56,    57,    57,    57,    58,    58,    59,
      60,    60,    61,    61,    62,    63,    63,    64,    64,    64,
      64,    64,    64,    64,    65,    65,    65,    65,    65,    65,
      65,    65,    65,    65,    65,    65,    65,    65,    65,    65,
      65,    65,    65,    65,    65,    65,    65,    65,    65,    65,
      66,    67,    67,    68,    69,    70,    71,    71,    72,    72,
      73,    73,    73,    73
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     1,     2,     1,     2,     2,     1,
       3,     1,     1,     2,     7,     5,     5,     1,     3,     6,
       0,     1,     1,     3,     3,     3,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     2,     3,
       3,     1,     3,     1,     4,     4,     0,     1,     1,     3,
       3,     5,     3,     8
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 10: /* statement: RETURN expression ';'  */
#line 80 "parser_g2dl.y"
                            { printf("Retornando valor (tipo %d): ", (yyvsp[-1].runtimeVal).type);
                                 if ((yyvsp[-1].runtimeVal).type == TYPE_INT) printf("%d\n", (yyvsp[-1].runtimeVal).data.intVal);
                                 else if ((yyvsp[-1].runtimeVal).type == TYPE_FLOAT) printf("%f\n", (yyvsp[-1].runtimeVal).data.floatVal);
                                 else if ((yyvsp[-1].runtimeVal).type == TYPE_STRING) printf("%s\n", (yyvsp[-1].runtimeVal).data.strVal);
                                 if ((yyvsp[-1].runtimeVal).type == TYPE_STRING && (yyvsp[-1].runtimeVal).data.strVal) free((yyvsp[-1].runtimeVal).data.strVal);
                               }
#line 1301 "parser_g2dl.tab.c"
    break;

  case 13: /* statement: error ';'  */
#line 88 "parser_g2dl.y"
                { fprintf(stderr, "Erro de sintaxe na linha %d. Tentando recuperar em ';'\n", yylineno); yyerrok; }
#line 1307 "parser_g2dl.tab.c"
    break;

  case 14: /* printf_statement: PRINTF LEFT_PARENTHESIS STRING_LITERAL COMMA argument_list_printf RIGHT_PARENTHESIS ';'  */
#line 93 "parser_g2dl.y"
    {
        my_printf_runtime((yyvsp[-4].strVal), (yyvsp[-2].argList));
        free((yyvsp[-4].strVal));
        free_argument_list((yyvsp[-2].argList));
    }
#line 1317 "parser_g2dl.tab.c"
    break;

  case 15: /* printf_statement: PRINTF LEFT_PARENTHESIS STRING_LITERAL RIGHT_PARENTHESIS ';'  */
#line 99 "parser_g2dl.y"
    {
        my_printf_runtime((yyvsp[-2].strVal), NULL);
        free((yyvsp[-2].strVal));
    }
#line 1326 "parser_g2dl.tab.c"
    break;

  case 16: /* printf_statement: PRINTF LEFT_PARENTHESIS ID RIGHT_PARENTHESIS ';'  */
#line 104 "parser_g2dl.y"
    {

        Symbol *sym = lookup_symbol((yyvsp[-2].strVal));

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
            fprintf(stderr, "Erro de runtime: Variável '%s' não definida na linha %d para printf.\n", (yyvsp[-2].strVal), yylineno);
            yyerror("Variável não definida em printf()");
        }
        free((yyvsp[-2].strVal));
    }
#line 1373 "parser_g2dl.tab.c"
    break;

  case 17: /* argument_list_printf: expression  */
#line 149 "parser_g2dl.y"
               { (yyval.argList) = (ArgumentNode *)malloc(sizeof(ArgumentNode));
                 if (!(yyval.argList)) { perror("malloc"); exit(EXIT_FAILURE); }
                 (yyval.argList)->value = (yyvsp[0].runtimeVal);
                 (yyval.argList)->next = NULL;
               }
#line 1383 "parser_g2dl.tab.c"
    break;

  case 18: /* argument_list_printf: argument_list_printf COMMA expression  */
#line 154 "parser_g2dl.y"
                                            {
                     ArgumentNode *newNode = (ArgumentNode *)malloc(sizeof(ArgumentNode));
                     if (!newNode) { perror("malloc"); exit(EXIT_FAILURE); }
                     newNode->value = (yyvsp[0].runtimeVal);
                     newNode->next = NULL;
                     ArgumentNode *current = (yyvsp[-2].argList);
                     while (current->next != NULL) {
                         current = current->next;
                     }
                     current->next = newNode;
                     (yyval.argList) = (yyvsp[-2].argList);
                   }
#line 1400 "parser_g2dl.tab.c"
    break;

  case 25: /* assignment: variable assignment_operator expression  */
#line 187 "parser_g2dl.y"
                                            {
        printf("Atribuição para a variável %s. Valor: ", (yyvsp[-2].strVal));
        if ((yyvsp[0].runtimeVal).type == TYPE_INT) printf("%d\n", (yyvsp[0].runtimeVal).data.intVal);
        else if ((yyvsp[0].runtimeVal).type == TYPE_FLOAT) printf("%f\n", (yyvsp[0].runtimeVal).data.floatVal);
        else if ((yyvsp[0].runtimeVal).type == TYPE_STRING) printf("%s\n", (yyvsp[0].runtimeVal).data.strVal);
        printf("\n");

        insert_symbol((yyvsp[-2].strVal), (yyvsp[0].runtimeVal));

        free((yyvsp[-2].strVal));
    }
#line 1416 "parser_g2dl.tab.c"
    break;

  case 34: /* expression: INTEGER  */
#line 212 "parser_g2dl.y"
                                { (yyval.runtimeVal) = (RuntimeValue){.type = TYPE_INT, .data.intVal = (yyvsp[0].intVal)}; }
#line 1422 "parser_g2dl.tab.c"
    break;

  case 35: /* expression: FLOAT_LITERAL  */
#line 213 "parser_g2dl.y"
                                { (yyval.runtimeVal) = (RuntimeValue){.type = TYPE_FLOAT, .data.floatVal = (yyvsp[0].floatVal)}; }
#line 1428 "parser_g2dl.tab.c"
    break;

  case 36: /* expression: STRING_LITERAL  */
#line 214 "parser_g2dl.y"
                                { (yyval.runtimeVal) = (RuntimeValue){.type = TYPE_STRING, .data.strVal = (yyvsp[0].strVal)}; }
#line 1434 "parser_g2dl.tab.c"
    break;

  case 37: /* expression: variable  */
#line 215 "parser_g2dl.y"
                                {
        printf("Usando variável %s\n", (yyvsp[0].strVal));
        Symbol *sym = lookup_symbol((yyvsp[0].strVal));
        if (sym != NULL) {
            (yyval.runtimeVal) = sym->value;
            if ((yyval.runtimeVal).type == TYPE_STRING && (yyval.runtimeVal).data.strVal != NULL) {
                (yyval.runtimeVal).data.strVal = strdup((yyval.runtimeVal).data.strVal);
            }
        } else {
            fprintf(stderr, "Erro de runtime: Variável '%s' não definida na linha %d.\n", (yyvsp[0].strVal), yylineno);
            yyerror("Variável não definida");
            (yyval.runtimeVal) = (RuntimeValue){.type = TYPE_INT, .data.intVal = 0};
        }
        free((yyvsp[0].strVal));
    }
#line 1454 "parser_g2dl.tab.c"
    break;

  case 38: /* expression: function_call  */
#line 230 "parser_g2dl.y"
                                { (yyval.runtimeVal) = (RuntimeValue){.type = TYPE_FLOAT, .data.floatVal = 0.0}; }
#line 1460 "parser_g2dl.tab.c"
    break;

  case 39: /* expression: array_access  */
#line 231 "parser_g2dl.y"
                                { (yyval.runtimeVal) = (RuntimeValue){.type = TYPE_FLOAT, .data.floatVal = 0.0}; }
#line 1466 "parser_g2dl.tab.c"
    break;

  case 40: /* expression: array_literal  */
#line 232 "parser_g2dl.y"
                                { (yyval.runtimeVal) = (RuntimeValue){.type = TYPE_FLOAT, .data.floatVal = 0.0}; }
#line 1472 "parser_g2dl.tab.c"
    break;

  case 41: /* expression: TRUE  */
#line 233 "parser_g2dl.y"
                                { (yyval.runtimeVal) = (RuntimeValue){.type = TYPE_INT, .data.intVal = 1}; }
#line 1478 "parser_g2dl.tab.c"
    break;

  case 42: /* expression: FALSE  */
#line 234 "parser_g2dl.y"
                                { (yyval.runtimeVal) = (RuntimeValue){.type = TYPE_INT, .data.intVal = 0}; }
#line 1484 "parser_g2dl.tab.c"
    break;

  case 43: /* expression: INPUT LEFT_PARENTHESIS RIGHT_PARENTHESIS  */
#line 235 "parser_g2dl.y"
                                               {
        printf("Chamada de input(). Aguardando entrada...\n");
        (yyval.runtimeVal) = runtime_input();
    }
#line 1493 "parser_g2dl.tab.c"
    break;

  case 44: /* expression: expression PLUS expression  */
#line 239 "parser_g2dl.y"
                                          {
        float val1 = ((yyvsp[-2].runtimeVal).type == TYPE_INT) ? (float)(yyvsp[-2].runtimeVal).data.intVal : (yyvsp[-2].runtimeVal).data.floatVal;
        float val2 = ((yyvsp[0].runtimeVal).type == TYPE_INT) ? (float)(yyvsp[0].runtimeVal).data.intVal : (yyvsp[0].runtimeVal).data.floatVal;
        (yyval.runtimeVal) = (RuntimeValue){.type = TYPE_FLOAT, .data.floatVal = val1 + val2};
    }
#line 1503 "parser_g2dl.tab.c"
    break;

  case 45: /* expression: expression MINUS expression  */
#line 244 "parser_g2dl.y"
                                          {
        float val1 = ((yyvsp[-2].runtimeVal).type == TYPE_INT) ? (float)(yyvsp[-2].runtimeVal).data.intVal : (yyvsp[-2].runtimeVal).data.floatVal;
        float val2 = ((yyvsp[0].runtimeVal).type == TYPE_INT) ? (float)(yyvsp[0].runtimeVal).data.intVal : (yyvsp[0].runtimeVal).data.floatVal;
        (yyval.runtimeVal) = (RuntimeValue){.type = TYPE_FLOAT, .data.floatVal = val1 - val2};
    }
#line 1513 "parser_g2dl.tab.c"
    break;

  case 46: /* expression: expression MULTIPLY expression  */
#line 249 "parser_g2dl.y"
                                          {
        float val1 = ((yyvsp[-2].runtimeVal).type == TYPE_INT) ? (float)(yyvsp[-2].runtimeVal).data.intVal : (yyvsp[-2].runtimeVal).data.floatVal;
        float val2 = ((yyvsp[0].runtimeVal).type == TYPE_INT) ? (float)(yyvsp[0].runtimeVal).data.intVal : (yyvsp[0].runtimeVal).data.floatVal;
        (yyval.runtimeVal) = (RuntimeValue){.type = TYPE_FLOAT, .data.floatVal = val1 * val2};
    }
#line 1523 "parser_g2dl.tab.c"
    break;

  case 47: /* expression: expression DIVIDE expression  */
#line 254 "parser_g2dl.y"
                                          {
        float val1 = ((yyvsp[-2].runtimeVal).type == TYPE_INT) ? (float)(yyvsp[-2].runtimeVal).data.intVal : (yyvsp[-2].runtimeVal).data.floatVal;
        float val2 = ((yyvsp[0].runtimeVal).type == TYPE_INT) ? (float)(yyvsp[0].runtimeVal).data.intVal : (yyvsp[0].runtimeVal).data.floatVal;
        if(val2 != 0) (yyval.runtimeVal) = (RuntimeValue){.type = TYPE_FLOAT, .data.floatVal = val1 / val2};
        else { yyerror("Divisão por zero"); (yyval.runtimeVal) = (RuntimeValue){.type = TYPE_FLOAT, .data.floatVal = 0.0}; }
    }
#line 1534 "parser_g2dl.tab.c"
    break;

  case 48: /* expression: expression MOD expression  */
#line 260 "parser_g2dl.y"
                                          {
        int val1 = ((yyvsp[-2].runtimeVal).type == TYPE_FLOAT) ? (int)(yyvsp[-2].runtimeVal).data.floatVal : (yyvsp[-2].runtimeVal).data.intVal;
        int val2 = ((yyvsp[0].runtimeVal).type == TYPE_FLOAT) ? (int)(yyvsp[0].runtimeVal).data.floatVal : (yyvsp[0].runtimeVal).data.intVal;
        if(val2 != 0) (yyval.runtimeVal) = (RuntimeValue){.type = TYPE_INT, .data.intVal = val1 % val2};
        else { yyerror("Modulo por zero"); (yyval.runtimeVal) = (RuntimeValue){.type = TYPE_INT, .data.intVal = 0}; }
    }
#line 1545 "parser_g2dl.tab.c"
    break;

  case 49: /* expression: expression POWER expression  */
#line 266 "parser_g2dl.y"
                                          {
        float val1 = ((yyvsp[-2].runtimeVal).type == TYPE_INT) ? (float)(yyvsp[-2].runtimeVal).data.intVal : (yyvsp[-2].runtimeVal).data.floatVal;
        float val2 = ((yyvsp[0].runtimeVal).type == TYPE_INT) ? (float)(yyvsp[0].runtimeVal).data.intVal : (yyvsp[0].runtimeVal).data.floatVal;
        (yyval.runtimeVal) = (RuntimeValue){.type = TYPE_FLOAT, .data.floatVal = pow(val1, val2)};
    }
#line 1555 "parser_g2dl.tab.c"
    break;

  case 50: /* expression: expression EQUAL expression  */
#line 271 "parser_g2dl.y"
                                          {
        if ((yyvsp[-2].runtimeVal).type == TYPE_FLOAT || (yyvsp[0].runtimeVal).type == TYPE_FLOAT) {
            float val1 = ((yyvsp[-2].runtimeVal).type == TYPE_INT) ? (float)(yyvsp[-2].runtimeVal).data.intVal : (yyvsp[-2].runtimeVal).data.floatVal;
            float val2 = ((yyvsp[0].runtimeVal).type == TYPE_INT) ? (float)(yyvsp[0].runtimeVal).data.intVal : (yyvsp[0].runtimeVal).data.floatVal;
            (yyval.runtimeVal) = (RuntimeValue){.type = TYPE_INT, .data.intVal = (val1 == val2)};
        } else {
            (yyval.runtimeVal) = (RuntimeValue){.type = TYPE_INT, .data.intVal = ((yyvsp[-2].runtimeVal).data.intVal == (yyvsp[0].runtimeVal).data.intVal)};
        }
    }
#line 1569 "parser_g2dl.tab.c"
    break;

  case 51: /* expression: expression NOT_EQUAL expression  */
#line 280 "parser_g2dl.y"
                                          {
        if ((yyvsp[-2].runtimeVal).type == TYPE_FLOAT || (yyvsp[0].runtimeVal).type == TYPE_FLOAT) {
            float val1 = ((yyvsp[-2].runtimeVal).type == TYPE_INT) ? (float)(yyvsp[-2].runtimeVal).data.intVal : (yyvsp[-2].runtimeVal).data.floatVal;
            float val2 = ((yyvsp[0].runtimeVal).type == TYPE_INT) ? (float)(yyvsp[0].runtimeVal).data.intVal : (yyvsp[0].runtimeVal).data.floatVal;
            (yyval.runtimeVal) = (RuntimeValue){.type = TYPE_INT, .data.intVal = (val1 != val2)};
        } else {
            (yyval.runtimeVal) = (RuntimeValue){.type = TYPE_INT, .data.intVal = ((yyvsp[-2].runtimeVal).data.intVal != (yyvsp[0].runtimeVal).data.intVal)};
        }
    }
#line 1583 "parser_g2dl.tab.c"
    break;

  case 52: /* expression: expression LESS_THAN expression  */
#line 289 "parser_g2dl.y"
                                          {
        float val1 = ((yyvsp[-2].runtimeVal).type == TYPE_INT) ? (float)(yyvsp[-2].runtimeVal).data.intVal : (yyvsp[-2].runtimeVal).data.floatVal;
        float val2 = ((yyvsp[0].runtimeVal).type == TYPE_INT) ? (float)(yyvsp[0].runtimeVal).data.intVal : (yyvsp[0].runtimeVal).data.floatVal;
        (yyval.runtimeVal) = (RuntimeValue){.type = TYPE_INT, .data.intVal = (val1 < val2)};
    }
#line 1593 "parser_g2dl.tab.c"
    break;

  case 53: /* expression: expression GREATER_THAN expression  */
#line 294 "parser_g2dl.y"
                                          {
        float val1 = ((yyvsp[-2].runtimeVal).type == TYPE_INT) ? (float)(yyvsp[-2].runtimeVal).data.intVal : (yyvsp[-2].runtimeVal).data.floatVal;
        float val2 = ((yyvsp[0].runtimeVal).type == TYPE_INT) ? (float)(yyvsp[0].runtimeVal).data.intVal : (yyvsp[0].runtimeVal).data.floatVal;
        (yyval.runtimeVal) = (RuntimeValue){.type = TYPE_INT, .data.intVal = (val1 > val2)};
    }
#line 1603 "parser_g2dl.tab.c"
    break;

  case 54: /* expression: expression LESS_THAN_OR_EQUAL expression  */
#line 299 "parser_g2dl.y"
                                               {
        float val1 = ((yyvsp[-2].runtimeVal).type == TYPE_INT) ? (float)(yyvsp[-2].runtimeVal).data.intVal : (yyvsp[-2].runtimeVal).data.floatVal;
        float val2 = ((yyvsp[0].runtimeVal).type == TYPE_INT) ? (float)(yyvsp[0].runtimeVal).data.intVal : (yyvsp[0].runtimeVal).data.floatVal;
        (yyval.runtimeVal) = (RuntimeValue){.type = TYPE_INT, .data.intVal = (val1 <= val2)};
    }
#line 1613 "parser_g2dl.tab.c"
    break;

  case 55: /* expression: expression GREATER_THAN_OR_EQUAL expression  */
#line 304 "parser_g2dl.y"
                                                  {
        float val1 = ((yyvsp[-2].runtimeVal).type == TYPE_INT) ? (float)(yyvsp[-2].runtimeVal).data.intVal : (yyvsp[-2].runtimeVal).data.floatVal;
        float val2 = ((yyvsp[0].runtimeVal).type == TYPE_INT) ? (float)(yyvsp[0].runtimeVal).data.intVal : (yyvsp[0].runtimeVal).data.floatVal;
        (yyval.runtimeVal) = (RuntimeValue){.type = TYPE_INT, .data.intVal = (val1 >= val2)};
    }
#line 1623 "parser_g2dl.tab.c"
    break;

  case 56: /* expression: expression AND expression  */
#line 309 "parser_g2dl.y"
                                          {
        int val1 = ((yyvsp[-2].runtimeVal).type == TYPE_FLOAT) ? (int)(yyvsp[-2].runtimeVal).data.floatVal : (yyvsp[-2].runtimeVal).data.intVal;
        int val2 = ((yyvsp[0].runtimeVal).type == TYPE_FLOAT) ? (int)(yyvsp[0].runtimeVal).data.floatVal : (yyvsp[0].runtimeVal).data.intVal;
        (yyval.runtimeVal) = (RuntimeValue){.type = TYPE_INT, .data.intVal = (val1 && val2)};
    }
#line 1633 "parser_g2dl.tab.c"
    break;

  case 57: /* expression: expression OR expression  */
#line 314 "parser_g2dl.y"
                                          {
        int val1 = ((yyvsp[-2].runtimeVal).type == TYPE_FLOAT) ? (int)(yyvsp[-2].runtimeVal).data.floatVal : (yyvsp[-2].runtimeVal).data.intVal;
        int val2 = ((yyvsp[0].runtimeVal).type == TYPE_FLOAT) ? (int)(yyvsp[0].runtimeVal).data.floatVal : (yyvsp[0].runtimeVal).data.intVal;
        (yyval.runtimeVal) = (RuntimeValue){.type = TYPE_INT, .data.intVal = (val1 || val2)};
    }
#line 1643 "parser_g2dl.tab.c"
    break;

  case 58: /* expression: NOT expression  */
#line 319 "parser_g2dl.y"
                                          {
        int val2 = ((yyvsp[0].runtimeVal).type == TYPE_FLOAT) ? (int)(yyvsp[0].runtimeVal).data.floatVal : (yyvsp[0].runtimeVal).data.intVal;
        (yyval.runtimeVal) = (RuntimeValue){.type = TYPE_INT, .data.intVal = !val2};
    }
#line 1652 "parser_g2dl.tab.c"
    break;

  case 59: /* expression: LEFT_PARENTHESIS expression RIGHT_PARENTHESIS  */
#line 323 "parser_g2dl.y"
                                                    { (yyval.runtimeVal) = (yyvsp[-1].runtimeVal); }
#line 1658 "parser_g2dl.tab.c"
    break;

  case 63: /* variable: ID  */
#line 337 "parser_g2dl.y"
       { (yyval.strVal) = (yyvsp[0].strVal); }
#line 1664 "parser_g2dl.tab.c"
    break;


#line 1668 "parser_g2dl.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 365 "parser_g2dl.y"


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
