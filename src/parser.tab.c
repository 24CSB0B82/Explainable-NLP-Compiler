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
#line 1 "parser.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ast.h"
#include "symbol_table.h"

int yylex(void);
int yyerror(const char *s);
extern int yylineno;
extern FILE *yyin;

static int syntax_error_count = 0;
static int semantic_error_count = 0;
static AstNode *ast_root = NULL;
static char current_decl_type[16] = "";

static char *dup_cstr(const char *s) {
    size_t n;
    char *copy;

    if (s == NULL) {
        return NULL;
    }

    n = strlen(s);
    copy = (char *)malloc(n + 1);
    if (copy == NULL) {
        return NULL;
    }

    memcpy(copy, s, n + 1);
    return copy;
}

static void set_decl_type(const char *type_name) {
    if (type_name == NULL) {
        current_decl_type[0] = '\0';
        return;
    }

    strncpy(current_decl_type, type_name, sizeof(current_decl_type) - 1);
    current_decl_type[sizeof(current_decl_type) - 1] = '\0';
}

static void report_undeclared(const char *name, int line) {
    fprintf(stderr, "Semantic error (line %d): '%s' used before declaration\n", line, name);
    semantic_error_count++;
}

#line 123 "parser.tab.c"

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
  YYSYMBOL_INT = 3,                        /* INT  */
  YYSYMBOL_CHAR = 4,                       /* CHAR  */
  YYSYMBOL_IF = 5,                         /* IF  */
  YYSYMBOL_ELSE = 6,                       /* ELSE  */
  YYSYMBOL_WHILE = 7,                      /* WHILE  */
  YYSYMBOL_ID = 8,                         /* ID  */
  YYSYMBOL_STRING = 9,                     /* STRING  */
  YYSYMBOL_NUMBER = 10,                    /* NUMBER  */
  YYSYMBOL_PLUS = 11,                      /* PLUS  */
  YYSYMBOL_MINUS = 12,                     /* MINUS  */
  YYSYMBOL_MUL = 13,                       /* MUL  */
  YYSYMBOL_DIV = 14,                       /* DIV  */
  YYSYMBOL_ASSIGN = 15,                    /* ASSIGN  */
  YYSYMBOL_GT = 16,                        /* GT  */
  YYSYMBOL_LT = 17,                        /* LT  */
  YYSYMBOL_GE = 18,                        /* GE  */
  YYSYMBOL_LE = 19,                        /* LE  */
  YYSYMBOL_EQ = 20,                        /* EQ  */
  YYSYMBOL_NE = 21,                        /* NE  */
  YYSYMBOL_LPAREN = 22,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 23,                    /* RPAREN  */
  YYSYMBOL_LBRACE = 24,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 25,                    /* RBRACE  */
  YYSYMBOL_SEMICOLON = 26,                 /* SEMICOLON  */
  YYSYMBOL_COMMA = 27,                     /* COMMA  */
  YYSYMBOL_YYACCEPT = 28,                  /* $accept  */
  YYSYMBOL_program = 29,                   /* program  */
  YYSYMBOL_stmt_list_opt = 30,             /* stmt_list_opt  */
  YYSYMBOL_stmt_list = 31,                 /* stmt_list  */
  YYSYMBOL_stmt = 32,                      /* stmt  */
  YYSYMBOL_declaration_stmt = 33,          /* declaration_stmt  */
  YYSYMBOL_34_1 = 34,                      /* $@1  */
  YYSYMBOL_type = 35,                      /* type  */
  YYSYMBOL_declarator_list = 36,           /* declarator_list  */
  YYSYMBOL_declarator = 37,                /* declarator  */
  YYSYMBOL_assignment_stmt = 38,           /* assignment_stmt  */
  YYSYMBOL_expr = 39,                      /* expr  */
  YYSYMBOL_term = 40,                      /* term  */
  YYSYMBOL_factor = 41,                    /* factor  */
  YYSYMBOL_if_stmt = 42,                   /* if_stmt  */
  YYSYMBOL_while_stmt = 43,                /* while_stmt  */
  YYSYMBOL_condition = 44,                 /* condition  */
  YYSYMBOL_relop = 45,                     /* relop  */
  YYSYMBOL_block = 46,                     /* block  */
  YYSYMBOL_47_2 = 47,                      /* $@2  */
  YYSYMBOL_function_call_stmt = 48,        /* function_call_stmt  */
  YYSYMBOL_arg_list = 49                   /* arg_list  */
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
typedef yytype_int8 yy_state_t;

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
#define YYFINAL  25
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   84

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  28
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  51
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  81

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   282


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
      25,    26,    27
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    84,    84,    92,    93,    97,    98,   102,   103,   104,
     105,   106,   107,   108,   112,   112,   123,   124,   128,   129,
     133,   140,   152,   161,   170,   176,   182,   186,   192,   198,
     202,   203,   210,   214,   218,   224,   234,   243,   250,   254,
     255,   256,   257,   258,   259,   263,   263,   272,   278,   287,
     288,   289
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
  "\"end of file\"", "error", "\"invalid token\"", "INT", "CHAR", "IF",
  "ELSE", "WHILE", "ID", "STRING", "NUMBER", "PLUS", "MINUS", "MUL", "DIV",
  "ASSIGN", "GT", "LT", "GE", "LE", "EQ", "NE", "LPAREN", "RPAREN",
  "LBRACE", "RBRACE", "SEMICOLON", "COMMA", "$accept", "program",
  "stmt_list_opt", "stmt_list", "stmt", "declaration_stmt", "$@1", "type",
  "declarator_list", "declarator", "assignment_stmt", "expr", "term",
  "factor", "if_stmt", "while_stmt", "condition", "relop", "block", "$@2",
  "function_call_stmt", "arg_list", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-44)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-5)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      18,   -24,   -44,   -44,    -2,     7,     2,   -44,    38,   -44,
       3,   -44,   -44,   -44,   -44,   -44,   -44,   -44,   -44,   -44,
      43,    43,    43,    43,    42,   -44,   -44,    32,   -44,   -44,
     -44,    43,    52,    46,   -44,    25,    34,     4,    23,    31,
      51,    62,    29,   -44,    21,    43,    43,   -44,   -44,   -44,
     -44,   -44,   -44,    43,    43,    43,    54,    54,   -44,   -44,
      11,    43,   -44,    43,   -44,    32,   -44,    46,    46,    23,
     -44,   -44,    73,   -44,   -44,   -44,    23,    23,   -44,    54,
     -44
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,    16,    17,     0,     0,     0,    45,     0,     2,
       0,     6,     7,    14,     8,     9,    10,    12,    11,    13,
       0,     0,     0,    51,     0,     1,     5,     0,    31,    32,
      30,     0,    38,    26,    29,     0,     0,     0,    50,     0,
       0,    20,     0,    19,     0,     0,     0,    39,    40,    41,
      42,    43,    44,     0,     0,     0,     0,     0,    23,    22,
       0,     0,    46,     0,    15,     0,    33,    24,    25,    37,
      27,    28,    34,    36,    48,    47,    49,    21,    18,     0,
      35
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -44,   -44,    56,   -44,    71,   -44,   -44,   -44,   -44,    17,
     -44,   -22,    16,    20,   -44,   -44,    63,   -44,   -43,   -44,
     -44,   -44
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     8,     9,    10,    11,    12,    27,    13,    42,    43,
      14,    32,    33,    34,    15,    16,    35,    53,    17,    24,
      18,    39
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      37,    38,    19,    -3,     1,    58,     2,     3,     4,    44,
       5,     6,    74,    72,    73,    45,    46,    22,    -4,     1,
      20,     2,     3,     4,    23,     5,     6,     7,    -3,    21,
      59,    69,    45,    46,    45,    46,    80,    75,    25,    76,
      41,    77,     7,     1,    66,     2,     3,     4,    56,     5,
       6,    28,    29,    30,    60,    64,    65,    57,    61,    54,
      55,    67,    68,    45,    46,    31,     7,    -4,    47,    48,
      49,    50,    51,    52,    70,    71,    62,    63,     7,    79,
      40,    26,    78,     0,    36
};

static const yytype_int8 yycheck[] =
{
      22,    23,    26,     0,     1,     1,     3,     4,     5,    31,
       7,     8,     1,    56,    57,    11,    12,    15,     0,     1,
      22,     3,     4,     5,    22,     7,     8,    24,    25,    22,
      26,    53,    11,    12,    11,    12,    79,    26,     0,    61,
       8,    63,    24,     1,    23,     3,     4,     5,    23,     7,
       8,     8,     9,    10,    23,    26,    27,    23,    27,    13,
      14,    45,    46,    11,    12,    22,    24,    25,    16,    17,
      18,    19,    20,    21,    54,    55,    25,    15,    24,     6,
      24,    10,    65,    -1,    21
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     1,     3,     4,     5,     7,     8,    24,    29,    30,
      31,    32,    33,    35,    38,    42,    43,    46,    48,    26,
      22,    22,    15,    22,    47,     0,    32,    34,     8,     9,
      10,    22,    39,    40,    41,    44,    44,    39,    39,    49,
      30,     8,    36,    37,    39,    11,    12,    16,    17,    18,
      19,    20,    21,    45,    13,    14,    23,    23,     1,    26,
      23,    27,    25,    15,    26,    27,    23,    40,    40,    39,
      41,    41,    46,    46,     1,    26,    39,    39,    37,     6,
      46
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    28,    29,    30,    30,    31,    31,    32,    32,    32,
      32,    32,    32,    32,    34,    33,    35,    35,    36,    36,
      37,    37,    38,    38,    39,    39,    39,    40,    40,    40,
      41,    41,    41,    41,    42,    42,    43,    44,    44,    45,
      45,    45,    45,    45,    45,    47,    46,    48,    48,    49,
      49,    49
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     0,     2,     1,     1,     1,     1,
       1,     1,     1,     2,     0,     4,     1,     1,     3,     1,
       1,     3,     4,     4,     3,     3,     1,     3,     3,     1,
       1,     1,     1,     3,     5,     7,     5,     3,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     5,     5,     3,
       1,     0
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
  case 2: /* program: stmt_list_opt  */
#line 84 "parser.y"
                    {
        ast_root = ast_create(AST_PROGRAM, NULL, 0, yylineno);
        ast_add_child(ast_root, (yyvsp[0].node));
        (yyval.node) = ast_root;
    }
#line 1217 "parser.tab.c"
    break;

  case 3: /* stmt_list_opt: stmt_list  */
#line 92 "parser.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 1223 "parser.tab.c"
    break;

  case 4: /* stmt_list_opt: %empty  */
#line 93 "parser.y"
                  { (yyval.node) = NULL; }
#line 1229 "parser.tab.c"
    break;

  case 5: /* stmt_list: stmt_list stmt  */
#line 97 "parser.y"
                     { (yyval.node) = ast_append_sibling((yyvsp[-1].node), (yyvsp[0].node)); }
#line 1235 "parser.tab.c"
    break;

  case 6: /* stmt_list: stmt  */
#line 98 "parser.y"
           { (yyval.node) = (yyvsp[0].node); }
#line 1241 "parser.tab.c"
    break;

  case 7: /* stmt: declaration_stmt  */
#line 102 "parser.y"
                       { (yyval.node) = (yyvsp[0].node); }
#line 1247 "parser.tab.c"
    break;

  case 8: /* stmt: assignment_stmt  */
#line 103 "parser.y"
                      { (yyval.node) = (yyvsp[0].node); }
#line 1253 "parser.tab.c"
    break;

  case 9: /* stmt: if_stmt  */
#line 104 "parser.y"
              { (yyval.node) = (yyvsp[0].node); }
#line 1259 "parser.tab.c"
    break;

  case 10: /* stmt: while_stmt  */
#line 105 "parser.y"
                 { (yyval.node) = (yyvsp[0].node); }
#line 1265 "parser.tab.c"
    break;

  case 11: /* stmt: function_call_stmt  */
#line 106 "parser.y"
                         { (yyval.node) = (yyvsp[0].node); }
#line 1271 "parser.tab.c"
    break;

  case 12: /* stmt: block  */
#line 107 "parser.y"
            { (yyval.node) = (yyvsp[0].node); }
#line 1277 "parser.tab.c"
    break;

  case 13: /* stmt: error SEMICOLON  */
#line 108 "parser.y"
                      { yyerror("discarded invalid statement"); yyerrok; (yyval.node) = NULL; }
#line 1283 "parser.tab.c"
    break;

  case 14: /* $@1: %empty  */
#line 112 "parser.y"
           { set_decl_type((yyvsp[0].sval)); free((yyvsp[0].sval)); }
#line 1289 "parser.tab.c"
    break;

  case 15: /* declaration_stmt: type $@1 declarator_list SEMICOLON  */
#line 112 "parser.y"
                                                                      {
        AstNode *decl_stmt = ast_create(AST_DECL_STMT, NULL, 0, yylineno);
        AstNode *type_node = ast_create(AST_TYPE, current_decl_type, 0, yylineno);

        ast_add_child(decl_stmt, type_node);
        ast_add_child(decl_stmt, (yyvsp[-1].node));
        (yyval.node) = decl_stmt;
    }
#line 1302 "parser.tab.c"
    break;

  case 16: /* type: INT  */
#line 123 "parser.y"
          { (yyval.sval) = dup_cstr("int"); }
#line 1308 "parser.tab.c"
    break;

  case 17: /* type: CHAR  */
#line 124 "parser.y"
           { (yyval.sval) = dup_cstr("char"); }
#line 1314 "parser.tab.c"
    break;

  case 18: /* declarator_list: declarator_list COMMA declarator  */
#line 128 "parser.y"
                                       { (yyval.node) = ast_append_sibling((yyvsp[-2].node), (yyvsp[0].node)); }
#line 1320 "parser.tab.c"
    break;

  case 19: /* declarator_list: declarator  */
#line 129 "parser.y"
                 { (yyval.node) = (yyvsp[0].node); }
#line 1326 "parser.tab.c"
    break;

  case 20: /* declarator: ID  */
#line 133 "parser.y"
         {
        if (!symtab_declare((yyvsp[0].sval), current_decl_type, yylineno)) {
            semantic_error_count++;
        }
        (yyval.node) = ast_create(AST_DECLARATOR, (yyvsp[0].sval), 0, yylineno);
        free((yyvsp[0].sval));
    }
#line 1338 "parser.tab.c"
    break;

  case 21: /* declarator: ID ASSIGN expr  */
#line 140 "parser.y"
                     {
        AstNode *decl = ast_create(AST_DECLARATOR, (yyvsp[-2].sval), 0, yylineno);
        if (!symtab_declare((yyvsp[-2].sval), current_decl_type, yylineno)) {
            semantic_error_count++;
        }
        ast_add_child(decl, (yyvsp[0].node));
        (yyval.node) = decl;
        free((yyvsp[-2].sval));
    }
#line 1352 "parser.tab.c"
    break;

  case 22: /* assignment_stmt: ID ASSIGN expr SEMICOLON  */
#line 152 "parser.y"
                               {
        AstNode *assign = ast_create(AST_ASSIGN_STMT, (yyvsp[-3].sval), 0, yylineno);
        if (symtab_lookup((yyvsp[-3].sval)) == NULL) {
            report_undeclared((yyvsp[-3].sval), yylineno);
        }
        ast_add_child(assign, (yyvsp[-1].node));
        (yyval.node) = assign;
        free((yyvsp[-3].sval));
    }
#line 1366 "parser.tab.c"
    break;

  case 23: /* assignment_stmt: ID ASSIGN expr error  */
#line 161 "parser.y"
                           {
        yyerror("missing ';' after assignment");
        yyerrok;
        free((yyvsp[-3].sval));
        (yyval.node) = NULL;
    }
#line 1377 "parser.tab.c"
    break;

  case 24: /* expr: expr PLUS term  */
#line 170 "parser.y"
                     {
        AstNode *op = ast_create(AST_BINOP, "+", 0, yylineno);
        ast_add_child(op, (yyvsp[-2].node));
        ast_add_child(op, (yyvsp[0].node));
        (yyval.node) = op;
    }
#line 1388 "parser.tab.c"
    break;

  case 25: /* expr: expr MINUS term  */
#line 176 "parser.y"
                      {
        AstNode *op = ast_create(AST_BINOP, "-", 0, yylineno);
        ast_add_child(op, (yyvsp[-2].node));
        ast_add_child(op, (yyvsp[0].node));
        (yyval.node) = op;
    }
#line 1399 "parser.tab.c"
    break;

  case 26: /* expr: term  */
#line 182 "parser.y"
           { (yyval.node) = (yyvsp[0].node); }
#line 1405 "parser.tab.c"
    break;

  case 27: /* term: term MUL factor  */
#line 186 "parser.y"
                      {
        AstNode *op = ast_create(AST_BINOP, "*", 0, yylineno);
        ast_add_child(op, (yyvsp[-2].node));
        ast_add_child(op, (yyvsp[0].node));
        (yyval.node) = op;
    }
#line 1416 "parser.tab.c"
    break;

  case 28: /* term: term DIV factor  */
#line 192 "parser.y"
                      {
        AstNode *op = ast_create(AST_BINOP, "/", 0, yylineno);
        ast_add_child(op, (yyvsp[-2].node));
        ast_add_child(op, (yyvsp[0].node));
        (yyval.node) = op;
    }
#line 1427 "parser.tab.c"
    break;

  case 29: /* term: factor  */
#line 198 "parser.y"
             { (yyval.node) = (yyvsp[0].node); }
#line 1433 "parser.tab.c"
    break;

  case 30: /* factor: NUMBER  */
#line 202 "parser.y"
             { (yyval.node) = ast_create(AST_NUMBER, NULL, (yyvsp[0].ival), yylineno); }
#line 1439 "parser.tab.c"
    break;

  case 31: /* factor: ID  */
#line 203 "parser.y"
         {
        if (symtab_lookup((yyvsp[0].sval)) == NULL) {
            report_undeclared((yyvsp[0].sval), yylineno);
        }
        (yyval.node) = ast_create(AST_IDENTIFIER, (yyvsp[0].sval), 0, yylineno);
        free((yyvsp[0].sval));
    }
#line 1451 "parser.tab.c"
    break;

  case 32: /* factor: STRING  */
#line 210 "parser.y"
             {
        (yyval.node) = ast_create(AST_STRING, (yyvsp[0].sval), 0, yylineno);
        free((yyvsp[0].sval));
    }
#line 1460 "parser.tab.c"
    break;

  case 33: /* factor: LPAREN expr RPAREN  */
#line 214 "parser.y"
                         { (yyval.node) = (yyvsp[-1].node); }
#line 1466 "parser.tab.c"
    break;

  case 34: /* if_stmt: IF LPAREN condition RPAREN block  */
#line 218 "parser.y"
                                       {
        AstNode *node = ast_create(AST_IF_STMT, NULL, 0, yylineno);
        ast_add_child(node, (yyvsp[-2].node));
        ast_add_child(node, (yyvsp[0].node));
        (yyval.node) = node;
    }
#line 1477 "parser.tab.c"
    break;

  case 35: /* if_stmt: IF LPAREN condition RPAREN block ELSE block  */
#line 224 "parser.y"
                                                  {
        AstNode *node = ast_create(AST_IF_STMT, "else", 0, yylineno);
        ast_add_child(node, (yyvsp[-4].node));
        ast_add_child(node, (yyvsp[-2].node));
        ast_add_child(node, (yyvsp[0].node));
        (yyval.node) = node;
    }
#line 1489 "parser.tab.c"
    break;

  case 36: /* while_stmt: WHILE LPAREN condition RPAREN block  */
#line 234 "parser.y"
                                          {
        AstNode *node = ast_create(AST_WHILE_STMT, NULL, 0, yylineno);
        ast_add_child(node, (yyvsp[-2].node));
        ast_add_child(node, (yyvsp[0].node));
        (yyval.node) = node;
    }
#line 1500 "parser.tab.c"
    break;

  case 37: /* condition: expr relop expr  */
#line 243 "parser.y"
                      {
        AstNode *node = ast_create(AST_BINOP, (yyvsp[-1].sval), 0, yylineno);
        ast_add_child(node, (yyvsp[-2].node));
        ast_add_child(node, (yyvsp[0].node));
        (yyval.node) = node;
        free((yyvsp[-1].sval));
    }
#line 1512 "parser.tab.c"
    break;

  case 38: /* condition: expr  */
#line 250 "parser.y"
           { (yyval.node) = (yyvsp[0].node); }
#line 1518 "parser.tab.c"
    break;

  case 39: /* relop: GT  */
#line 254 "parser.y"
         { (yyval.sval) = dup_cstr(">"); }
#line 1524 "parser.tab.c"
    break;

  case 40: /* relop: LT  */
#line 255 "parser.y"
         { (yyval.sval) = dup_cstr("<"); }
#line 1530 "parser.tab.c"
    break;

  case 41: /* relop: GE  */
#line 256 "parser.y"
         { (yyval.sval) = dup_cstr(">="); }
#line 1536 "parser.tab.c"
    break;

  case 42: /* relop: LE  */
#line 257 "parser.y"
         { (yyval.sval) = dup_cstr("<="); }
#line 1542 "parser.tab.c"
    break;

  case 43: /* relop: EQ  */
#line 258 "parser.y"
         { (yyval.sval) = dup_cstr("=="); }
#line 1548 "parser.tab.c"
    break;

  case 44: /* relop: NE  */
#line 259 "parser.y"
         { (yyval.sval) = dup_cstr("!="); }
#line 1554 "parser.tab.c"
    break;

  case 45: /* $@2: %empty  */
#line 263 "parser.y"
             { symtab_enter_scope(); }
#line 1560 "parser.tab.c"
    break;

  case 46: /* block: LBRACE $@2 stmt_list_opt RBRACE  */
#line 263 "parser.y"
                                                            {
        AstNode *node = ast_create(AST_BLOCK, NULL, 0, yylineno);
        ast_add_child(node, (yyvsp[-1].node));
        (yyval.node) = node;
        symtab_exit_scope();
    }
#line 1571 "parser.tab.c"
    break;

  case 47: /* function_call_stmt: ID LPAREN arg_list RPAREN SEMICOLON  */
#line 272 "parser.y"
                                          {
        AstNode *call = ast_create(AST_FUNC_CALL, (yyvsp[-4].sval), 0, yylineno);
        ast_add_child(call, (yyvsp[-2].node));
        (yyval.node) = call;
        free((yyvsp[-4].sval));
    }
#line 1582 "parser.tab.c"
    break;

  case 48: /* function_call_stmt: ID LPAREN arg_list RPAREN error  */
#line 278 "parser.y"
                                      {
        yyerror("missing ';' after function call");
        yyerrok;
        free((yyvsp[-4].sval));
        (yyval.node) = NULL;
    }
#line 1593 "parser.tab.c"
    break;

  case 49: /* arg_list: arg_list COMMA expr  */
#line 287 "parser.y"
                          { (yyval.node) = ast_append_sibling((yyvsp[-2].node), (yyvsp[0].node)); }
#line 1599 "parser.tab.c"
    break;

  case 50: /* arg_list: expr  */
#line 288 "parser.y"
           { (yyval.node) = (yyvsp[0].node); }
#line 1605 "parser.tab.c"
    break;

  case 51: /* arg_list: %empty  */
#line 289 "parser.y"
                  { (yyval.node) = NULL; }
#line 1611 "parser.tab.c"
    break;


#line 1615 "parser.tab.c"

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

#line 292 "parser.y"


int main(int argc, char **argv) {
    int parse_result;

    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        if (yyin == NULL) {
            fprintf(stderr, "Error: cannot open input file '%s'\n", argv[1]);
            return 1;
        }
    }

    symtab_init();
    parse_result = yyparse();

    if (parse_result == 0 && syntax_error_count == 0 && semantic_error_count == 0) {
        printf("Parse successful\n");
        if (ast_root != NULL) {
            printf("\nAST:\n");
            ast_print(ast_root, 0);
        }
    } else {
        if (parse_result == 0 && syntax_error_count > 0) {
            fprintf(stderr, "Parse completed with %d syntax error(s)\n", syntax_error_count);
        }
        if (semantic_error_count > 0) {
            fprintf(stderr, "Semantic analysis found %d issue(s)\n", semantic_error_count);
        }
        parse_result = 1;
    }

    ast_free(ast_root);
    symtab_destroy();

    if (yyin != NULL && yyin != stdin) {
        fclose(yyin);
    }

    return parse_result;
}

int yyerror(const char *s) {
    syntax_error_count++;
    fprintf(stderr, "Syntax error at line %d: %s\n", yylineno, s);
    return 0;
}
