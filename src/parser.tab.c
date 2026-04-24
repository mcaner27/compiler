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
#line 5 "src/parser.y"

#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

int yylex(void);
void yyerror(const char *s);

ASTNode *root;

#line 82 "src/parser.tab.c"

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

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_TOKEN_ARRAY = 3,                /* TOKEN_ARRAY  */
  YYSYMBOL_TOKEN_BOOLEAN = 4,              /* TOKEN_BOOLEAN  */
  YYSYMBOL_TOKEN_CHAR = 5,                 /* TOKEN_CHAR  */
  YYSYMBOL_TOKEN_ELSE = 6,                 /* TOKEN_ELSE  */
  YYSYMBOL_TOKEN_FALSE = 7,                /* TOKEN_FALSE  */
  YYSYMBOL_TOKEN_FOR = 8,                  /* TOKEN_FOR  */
  YYSYMBOL_TOKEN_FUNCTION = 9,             /* TOKEN_FUNCTION  */
  YYSYMBOL_TOKEN_IF = 10,                  /* TOKEN_IF  */
  YYSYMBOL_TOKEN_INTEGER = 11,             /* TOKEN_INTEGER  */
  YYSYMBOL_TOKEN_PRINT = 12,               /* TOKEN_PRINT  */
  YYSYMBOL_TOKEN_RETURN = 13,              /* TOKEN_RETURN  */
  YYSYMBOL_TOKEN_STRING = 14,              /* TOKEN_STRING  */
  YYSYMBOL_TOKEN_TRUE = 15,                /* TOKEN_TRUE  */
  YYSYMBOL_TOKEN_VOID = 16,                /* TOKEN_VOID  */
  YYSYMBOL_TOKEN_WHILE = 17,               /* TOKEN_WHILE  */
  YYSYMBOL_TOKEN_IDENTIFIER = 18,          /* TOKEN_IDENTIFIER  */
  YYSYMBOL_TOKEN_INTEGER_LITERAL = 19,     /* TOKEN_INTEGER_LITERAL  */
  YYSYMBOL_TOKEN_STRING_LITERAL = 20,      /* TOKEN_STRING_LITERAL  */
  YYSYMBOL_TOKEN_CHARACTER_LITERAL = 21,   /* TOKEN_CHARACTER_LITERAL  */
  YYSYMBOL_TOKEN_LPAREN = 22,              /* TOKEN_LPAREN  */
  YYSYMBOL_TOKEN_RPAREN = 23,              /* TOKEN_RPAREN  */
  YYSYMBOL_TOKEN_LBRACKET = 24,            /* TOKEN_LBRACKET  */
  YYSYMBOL_TOKEN_RBRACKET = 25,            /* TOKEN_RBRACKET  */
  YYSYMBOL_TOKEN_LBRACE = 26,              /* TOKEN_LBRACE  */
  YYSYMBOL_TOKEN_RBRACE = 27,              /* TOKEN_RBRACE  */
  YYSYMBOL_TOKEN_COLON = 28,               /* TOKEN_COLON  */
  YYSYMBOL_TOKEN_SEMICOLON = 29,           /* TOKEN_SEMICOLON  */
  YYSYMBOL_TOKEN_COMMA = 30,               /* TOKEN_COMMA  */
  YYSYMBOL_TOKEN_INCREMENT = 31,           /* TOKEN_INCREMENT  */
  YYSYMBOL_TOKEN_DECREMENT = 32,           /* TOKEN_DECREMENT  */
  YYSYMBOL_TOKEN_EXPONENT = 33,            /* TOKEN_EXPONENT  */
  YYSYMBOL_TOKEN_MULTIPLY = 34,            /* TOKEN_MULTIPLY  */
  YYSYMBOL_TOKEN_DIVIDE = 35,              /* TOKEN_DIVIDE  */
  YYSYMBOL_TOKEN_MODULO = 36,              /* TOKEN_MODULO  */
  YYSYMBOL_TOKEN_ADD = 37,                 /* TOKEN_ADD  */
  YYSYMBOL_TOKEN_SUBTRACT = 38,            /* TOKEN_SUBTRACT  */
  YYSYMBOL_TOKEN_LESS_THAN = 39,           /* TOKEN_LESS_THAN  */
  YYSYMBOL_TOKEN_LESS_EQUAL = 40,          /* TOKEN_LESS_EQUAL  */
  YYSYMBOL_TOKEN_GREATER_THAN = 41,        /* TOKEN_GREATER_THAN  */
  YYSYMBOL_TOKEN_GREATER_EQUAL = 42,       /* TOKEN_GREATER_EQUAL  */
  YYSYMBOL_TOKEN_EQUAL = 43,               /* TOKEN_EQUAL  */
  YYSYMBOL_TOKEN_NOT_EQUAL = 44,           /* TOKEN_NOT_EQUAL  */
  YYSYMBOL_TOKEN_LOGICAL_AND = 45,         /* TOKEN_LOGICAL_AND  */
  YYSYMBOL_TOKEN_LOGICAL_OR = 46,          /* TOKEN_LOGICAL_OR  */
  YYSYMBOL_TOKEN_LOGICAL_NOT = 47,         /* TOKEN_LOGICAL_NOT  */
  YYSYMBOL_TOKEN_ASSIGN = 48,              /* TOKEN_ASSIGN  */
  YYSYMBOL_TOKEN_ERROR = 49,               /* TOKEN_ERROR  */
  YYSYMBOL_LOWER_THAN_ELSE = 50,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_YYACCEPT = 51,                  /* $accept  */
  YYSYMBOL_program = 52,                   /* program  */
  YYSYMBOL_declaration_list = 53,          /* declaration_list  */
  YYSYMBOL_declaration = 54,               /* declaration  */
  YYSYMBOL_function_decl = 55,             /* function_decl  */
  YYSYMBOL_return_type = 56,               /* return_type  */
  YYSYMBOL_param_list_opt = 57,            /* param_list_opt  */
  YYSYMBOL_param_list = 58,                /* param_list  */
  YYSYMBOL_param = 59,                     /* param  */
  YYSYMBOL_type = 60,                      /* type  */
  YYSYMBOL_block = 61,                     /* block  */
  YYSYMBOL_stmt_list = 62,                 /* stmt_list  */
  YYSYMBOL_statement = 63,                 /* statement  */
  YYSYMBOL_expr_opt = 64,                  /* expr_opt  */
  YYSYMBOL_print_list = 65,                /* print_list  */
  YYSYMBOL_array_initializer = 66,         /* array_initializer  */
  YYSYMBOL_expr_list_opt = 67,             /* expr_list_opt  */
  YYSYMBOL_expr_list = 68,                 /* expr_list  */
  YYSYMBOL_expr = 69,                      /* expr  */
  YYSYMBOL_argument_list_opt = 70,         /* argument_list_opt  */
  YYSYMBOL_argument_list = 71              /* argument_list  */
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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   465

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  51
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  21
/* YYNRULES -- Number of rules.  */
#define YYNRULES  77
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  150

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   305


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
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    73,    73,    81,    94,   100,   106,   113,   120,   127,
     134,   145,   160,   164,   172,   177,   183,   187,   202,   208,
     217,   222,   227,   232,   240,   249,   262,   268,   274,   280,
     285,   291,   295,   302,   310,   328,   335,   342,   347,   353,
     357,   372,   379,   384,   390,   394,   409,   415,   421,   427,
     433,   439,   445,   449,   456,   463,   470,   477,   484,   491,
     498,   505,   512,   519,   526,   533,   540,   547,   553,   559,
     566,   573,   580,   586,   595,   600,   606,   610
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
  "\"end of file\"", "error", "\"invalid token\"", "TOKEN_ARRAY",
  "TOKEN_BOOLEAN", "TOKEN_CHAR", "TOKEN_ELSE", "TOKEN_FALSE", "TOKEN_FOR",
  "TOKEN_FUNCTION", "TOKEN_IF", "TOKEN_INTEGER", "TOKEN_PRINT",
  "TOKEN_RETURN", "TOKEN_STRING", "TOKEN_TRUE", "TOKEN_VOID",
  "TOKEN_WHILE", "TOKEN_IDENTIFIER", "TOKEN_INTEGER_LITERAL",
  "TOKEN_STRING_LITERAL", "TOKEN_CHARACTER_LITERAL", "TOKEN_LPAREN",
  "TOKEN_RPAREN", "TOKEN_LBRACKET", "TOKEN_RBRACKET", "TOKEN_LBRACE",
  "TOKEN_RBRACE", "TOKEN_COLON", "TOKEN_SEMICOLON", "TOKEN_COMMA",
  "TOKEN_INCREMENT", "TOKEN_DECREMENT", "TOKEN_EXPONENT", "TOKEN_MULTIPLY",
  "TOKEN_DIVIDE", "TOKEN_MODULO", "TOKEN_ADD", "TOKEN_SUBTRACT",
  "TOKEN_LESS_THAN", "TOKEN_LESS_EQUAL", "TOKEN_GREATER_THAN",
  "TOKEN_GREATER_EQUAL", "TOKEN_EQUAL", "TOKEN_NOT_EQUAL",
  "TOKEN_LOGICAL_AND", "TOKEN_LOGICAL_OR", "TOKEN_LOGICAL_NOT",
  "TOKEN_ASSIGN", "TOKEN_ERROR", "LOWER_THAN_ELSE", "$accept", "program",
  "declaration_list", "declaration", "function_decl", "return_type",
  "param_list_opt", "param_list", "param", "type", "block", "stmt_list",
  "statement", "expr_opt", "print_list", "array_initializer",
  "expr_list_opt", "expr_list", "expr", "argument_list_opt",
  "argument_list", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-93)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -93,     3,    32,   -93,   -17,   -93,   -93,   451,    35,   -93,
     -93,    56,   -93,   -93,   -28,   134,   -93,    42,   -93,   -93,
     134,   -93,   -93,    44,   -93,   -93,   -93,   134,   134,   134,
     228,    50,   251,   134,   151,    68,    -7,   134,    80,   -93,
     -93,   134,   134,   134,   134,   134,   134,   134,   134,   134,
     134,   134,   134,   134,   134,   134,    41,    52,    59,   -93,
     -93,   345,    65,    60,   -93,   276,   -27,   174,   174,   174,
     174,    68,    68,   133,   133,   133,   133,   411,   411,   390,
     368,   345,     5,   -25,    50,   -93,   134,   -93,   -93,    69,
      82,   -93,   -93,    84,   -93,   345,   134,    53,    86,   -93,
     -93,    85,    87,   345,   -93,    80,    36,   -93,   134,   -93,
      92,    93,   134,    58,    94,    19,   -93,   -93,   -93,   -93,
     299,   345,   134,   134,   -23,   345,   -93,   322,   134,   -93,
      89,   345,   177,   -93,   134,   -93,   203,   134,   113,   345,
     113,    95,   121,   -93,   134,   113,   114,   -93,   113,   -93
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       4,     0,     2,     1,     0,     3,     9,     0,     0,    21,
      22,     0,    20,    23,     0,     0,    13,     0,    12,     5,
       0,    51,    50,    46,    47,    48,    49,     0,     0,     0,
       0,    15,     0,    75,     0,    68,    67,     0,     0,    72,
      73,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    14,    16,
       6,    76,     0,    74,    52,     0,     0,    58,    55,    56,
      57,    53,    54,    59,    60,    61,    62,    63,    64,    65,
      66,    69,     0,     0,     0,    71,     0,    70,     7,     0,
       0,    18,    11,     0,    17,    77,    43,     0,     0,    26,
      10,     0,    42,    44,     8,     0,     0,    41,     0,    19,
       0,     0,     0,     0,     0,    46,    24,    36,    31,    25,
       0,    45,    38,     0,     0,    39,    29,     0,     0,    27,
       0,    37,     0,    30,     0,    28,     0,    38,     0,    40,
       0,     0,    32,    35,    38,     0,     0,    33,     0,    34
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -93,   -93,   -93,   138,   -93,   -93,   -93,   -93,    61,     4,
      49,   -93,    -2,   -92,   -93,   -93,   -93,   -93,   -15,   -93,
     -93
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,     2,   117,     6,    17,    57,    58,    59,    14,
     118,   106,   119,   130,   124,    97,   101,   102,   120,    62,
      63
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      30,    19,    88,     3,    92,    32,   133,   134,    90,     9,
      10,     7,    34,    35,    36,    18,    12,    37,    61,    13,
      20,    89,    65,    93,    39,    40,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    33,    66,    21,   110,   141,   111,     7,   112,   113,
       4,    22,   146,   114,   115,    24,    25,    26,    27,    15,
       9,    10,    99,   116,    31,    21,    33,    12,    56,    82,
      13,    95,    16,    22,    28,    83,    23,    24,    25,    26,
      27,   103,   104,    29,     9,    10,    91,   126,    85,    84,
      86,    12,    37,   121,    13,    96,    28,   125,   127,    39,
      40,    41,    42,    43,    44,    29,    98,   131,   132,   109,
      99,   105,   107,   136,   122,   123,   128,   108,   137,   139,
      21,   110,   131,   111,   144,   112,   113,   145,    22,   131,
     114,   115,    24,    25,    26,    27,   142,   148,   143,    99,
       5,    21,   100,   147,     0,    94,   149,     0,     0,    22,
       0,    28,    23,    24,    25,    26,    27,    37,     0,     0,
      29,     0,     0,     0,    39,    40,    41,    42,    43,    44,
      45,    46,    28,     0,    64,    37,     0,     0,     0,     0,
       0,    29,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    37,    55,
     138,    37,     0,     0,     0,    39,    40,    41,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,     0,    55,   140,    37,     0,     0,
       0,     0,     0,     0,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
       0,    55,    37,    38,     0,     0,     0,     0,     0,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    37,    55,     0,     0,     0,
      60,     0,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,     0,    55,
      37,    87,     0,     0,     0,     0,     0,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    37,    55,     0,     0,     0,   129,     0,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    37,    55,     0,     0,
       0,   135,     0,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    37,
      55,     0,     0,     0,     0,     0,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    37,    55,     0,     0,     0,     0,     0,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    37,     0,     0,     0,     0,     0,
       0,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    37,     0,     0,     0,     0,
       0,     0,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,     8,     9,    10,     0,     0,     0,
      11,     0,    12,     0,     0,    13
};

static const yytype_int16 yycheck[] =
{
      15,    29,    29,     0,    29,    20,    29,    30,     3,     4,
       5,    28,    27,    28,    29,    11,    11,    24,    33,    14,
      48,    48,    37,    48,    31,    32,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    22,    38,     7,     8,   137,    10,    28,    12,    13,
      18,    15,   144,    17,    18,    19,    20,    21,    22,    24,
       4,     5,    26,    27,    22,     7,    22,    11,    18,    28,
      14,    86,    16,    15,    38,    23,    18,    19,    20,    21,
      22,    96,    29,    47,     4,     5,    82,    29,    23,    30,
      30,    11,    24,   108,    14,    26,    38,   112,   113,    31,
      32,    33,    34,    35,    36,    47,    24,   122,   123,   105,
      26,    25,    27,   128,    22,    22,    22,    30,    29,   134,
       7,     8,   137,    10,    29,    12,    13,     6,    15,   144,
      17,    18,    19,    20,    21,    22,   138,    23,   140,    26,
       2,     7,    93,   145,    -1,    84,   148,    -1,    -1,    15,
      -1,    38,    18,    19,    20,    21,    22,    24,    -1,    -1,
      47,    -1,    -1,    -1,    31,    32,    33,    34,    35,    36,
      37,    38,    38,    -1,    23,    24,    -1,    -1,    -1,    -1,
      -1,    47,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    24,    48,
      23,    24,    -1,    -1,    -1,    31,    32,    33,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    -1,    48,    23,    24,    -1,    -1,
      -1,    -1,    -1,    -1,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      -1,    48,    24,    25,    -1,    -1,    -1,    -1,    -1,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    24,    48,    -1,    -1,    -1,
      29,    -1,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    -1,    48,
      24,    25,    -1,    -1,    -1,    -1,    -1,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    24,    48,    -1,    -1,    -1,    29,    -1,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    24,    48,    -1,    -1,
      -1,    29,    -1,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    24,
      48,    -1,    -1,    -1,    -1,    -1,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    24,    48,    -1,    -1,    -1,    -1,    -1,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    24,    -1,    -1,    -1,    -1,    -1,
      -1,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    24,    -1,    -1,    -1,    -1,
      -1,    -1,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,     3,     4,     5,    -1,    -1,    -1,
       9,    -1,    11,    -1,    -1,    14
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    52,    53,     0,    18,    54,    55,    28,     3,     4,
       5,     9,    11,    14,    60,    24,    16,    56,    60,    29,
      48,     7,    15,    18,    19,    20,    21,    22,    38,    47,
      69,    22,    69,    22,    69,    69,    69,    24,    25,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    48,    18,    57,    58,    59,
      29,    69,    70,    71,    23,    69,    60,    69,    69,    69,
      69,    69,    69,    69,    69,    69,    69,    69,    69,    69,
      69,    69,    28,    23,    30,    23,    30,    25,    29,    48,
       3,    60,    29,    48,    59,    69,    26,    66,    24,    26,
      61,    67,    68,    69,    29,    25,    62,    27,    30,    60,
       8,    10,    12,    13,    17,    18,    27,    54,    61,    63,
      69,    69,    22,    22,    65,    69,    29,    69,    22,    29,
      64,    69,    69,    29,    30,    29,    69,    29,    23,    69,
      23,    64,    63,    63,    29,     6,    64,    63,    23,    63
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    51,    52,    53,    53,    54,    54,    54,    54,    54,
      55,    55,    56,    56,    57,    57,    58,    58,    59,    59,
      60,    60,    60,    60,    61,    62,    62,    63,    63,    63,
      63,    63,    63,    63,    63,    63,    63,    64,    64,    65,
      65,    66,    67,    67,    68,    68,    69,    69,    69,    69,
      69,    69,    69,    69,    69,    69,    69,    69,    69,    69,
      69,    69,    69,    69,    69,    69,    69,    69,    69,    69,
      69,    69,    69,    69,    70,    70,    71,    71
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     0,     4,     6,     8,    10,     1,
       9,     8,     1,     1,     1,     0,     1,     3,     3,     6,
       1,     1,     1,     1,     3,     2,     0,     2,     3,     2,
       3,     1,     5,     7,     9,     5,     1,     1,     0,     1,
       3,     3,     1,     0,     1,     3,     1,     1,     1,     1,
       1,     1,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     2,     2,     3,
       4,     4,     2,     2,     1,     0,     1,     3
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
  case 2: /* program: declaration_list  */
#line 74 "src/parser.y"
        {
            root = (yyvsp[0].node);
            (yyval.node) = (yyvsp[0].node);
        }
#line 1310 "src/parser.tab.c"
    break;

  case 3: /* declaration_list: declaration_list declaration  */
#line 82 "src/parser.y"
        {
            if ((yyvsp[-1].node) == NULL) {
                (yyval.node) = (yyvsp[0].node);
            } else {
                ASTNode *temp = (yyvsp[-1].node);
                while (temp->next != NULL)
                    temp = temp->next;
                temp->next = (yyvsp[0].node);
                (yyval.node) = (yyvsp[-1].node);
            }
        }
#line 1326 "src/parser.tab.c"
    break;

  case 4: /* declaration_list: %empty  */
#line 94 "src/parser.y"
        {
            (yyval.node) = NULL;
        }
#line 1334 "src/parser.tab.c"
    break;

  case 5: /* declaration: TOKEN_IDENTIFIER TOKEN_COLON type TOKEN_SEMICOLON  */
#line 101 "src/parser.y"
        {
            (yyval.node) = create_node(NODE_DECLARATION);
            (yyval.node)->name = (yyvsp[-3].text);
            (yyval.node)->left = (yyvsp[-1].node);
        }
#line 1344 "src/parser.tab.c"
    break;

  case 6: /* declaration: TOKEN_IDENTIFIER TOKEN_COLON type TOKEN_ASSIGN expr TOKEN_SEMICOLON  */
#line 107 "src/parser.y"
        {
            (yyval.node) = create_node(NODE_DECLARATION);
            (yyval.node)->name = (yyvsp[-5].text);
            (yyval.node)->left = (yyvsp[-3].node);
            (yyval.node)->right = (yyvsp[-1].node);
        }
#line 1355 "src/parser.tab.c"
    break;

  case 7: /* declaration: TOKEN_IDENTIFIER TOKEN_COLON TOKEN_ARRAY TOKEN_LBRACKET expr TOKEN_RBRACKET type TOKEN_SEMICOLON  */
#line 114 "src/parser.y"
        {
            (yyval.node) = create_node(NODE_DECLARATION);
            (yyval.node)->name = (yyvsp[-7].text);
            (yyval.node)->left = (yyvsp[-3].node);
            (yyval.node)->right = (yyvsp[-1].node);
        }
#line 1366 "src/parser.tab.c"
    break;

  case 8: /* declaration: TOKEN_IDENTIFIER TOKEN_COLON TOKEN_ARRAY TOKEN_LBRACKET expr TOKEN_RBRACKET type TOKEN_ASSIGN array_initializer TOKEN_SEMICOLON  */
#line 121 "src/parser.y"
        {
            (yyval.node) = create_node(NODE_DECLARATION);
            (yyval.node)->name = (yyvsp[-9].text);
            (yyval.node)->left = (yyvsp[-5].node);
            (yyval.node)->right = (yyvsp[-1].node);
        }
#line 1377 "src/parser.tab.c"
    break;

  case 9: /* declaration: function_decl  */
#line 128 "src/parser.y"
        {
            (yyval.node) = (yyvsp[0].node);
        }
#line 1385 "src/parser.tab.c"
    break;

  case 10: /* function_decl: TOKEN_IDENTIFIER TOKEN_COLON TOKEN_FUNCTION return_type TOKEN_LPAREN param_list_opt TOKEN_RPAREN TOKEN_ASSIGN block  */
#line 135 "src/parser.y"
        {
            (yyval.node) = create_node(NODE_FUNCTION);
            (yyval.node)->name = (yyvsp[-8].text);
            (yyval.node)->left = (yyvsp[-5].node);
            (yyval.node)->right = (yyvsp[0].node);

            if ((yyvsp[-3].node) != NULL && (yyvsp[-5].node) != NULL) {
                (yyvsp[-5].node)->next = (yyvsp[-3].node);
            }
        }
#line 1400 "src/parser.tab.c"
    break;

  case 11: /* function_decl: TOKEN_IDENTIFIER TOKEN_COLON TOKEN_FUNCTION return_type TOKEN_LPAREN param_list_opt TOKEN_RPAREN TOKEN_SEMICOLON  */
#line 146 "src/parser.y"
        {
            /* Function prototype: no body */
            (yyval.node) = create_node(NODE_FUNCTION);
            (yyval.node)->name = (yyvsp[-7].text);
            (yyval.node)->left = (yyvsp[-4].node);
            (yyval.node)->right = NULL;  /* NULL body marks this as prototype */

            if ((yyvsp[-2].node) != NULL && (yyvsp[-4].node) != NULL) {
                (yyvsp[-4].node)->next = (yyvsp[-2].node);
            }
        }
#line 1416 "src/parser.tab.c"
    break;

  case 12: /* return_type: type  */
#line 161 "src/parser.y"
        {
            (yyval.node) = (yyvsp[0].node);
        }
#line 1424 "src/parser.tab.c"
    break;

  case 13: /* return_type: TOKEN_VOID  */
#line 165 "src/parser.y"
        {
            (yyval.node) = create_node(NODE_TYPE);
            (yyval.node)->type_kind_val = TYPE_VOID;
        }
#line 1433 "src/parser.tab.c"
    break;

  case 14: /* param_list_opt: param_list  */
#line 173 "src/parser.y"
        {
            (yyval.node) = (yyvsp[0].node);
        }
#line 1441 "src/parser.tab.c"
    break;

  case 15: /* param_list_opt: %empty  */
#line 177 "src/parser.y"
        {
            (yyval.node) = NULL;
        }
#line 1449 "src/parser.tab.c"
    break;

  case 16: /* param_list: param  */
#line 184 "src/parser.y"
        {
            (yyval.node) = (yyvsp[0].node);
        }
#line 1457 "src/parser.tab.c"
    break;

  case 17: /* param_list: param_list TOKEN_COMMA param  */
#line 188 "src/parser.y"
        {
            if ((yyvsp[-2].node) == NULL) {
                (yyval.node) = (yyvsp[0].node);
            } else {
                ASTNode *temp = (yyvsp[-2].node);
                while (temp->next != NULL)
                    temp = temp->next;
                temp->next = (yyvsp[0].node);
                (yyval.node) = (yyvsp[-2].node);
            }
        }
#line 1473 "src/parser.tab.c"
    break;

  case 18: /* param: TOKEN_IDENTIFIER TOKEN_COLON type  */
#line 203 "src/parser.y"
        {
            (yyval.node) = create_node(NODE_DECLARATION);
            (yyval.node)->name = (yyvsp[-2].text);
            (yyval.node)->left = (yyvsp[0].node);
        }
#line 1483 "src/parser.tab.c"
    break;

  case 19: /* param: TOKEN_IDENTIFIER TOKEN_COLON TOKEN_ARRAY TOKEN_LBRACKET TOKEN_RBRACKET type  */
#line 209 "src/parser.y"
        {
            (yyval.node) = create_node(NODE_DECLARATION);
            (yyval.node)->name = (yyvsp[-5].text);
            (yyval.node)->left = (yyvsp[0].node);
        }
#line 1493 "src/parser.tab.c"
    break;

  case 20: /* type: TOKEN_INTEGER  */
#line 218 "src/parser.y"
        {
            (yyval.node) = create_node(NODE_TYPE);
            (yyval.node)->type_kind_val = TYPE_INTEGER;
        }
#line 1502 "src/parser.tab.c"
    break;

  case 21: /* type: TOKEN_BOOLEAN  */
#line 223 "src/parser.y"
        {
            (yyval.node) = create_node(NODE_TYPE);
            (yyval.node)->type_kind_val = TYPE_BOOLEAN;
        }
#line 1511 "src/parser.tab.c"
    break;

  case 22: /* type: TOKEN_CHAR  */
#line 228 "src/parser.y"
        {
            (yyval.node) = create_node(NODE_TYPE);
            (yyval.node)->type_kind_val = TYPE_CHAR;
        }
#line 1520 "src/parser.tab.c"
    break;

  case 23: /* type: TOKEN_STRING  */
#line 233 "src/parser.y"
        {
            (yyval.node) = create_node(NODE_TYPE);
            (yyval.node)->type_kind_val = TYPE_STRING;
        }
#line 1529 "src/parser.tab.c"
    break;

  case 24: /* block: TOKEN_LBRACE stmt_list TOKEN_RBRACE  */
#line 241 "src/parser.y"
        {
            (yyval.node) = create_node(NODE_STATEMENT);
            (yyval.node)->stmt_kind_val = STMT_BLOCK;
            (yyval.node)->left = (yyvsp[-1].node);
        }
#line 1539 "src/parser.tab.c"
    break;

  case 25: /* stmt_list: stmt_list statement  */
#line 250 "src/parser.y"
        {
            if ((yyvsp[-1].node) == NULL) {
                (yyval.node) = (yyvsp[0].node);
            } else {
                ASTNode *temp = (yyvsp[-1].node);
                while (temp->next != NULL)
                    temp = temp->next;
                temp->next = (yyvsp[0].node);
                (yyval.node) = (yyvsp[-1].node);
            }
        }
#line 1555 "src/parser.tab.c"
    break;

  case 26: /* stmt_list: %empty  */
#line 262 "src/parser.y"
        {
            (yyval.node) = NULL;
        }
#line 1563 "src/parser.tab.c"
    break;

  case 27: /* statement: expr TOKEN_SEMICOLON  */
#line 269 "src/parser.y"
        {
            (yyval.node) = create_node(NODE_STATEMENT);
            (yyval.node)->stmt_kind_val = STMT_EXPR;
            (yyval.node)->left = (yyvsp[-1].node);
        }
#line 1573 "src/parser.tab.c"
    break;

  case 28: /* statement: TOKEN_RETURN expr TOKEN_SEMICOLON  */
#line 275 "src/parser.y"
        {
            (yyval.node) = create_node(NODE_STATEMENT);
            (yyval.node)->stmt_kind_val = STMT_RETURN;
            (yyval.node)->left = (yyvsp[-1].node);
        }
#line 1583 "src/parser.tab.c"
    break;

  case 29: /* statement: TOKEN_RETURN TOKEN_SEMICOLON  */
#line 281 "src/parser.y"
        {
            (yyval.node) = create_node(NODE_STATEMENT);
            (yyval.node)->stmt_kind_val = STMT_RETURN;
        }
#line 1592 "src/parser.tab.c"
    break;

  case 30: /* statement: TOKEN_PRINT print_list TOKEN_SEMICOLON  */
#line 286 "src/parser.y"
        {
            (yyval.node) = create_node(NODE_STATEMENT);
            (yyval.node)->stmt_kind_val = STMT_PRINT;
            (yyval.node)->left = (yyvsp[-1].node);
        }
#line 1602 "src/parser.tab.c"
    break;

  case 31: /* statement: block  */
#line 292 "src/parser.y"
        {
            (yyval.node) = (yyvsp[0].node);
        }
#line 1610 "src/parser.tab.c"
    break;

  case 32: /* statement: TOKEN_IF TOKEN_LPAREN expr TOKEN_RPAREN statement  */
#line 296 "src/parser.y"
        {
            (yyval.node) = create_node(NODE_STATEMENT);
            (yyval.node)->stmt_kind_val = STMT_IF;
            (yyval.node)->left = (yyvsp[-2].node);
            (yyval.node)->right = (yyvsp[0].node);
        }
#line 1621 "src/parser.tab.c"
    break;

  case 33: /* statement: TOKEN_IF TOKEN_LPAREN expr TOKEN_RPAREN statement TOKEN_ELSE statement  */
#line 303 "src/parser.y"
        {
            (yyval.node) = create_node(NODE_STATEMENT);
            (yyval.node)->stmt_kind_val = STMT_IF_ELSE;
            (yyval.node)->left = (yyvsp[-4].node);
            (yyval.node)->right = (yyvsp[-2].node);
            (yyval.node)->third = (yyvsp[0].node);
        }
#line 1633 "src/parser.tab.c"
    break;

  case 34: /* statement: TOKEN_FOR TOKEN_LPAREN expr_opt TOKEN_SEMICOLON expr_opt TOKEN_SEMICOLON expr_opt TOKEN_RPAREN statement  */
#line 311 "src/parser.y"
        {
            (yyval.node) = create_node(NODE_STATEMENT);
            (yyval.node)->stmt_kind_val = STMT_FOR;
            (yyval.node)->left = (yyvsp[-6].node);
            (yyval.node)->right = (yyvsp[-4].node);
            (yyval.node)->third = (yyvsp[-2].node);

            if ((yyvsp[-2].node) != NULL) {
                (yyvsp[-2].node)->next = (yyvsp[0].node);
            } else if ((yyvsp[-4].node) != NULL) {
                (yyvsp[-4].node)->next = (yyvsp[0].node);
            } else if ((yyvsp[-6].node) != NULL) {
                (yyvsp[-6].node)->next = (yyvsp[0].node);
            } else {
                (yyval.node)->third = (yyvsp[0].node);
            }
        }
#line 1655 "src/parser.tab.c"
    break;

  case 35: /* statement: TOKEN_WHILE TOKEN_LPAREN expr TOKEN_RPAREN statement  */
#line 329 "src/parser.y"
        {
            (yyval.node) = create_node(NODE_STATEMENT);
            (yyval.node)->stmt_kind_val = STMT_WHILE;
            (yyval.node)->left = (yyvsp[-2].node);
            (yyval.node)->right = (yyvsp[0].node);
        }
#line 1666 "src/parser.tab.c"
    break;

  case 36: /* statement: declaration  */
#line 336 "src/parser.y"
        {
            (yyval.node) = (yyvsp[0].node);
        }
#line 1674 "src/parser.tab.c"
    break;

  case 37: /* expr_opt: expr  */
#line 343 "src/parser.y"
        {
            (yyval.node) = (yyvsp[0].node);
        }
#line 1682 "src/parser.tab.c"
    break;

  case 38: /* expr_opt: %empty  */
#line 347 "src/parser.y"
        {
            (yyval.node) = NULL;
        }
#line 1690 "src/parser.tab.c"
    break;

  case 39: /* print_list: expr  */
#line 354 "src/parser.y"
        {
            (yyval.node) = (yyvsp[0].node);
        }
#line 1698 "src/parser.tab.c"
    break;

  case 40: /* print_list: print_list TOKEN_COMMA expr  */
#line 358 "src/parser.y"
        {
            if ((yyvsp[-2].node) == NULL) {
                (yyval.node) = (yyvsp[0].node);
            } else {
                ASTNode *temp = (yyvsp[-2].node);
                while (temp->next != NULL)
                    temp = temp->next;
                temp->next = (yyvsp[0].node);
                (yyval.node) = (yyvsp[-2].node);
            }
        }
#line 1714 "src/parser.tab.c"
    break;

  case 41: /* array_initializer: TOKEN_LBRACE expr_list_opt TOKEN_RBRACE  */
#line 373 "src/parser.y"
        {
            (yyval.node) = (yyvsp[-1].node);
        }
#line 1722 "src/parser.tab.c"
    break;

  case 42: /* expr_list_opt: expr_list  */
#line 380 "src/parser.y"
        {
            (yyval.node) = (yyvsp[0].node);
        }
#line 1730 "src/parser.tab.c"
    break;

  case 43: /* expr_list_opt: %empty  */
#line 384 "src/parser.y"
        {
            (yyval.node) = NULL;
        }
#line 1738 "src/parser.tab.c"
    break;

  case 44: /* expr_list: expr  */
#line 391 "src/parser.y"
        {
            (yyval.node) = (yyvsp[0].node);
        }
#line 1746 "src/parser.tab.c"
    break;

  case 45: /* expr_list: expr_list TOKEN_COMMA expr  */
#line 395 "src/parser.y"
        {
            if ((yyvsp[-2].node) == NULL) {
                (yyval.node) = (yyvsp[0].node);
            } else {
                ASTNode *temp = (yyvsp[-2].node);
                while (temp->next != NULL)
                    temp = temp->next;
                temp->next = (yyvsp[0].node);
                (yyval.node) = (yyvsp[-2].node);
            }
        }
#line 1762 "src/parser.tab.c"
    break;

  case 46: /* expr: TOKEN_IDENTIFIER  */
#line 410 "src/parser.y"
        {
            (yyval.node) = create_node(NODE_EXPRESSION);
            (yyval.node)->expr_kind_val = EXPR_IDENTIFIER;
            (yyval.node)->name = (yyvsp[0].text);
        }
#line 1772 "src/parser.tab.c"
    break;

  case 47: /* expr: TOKEN_INTEGER_LITERAL  */
#line 416 "src/parser.y"
        {
            (yyval.node) = create_node(NODE_EXPRESSION);
            (yyval.node)->expr_kind_val = EXPR_INTEGER_LITERAL;
            (yyval.node)->int_value = (yyvsp[0].number);
        }
#line 1782 "src/parser.tab.c"
    break;

  case 48: /* expr: TOKEN_STRING_LITERAL  */
#line 422 "src/parser.y"
        {
            (yyval.node) = create_node(NODE_EXPRESSION);
            (yyval.node)->expr_kind_val = EXPR_STRING_LITERAL;
            (yyval.node)->string_value = (yyvsp[0].text);
        }
#line 1792 "src/parser.tab.c"
    break;

  case 49: /* expr: TOKEN_CHARACTER_LITERAL  */
#line 428 "src/parser.y"
        {
            (yyval.node) = create_node(NODE_EXPRESSION);
            (yyval.node)->expr_kind_val = EXPR_CHAR_LITERAL;
            (yyval.node)->string_value = (yyvsp[0].text);
        }
#line 1802 "src/parser.tab.c"
    break;

  case 50: /* expr: TOKEN_TRUE  */
#line 434 "src/parser.y"
        {
            (yyval.node) = create_node(NODE_EXPRESSION);
            (yyval.node)->expr_kind_val = EXPR_BOOLEAN_LITERAL;
            (yyval.node)->int_value = 1;
        }
#line 1812 "src/parser.tab.c"
    break;

  case 51: /* expr: TOKEN_FALSE  */
#line 440 "src/parser.y"
        {
            (yyval.node) = create_node(NODE_EXPRESSION);
            (yyval.node)->expr_kind_val = EXPR_BOOLEAN_LITERAL;
            (yyval.node)->int_value = 0;
        }
#line 1822 "src/parser.tab.c"
    break;

  case 52: /* expr: TOKEN_LPAREN expr TOKEN_RPAREN  */
#line 446 "src/parser.y"
        {
            (yyval.node) = (yyvsp[-1].node);
        }
#line 1830 "src/parser.tab.c"
    break;

  case 53: /* expr: expr TOKEN_ADD expr  */
#line 450 "src/parser.y"
        {
            (yyval.node) = create_node(NODE_EXPRESSION);
            (yyval.node)->expr_kind_val = EXPR_ADD;
            (yyval.node)->left = (yyvsp[-2].node);
            (yyval.node)->right = (yyvsp[0].node);
        }
#line 1841 "src/parser.tab.c"
    break;

  case 54: /* expr: expr TOKEN_SUBTRACT expr  */
#line 457 "src/parser.y"
        {
            (yyval.node) = create_node(NODE_EXPRESSION);
            (yyval.node)->expr_kind_val = EXPR_SUB;
            (yyval.node)->left = (yyvsp[-2].node);
            (yyval.node)->right = (yyvsp[0].node);
        }
#line 1852 "src/parser.tab.c"
    break;

  case 55: /* expr: expr TOKEN_MULTIPLY expr  */
#line 464 "src/parser.y"
        {
            (yyval.node) = create_node(NODE_EXPRESSION);
            (yyval.node)->expr_kind_val = EXPR_MUL;
            (yyval.node)->left = (yyvsp[-2].node);
            (yyval.node)->right = (yyvsp[0].node);
        }
#line 1863 "src/parser.tab.c"
    break;

  case 56: /* expr: expr TOKEN_DIVIDE expr  */
#line 471 "src/parser.y"
        {
            (yyval.node) = create_node(NODE_EXPRESSION);
            (yyval.node)->expr_kind_val = EXPR_DIV;
            (yyval.node)->left = (yyvsp[-2].node);
            (yyval.node)->right = (yyvsp[0].node);
        }
#line 1874 "src/parser.tab.c"
    break;

  case 57: /* expr: expr TOKEN_MODULO expr  */
#line 478 "src/parser.y"
        {
            (yyval.node) = create_node(NODE_EXPRESSION);
            (yyval.node)->expr_kind_val = EXPR_MOD;
            (yyval.node)->left = (yyvsp[-2].node);
            (yyval.node)->right = (yyvsp[0].node);
        }
#line 1885 "src/parser.tab.c"
    break;

  case 58: /* expr: expr TOKEN_EXPONENT expr  */
#line 485 "src/parser.y"
        {
            (yyval.node) = create_node(NODE_EXPRESSION);
            (yyval.node)->expr_kind_val = EXPR_EXP;
            (yyval.node)->left = (yyvsp[-2].node);
            (yyval.node)->right = (yyvsp[0].node);
        }
#line 1896 "src/parser.tab.c"
    break;

  case 59: /* expr: expr TOKEN_LESS_THAN expr  */
#line 492 "src/parser.y"
        {
            (yyval.node) = create_node(NODE_EXPRESSION);
            (yyval.node)->expr_kind_val = EXPR_LT;
            (yyval.node)->left = (yyvsp[-2].node);
            (yyval.node)->right = (yyvsp[0].node);
        }
#line 1907 "src/parser.tab.c"
    break;

  case 60: /* expr: expr TOKEN_LESS_EQUAL expr  */
#line 499 "src/parser.y"
        {
            (yyval.node) = create_node(NODE_EXPRESSION);
            (yyval.node)->expr_kind_val = EXPR_LE;
            (yyval.node)->left = (yyvsp[-2].node);
            (yyval.node)->right = (yyvsp[0].node);
        }
#line 1918 "src/parser.tab.c"
    break;

  case 61: /* expr: expr TOKEN_GREATER_THAN expr  */
#line 506 "src/parser.y"
        {
            (yyval.node) = create_node(NODE_EXPRESSION);
            (yyval.node)->expr_kind_val = EXPR_GT;
            (yyval.node)->left = (yyvsp[-2].node);
            (yyval.node)->right = (yyvsp[0].node);
        }
#line 1929 "src/parser.tab.c"
    break;

  case 62: /* expr: expr TOKEN_GREATER_EQUAL expr  */
#line 513 "src/parser.y"
        {
            (yyval.node) = create_node(NODE_EXPRESSION);
            (yyval.node)->expr_kind_val = EXPR_GE;
            (yyval.node)->left = (yyvsp[-2].node);
            (yyval.node)->right = (yyvsp[0].node);
        }
#line 1940 "src/parser.tab.c"
    break;

  case 63: /* expr: expr TOKEN_EQUAL expr  */
#line 520 "src/parser.y"
        {
            (yyval.node) = create_node(NODE_EXPRESSION);
            (yyval.node)->expr_kind_val = EXPR_EQ;
            (yyval.node)->left = (yyvsp[-2].node);
            (yyval.node)->right = (yyvsp[0].node);
        }
#line 1951 "src/parser.tab.c"
    break;

  case 64: /* expr: expr TOKEN_NOT_EQUAL expr  */
#line 527 "src/parser.y"
        {
            (yyval.node) = create_node(NODE_EXPRESSION);
            (yyval.node)->expr_kind_val = EXPR_NE;
            (yyval.node)->left = (yyvsp[-2].node);
            (yyval.node)->right = (yyvsp[0].node);
        }
#line 1962 "src/parser.tab.c"
    break;

  case 65: /* expr: expr TOKEN_LOGICAL_AND expr  */
#line 534 "src/parser.y"
        {
            (yyval.node) = create_node(NODE_EXPRESSION);
            (yyval.node)->expr_kind_val = EXPR_AND;
            (yyval.node)->left = (yyvsp[-2].node);
            (yyval.node)->right = (yyvsp[0].node);
        }
#line 1973 "src/parser.tab.c"
    break;

  case 66: /* expr: expr TOKEN_LOGICAL_OR expr  */
#line 541 "src/parser.y"
        {
            (yyval.node) = create_node(NODE_EXPRESSION);
            (yyval.node)->expr_kind_val = EXPR_OR;
            (yyval.node)->left = (yyvsp[-2].node);
            (yyval.node)->right = (yyvsp[0].node);
        }
#line 1984 "src/parser.tab.c"
    break;

  case 67: /* expr: TOKEN_LOGICAL_NOT expr  */
#line 548 "src/parser.y"
        {
            (yyval.node) = create_node(NODE_EXPRESSION);
            (yyval.node)->expr_kind_val = EXPR_NOT;
            (yyval.node)->left = (yyvsp[0].node);
        }
#line 1994 "src/parser.tab.c"
    break;

  case 68: /* expr: TOKEN_SUBTRACT expr  */
#line 554 "src/parser.y"
        {
            (yyval.node) = create_node(NODE_EXPRESSION);
            (yyval.node)->expr_kind_val = EXPR_NEG;
            (yyval.node)->left = (yyvsp[0].node);
        }
#line 2004 "src/parser.tab.c"
    break;

  case 69: /* expr: expr TOKEN_ASSIGN expr  */
#line 560 "src/parser.y"
        {
            (yyval.node) = create_node(NODE_EXPRESSION);
            (yyval.node)->expr_kind_val = EXPR_ASSIGN;
            (yyval.node)->left = (yyvsp[-2].node);
            (yyval.node)->right = (yyvsp[0].node);
        }
#line 2015 "src/parser.tab.c"
    break;

  case 70: /* expr: expr TOKEN_LBRACKET expr TOKEN_RBRACKET  */
#line 567 "src/parser.y"
        {
            (yyval.node) = create_node(NODE_EXPRESSION);
            (yyval.node)->expr_kind_val = EXPR_INDEX;
            (yyval.node)->left = (yyvsp[-3].node);
            (yyval.node)->right = (yyvsp[-1].node);
        }
#line 2026 "src/parser.tab.c"
    break;

  case 71: /* expr: TOKEN_IDENTIFIER TOKEN_LPAREN argument_list_opt TOKEN_RPAREN  */
#line 574 "src/parser.y"
        {
            (yyval.node) = create_node(NODE_EXPRESSION);
            (yyval.node)->expr_kind_val = EXPR_CALL;
            (yyval.node)->name = (yyvsp[-3].text);
            (yyval.node)->left = (yyvsp[-1].node);
        }
#line 2037 "src/parser.tab.c"
    break;

  case 72: /* expr: expr TOKEN_INCREMENT  */
#line 581 "src/parser.y"
        {
            (yyval.node) = create_node(NODE_EXPRESSION);
            (yyval.node)->expr_kind_val = EXPR_POST_INC;
            (yyval.node)->left = (yyvsp[-1].node);
        }
#line 2047 "src/parser.tab.c"
    break;

  case 73: /* expr: expr TOKEN_DECREMENT  */
#line 587 "src/parser.y"
        {
            (yyval.node) = create_node(NODE_EXPRESSION);
            (yyval.node)->expr_kind_val = EXPR_POST_DEC;
            (yyval.node)->left = (yyvsp[-1].node);
        }
#line 2057 "src/parser.tab.c"
    break;

  case 74: /* argument_list_opt: argument_list  */
#line 596 "src/parser.y"
        {
            (yyval.node) = (yyvsp[0].node);
        }
#line 2065 "src/parser.tab.c"
    break;

  case 75: /* argument_list_opt: %empty  */
#line 600 "src/parser.y"
        {
            (yyval.node) = NULL;
        }
#line 2073 "src/parser.tab.c"
    break;

  case 76: /* argument_list: expr  */
#line 607 "src/parser.y"
        {
            (yyval.node) = (yyvsp[0].node);
        }
#line 2081 "src/parser.tab.c"
    break;

  case 77: /* argument_list: argument_list TOKEN_COMMA expr  */
#line 611 "src/parser.y"
        {
            if ((yyvsp[-2].node) == NULL) {
                (yyval.node) = (yyvsp[0].node);
            } else {
                ASTNode *temp = (yyvsp[-2].node);
                while (temp->next != NULL)
                    temp = temp->next;
                temp->next = (yyvsp[0].node);
                (yyval.node) = (yyvsp[-2].node);
            }
        }
#line 2097 "src/parser.tab.c"
    break;


#line 2101 "src/parser.tab.c"

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

#line 624 "src/parser.y"


void yyerror(const char *s)
{
    fprintf(stderr, "PARSE ERROR: %s\n", s);
}
