/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "hoc.y" /* yacc.c:339  */

#include <stdio.h>
#include <ctype.h>
#ifdef STDC_HEADERS
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#else
char *malloc();
char *strchr();
#endif

#include "hoc.h"

#define code2(c1,c2)	code(c1);code(c2)
#define code3(c1,c2,c3)	code(c1);code(c2);code(c3)
#define code4(c1,c2,c3,c4)	code(c1);code(c2);code(c3);code(c4)
#if YYDEBUG
extern int yydebug;
#endif

static Constant zero;	/* zero.d=0 because it's statically allocated (which
                           has nothing to do with the "static" keyword) */

/* Default definitions of an empty function or procedure */
Inst deffunc[] = {	/* a function that does nothing but returns 0 */
	constpush,
	(Inst)&zero,
	funcret,
	STOP
};
Inst defproc[] = {	/* procedure that does nothing */
	procret,
	STOP
};

static char *atstring="";
int indef;
static int showprompt;	/* what the next yylex should show:
				0: no prompt, 1: new statement prompt
			*/

/* functions which will be defined below */
static void defnonly _PROTO((char *s));
static int skipc _PROTO((void));
static int backslash _PROTO((int c));
static char lookahead _PROTO((void));
static RETSIGTYPE fpecatch _PROTO((int sig));
static RETSIGTYPE intcatch _PROTO((int sig));
static int moreinput _PROTO((void));

static int yylex();
static void yyerror();

#line 121 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    EXIT = 258,
    BREAK = 259,
    CONT = 260,
    DEBUG = 261,
    LEVEL = 262,
    MOD = 263,
    PRCALLS = 264,
    IGNOREUNDEF = 265,
    LOCALCMD = 266,
    STRING = 267,
    PRINT = 268,
    VAR = 269,
    BLTIN = 270,
    UNDEF = 271,
    WHILE = 272,
    IF = 273,
    ELSE = 274,
    FOR = 275,
    PRNAMES = 276,
    INCLUDE = 277,
    FUNCTION = 278,
    PROCEDURE = 279,
    RETURN = 280,
    FUNC = 281,
    PROC = 282,
    READ = 283,
    SYSTEM = 284,
    LOCAL = 285,
    SET = 286,
    CONSTCMD = 287,
    CONST = 288,
    VERSION = 289,
    TYPE = 290,
    CALLFUNC = 291,
    CALLPROC = 292,
    ABORT = 293,
    DOEOF = 294,
    CHDIR = 295,
    ARG = 296,
    ARGCNT = 297,
    NUMBER = 298,
    ADDEQ = 299,
    SUBEQ = 300,
    MULEQ = 301,
    DIVEQ = 302,
    POWEQ = 303,
    REMEQ = 304,
    OR = 305,
    AND = 306,
    GT = 307,
    GE = 308,
    LT = 309,
    LE = 310,
    EQ = 311,
    NE = 312,
    APPROXEQ = 313,
    NOTAPPROXEQ = 314,
    UNARYMINUS = 315,
    NOT = 316,
    INCR = 317,
    DECR = 318
  };
#endif
/* Tokens.  */
#define EXIT 258
#define BREAK 259
#define CONT 260
#define DEBUG 261
#define LEVEL 262
#define MOD 263
#define PRCALLS 264
#define IGNOREUNDEF 265
#define LOCALCMD 266
#define STRING 267
#define PRINT 268
#define VAR 269
#define BLTIN 270
#define UNDEF 271
#define WHILE 272
#define IF 273
#define ELSE 274
#define FOR 275
#define PRNAMES 276
#define INCLUDE 277
#define FUNCTION 278
#define PROCEDURE 279
#define RETURN 280
#define FUNC 281
#define PROC 282
#define READ 283
#define SYSTEM 284
#define LOCAL 285
#define SET 286
#define CONSTCMD 287
#define CONST 288
#define VERSION 289
#define TYPE 290
#define CALLFUNC 291
#define CALLPROC 292
#define ABORT 293
#define DOEOF 294
#define CHDIR 295
#define ARG 296
#define ARGCNT 297
#define NUMBER 298
#define ADDEQ 299
#define SUBEQ 300
#define MULEQ 301
#define DIVEQ 302
#define POWEQ 303
#define REMEQ 304
#define OR 305
#define AND 306
#define GT 307
#define GE 308
#define LT 309
#define LE 310
#define EQ 311
#define NE 312
#define APPROXEQ 313
#define NOTAPPROXEQ 314
#define UNARYMINUS 315
#define NOT 316
#define INCR 317
#define DECR 318

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 55 "hoc.y" /* yacc.c:355  */

	Symbol	*sym;	/* symbol table pointer */
	Inst	*inst;	/* machine instruction */
	int	narg;	/* number of arguments */
	Constant *Const;/* constant number */

#line 294 "y.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 311 "y.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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


#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
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
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   684

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  81
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  30
/* YYNRULES -- Number of rules.  */
#define YYNRULES  167
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  281

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   318

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      80,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     6,     2,    74,     2,     2,
       3,     4,    72,    70,     9,    71,     2,    73,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     5,
       2,    51,     2,    58,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    79,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     7,    59,     8,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     1,     2,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    52,
      53,    54,    55,    56,    57,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    75,    76,    77,    78
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    88,    88,    89,    90,    91,    92,    93,    94,   100,
     102,   104,   105,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   133,   136,   138,   139,
     140,   141,   142,   143,   144,   189,   190,   191,   192,   193,
     194,   196,   199,   202,   205,   206,   207,   208,   211,   215,
     219,   226,   228,   230,   232,   234,   236,   238,   241,   243,
     245,   246,   247,   248,   250,   251,   253,   254,   256,   257,
     258,   259,   261,   263,   264,   266,   269,   272,   273,   275,
     276,   277,   278,   279,   280,   281,   282,   283,   284,   285,
     286,   287,   288,   289,   290,   291,   292,   301,   310,   311,
     323,   325,   326,   327,   328,   330,   330,   333,   333,   337,
     339,   340,   348,   349,   351,   355,   361,   363,   365,   366,
     368,   369,   371,   372,   374,   374,   374,   374,   374,   374,
     374,   374,   374,   374,   375,   375,   375,   375,   375,   375,
     375,   375,   375,   376,   376,   376,   376,   376,   376,   376,
     376,   376,   376,   377,   377,   377,   377,   377
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "'('", "')'", "';'", "'#'", "'{'", "'}'",
  "','", "EXIT", "BREAK", "CONT", "DEBUG", "LEVEL", "MOD", "PRCALLS",
  "IGNOREUNDEF", "LOCALCMD", "STRING", "PRINT", "VAR", "BLTIN", "UNDEF",
  "WHILE", "IF", "ELSE", "FOR", "PRNAMES", "INCLUDE", "FUNCTION",
  "PROCEDURE", "RETURN", "FUNC", "PROC", "READ", "SYSTEM", "LOCAL", "SET",
  "CONSTCMD", "CONST", "VERSION", "TYPE", "CALLFUNC", "CALLPROC", "ABORT",
  "DOEOF", "CHDIR", "ARG", "ARGCNT", "NUMBER", "'='", "ADDEQ", "SUBEQ",
  "MULEQ", "DIVEQ", "POWEQ", "REMEQ", "'?'", "'|'", "OR", "AND", "GT",
  "GE", "LT", "LE", "EQ", "NE", "APPROXEQ", "NOTAPPROXEQ", "'+'", "'-'",
  "'*'", "'/'", "'%'", "UNARYMINUS", "NOT", "INCR", "DECR", "'^'", "'\\n'",
  "$accept", "list", "newp", "newl", "asgn", "stmt", "fsc", "frp", "cond",
  "while", "if", "for", "begin", "end", "stmtlist", "opt_expr", "opt_stmt",
  "expr", "prlist", "defn", "$@1", "$@2", "procname", "opt_formals",
  "formals", "constname", "opt_arglist", "opt_arglist1", "arglist",
  "identifier", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,    40,    41,    59,    35,   123,   125,    44,
     258,   259,   260,   261,   262,   263,   264,   265,   266,   267,
     268,   269,   270,   271,   272,   273,   274,   275,   276,   277,
     278,   279,   280,   281,   282,   283,   284,   285,   286,   287,
     288,   289,   290,   291,   292,   293,   294,   295,   296,   297,
     298,    61,   299,   300,   301,   302,   303,   304,    63,   124,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
      43,    45,    42,    47,    37,   315,   316,   317,   318,    94,
      10
};
# endif

#define YYPACT_NINF -190

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-190)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -190,   150,  -190,     4,   514,  -190,   -30,   261,   514,   514,
     514,  -190,     7,    16,    44,    26,  -190,  -190,  -190,  -190,
      11,  -190,  -190,   514,    10,    10,    30,    17,    20,   -13,
    -190,  -190,    39,  -190,  -190,  -190,  -190,    24,   180,  -190,
    -190,   514,   514,   -16,     2,  -190,  -190,  -190,     4,     4,
      49,    49,    54,   307,     4,  -190,  -190,   283,    28,  -190,
       9,   535,  -190,   535,  -190,  -190,    12,  -190,   535,    51,
     514,   514,   514,   514,   514,   514,   514,  -190,  -190,   514,
       4,    58,    59,  -190,  -190,  -190,  -190,  -190,  -190,    46,
    -190,  -190,  -190,  -190,    18,   637,    65,    67,  -190,   514,
     514,   514,   514,   514,   514,   514,  -190,  -190,    -7,    -7,
    -190,  -190,  -190,  -190,  -190,  -190,   514,   261,   261,   261,
     514,   514,   514,   514,   514,   514,   514,   514,   514,   514,
     514,   514,   514,   514,   514,   514,   514,   514,  -190,  -190,
    -190,  -190,  -190,   261,   514,   470,   535,   535,   535,   535,
     535,   535,   535,   378,  -190,   514,   514,    68,    80,    81,
     514,  -190,  -190,  -190,  -190,  -190,  -190,  -190,  -190,  -190,
    -190,  -190,  -190,  -190,  -190,  -190,  -190,  -190,  -190,  -190,
    -190,  -190,  -190,  -190,  -190,  -190,  -190,  -190,  -190,  -190,
    -190,  -190,  -190,  -190,  -190,    82,   637,   637,   535,   535,
     535,   535,   535,   535,   535,   398,  -190,  -190,  -190,    83,
      -7,   507,   567,   139,   246,   246,   246,   246,   246,   246,
     246,   246,   254,   254,    -7,    -7,    -7,    -7,  -190,   535,
    -190,   535,  -190,   535,    87,   100,   106,    90,    90,  -190,
     535,  -190,   103,   103,  -190,  -190,    88,  -190,   514,   514,
    -190,   514,  -190,  -190,   109,   111,   114,   514,   137,   140,
     261,    83,   535,   535,   261,    94,   261,   100,  -190,  -190,
    -190,   261,  -190,  -190,  -190,  -190,   141,  -190,   261,  -190,
    -190
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     0,     0,    12,     0,    70,    74,    74,
      74,    45,     0,     0,    80,     0,    65,    66,    67,    48,
       0,    68,    68,    74,     0,     0,     0,     0,    43,     0,
      79,    49,     0,    68,    68,    40,    41,     0,    81,    82,
      78,     0,     0,     0,     0,    11,     3,    10,    83,     0,
       0,     0,     0,     0,     0,     9,    83,     0,     0,    71,
       0,    38,    39,    75,    46,    47,    36,   112,   111,    54,
       0,     0,     0,     0,     0,     0,     0,    21,    23,     0,
       0,    84,    51,    50,   119,   120,   121,   115,   117,     0,
      55,    44,   126,   127,     0,     0,     0,     0,    42,     0,
       0,     0,     0,     0,     0,     0,    32,    34,    97,   108,
      20,    31,    22,    33,     5,     6,     0,     0,     0,    76,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     7,     4,
      89,    56,    61,    72,     0,     0,    13,    14,    15,    16,
      17,    18,    19,     0,     8,   128,   128,     0,     0,     0,
       0,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   148,   149,   150,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   160,   161,   162,
     163,   164,   165,   166,   167,     0,     0,     0,    24,    25,
      26,    27,    28,    29,    30,     0,    69,    69,    77,     0,
      95,     0,   107,   106,    98,    99,   100,   101,   102,   105,
     103,   104,    90,    91,    92,    93,    94,    96,    73,    35,
     114,   113,    88,   132,     0,   129,     0,   122,   122,    87,
      37,   110,   130,   130,    64,    57,    58,    62,    74,     0,
      85,     0,    52,   124,     0,   123,     0,     0,     0,     0,
       0,     0,   109,   133,     0,     0,     0,   131,    86,    53,
      69,    76,   116,   125,   118,    59,     0,    63,     0,    69,
      60
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -190,  -190,     0,    86,   142,    -1,  -112,  -190,   101,  -190,
    -190,  -190,   -12,  -189,  -190,    -8,  -106,     3,  -190,  -190,
    -190,  -190,   144,   -72,  -190,  -190,    31,   -76,   -84,  -172
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    46,    47,    56,   208,   248,   278,   117,    50,
      51,    52,    81,   245,    60,    62,   209,    61,    69,    54,
     157,   158,    87,   254,   255,    94,   234,   258,   235,   195
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint16 yytable[] =
{
      49,    64,    65,    55,    53,   110,    59,    57,    92,     5,
      82,    63,    63,    63,     5,    83,    68,   142,   246,     4,
      58,    96,    97,   112,   242,   243,    63,    93,    66,    79,
      80,    84,   111,    89,    12,    67,    90,    14,    15,    91,
      85,    86,    95,    98,   108,   109,    21,   141,   114,   115,
     113,    26,   116,   138,   139,    29,    30,   119,    32,    33,
     145,   155,   156,   144,    38,    39,    40,   159,   196,   160,
     197,   237,   137,   146,   147,   148,   149,   150,   151,   152,
     154,   275,   153,   238,    45,   239,   241,    41,   247,    45,
     280,   250,    42,    43,    44,    70,    71,    72,    73,    74,
      75,    76,   198,   199,   200,   201,   202,   203,   204,   251,
     252,   253,   257,   264,   260,   273,   206,   207,   266,   205,
     265,    77,    78,   210,   211,   212,   213,   214,   215,   216,
     217,   218,   219,   220,   221,   222,   223,   224,   225,   226,
     227,   268,   228,    48,   269,   277,   143,   229,   231,   271,
       2,     3,   118,     4,   120,     5,     6,     7,   233,   233,
       8,     9,    10,   240,    11,   276,   256,   259,    12,    88,
      13,    14,    15,   267,    16,    17,     0,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,   236,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,     0,     0,     0,     0,   137,     0,
       0,    41,     0,     0,     0,     0,    42,    43,    44,     0,
      45,    99,   100,   101,   102,   103,   104,   105,     0,     0,
     261,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    63,   262,     0,   263,     0,     0,   106,   107,   270,
     233,   120,     0,   272,     4,   274,     0,     6,     7,   120,
       0,     8,     9,    10,     0,    11,     0,   279,     0,    12,
       0,    13,    14,    15,     0,    16,    17,   140,    18,    19,
       0,    21,    22,    23,     0,     0,    26,    27,   120,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,     5,     0,     0,     0,   132,   133,   134,   135,
     136,     0,   120,     0,     0,   137,   134,   135,   136,     0,
       0,     0,    41,   137,     0,     0,     0,    42,    43,    44,
       0,   121,     0,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   136,     0,     0,
       0,     0,   137,     0,     0,   121,     0,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   232,     0,     0,     0,   137,    45,     0,     0,
       0,     0,     0,   120,     0,     0,     0,     0,     0,     0,
       0,     0,   244,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   120,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   121,     0,   122,   123,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   136,     0,     0,     0,   121,   137,   122,   123,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   136,     4,     0,     0,     0,   137,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    12,   230,
       0,    14,    15,     0,     0,     0,     0,     0,     0,     0,
      21,     0,     0,     0,     0,    26,     0,     0,     0,    29,
      30,     0,    32,    33,     0,     0,     0,     4,    38,    39,
      40,     0,   120,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    12,     0,     0,    14,    15,     0,     0,     0,
       0,    41,     0,     0,    21,     0,    42,    43,    44,    26,
     120,     0,     0,    29,    30,     0,    32,    33,     0,     0,
       0,     0,    38,    39,    40,   121,   249,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   120,     0,     0,    41,   137,     0,     0,     0,
      42,    43,    44,   121,     0,   122,   123,   124,   125,   126,
     127,   128,   129,   130,   131,   132,   133,   134,   135,   136,
       0,     0,     0,     0,   137,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,     0,     0,     0,     0,   137,   161,   162,   163,
     164,   165,     0,     0,     0,   166,     0,   167,   168,   169,
     170,   171,   172,   173,   174,   175,   176,   177,   178,   179,
     180,   181,   182,   183,   184,   185,   186,   187,   188,   189,
     190,   191,   192,   193,   194
};

static const yytype_int16 yycheck[] =
{
       1,     9,    10,     3,     1,    21,     7,     4,    21,     5,
      22,     8,     9,    10,     5,    23,    13,     8,   207,     3,
      50,    33,    34,    21,   196,   197,    23,    40,    21,     3,
      19,    21,    48,     3,    18,    19,    19,    21,    22,    19,
      30,    31,     3,    19,    41,    42,    30,    19,    48,    49,
      48,    35,     3,    53,    54,    39,    40,     3,    42,    43,
       9,     3,     3,    51,    48,    49,    50,    21,     3,    51,
       3,     3,    79,    70,    71,    72,    73,    74,    75,    76,
      80,   270,    79,     3,    80,     4,     4,    71,     5,    80,
     279,     4,    76,    77,    78,    51,    52,    53,    54,    55,
      56,    57,    99,   100,   101,   102,   103,   104,   105,     9,
       4,    21,     9,     4,    26,    21,   117,   118,     4,   116,
       9,    77,    78,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,   131,   132,   133,   134,   135,   136,
     137,     4,   143,     1,     4,     4,    60,   144,   145,   261,
       0,     1,    51,     3,    15,     5,     6,     7,   155,   156,
      10,    11,    12,   160,    14,   271,   238,   243,    18,    25,
      20,    21,    22,   257,    24,    25,    -1,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,   156,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    -1,    -1,    -1,    -1,    79,    -1,
      -1,    71,    -1,    -1,    -1,    -1,    76,    77,    78,    -1,
      80,    51,    52,    53,    54,    55,    56,    57,    -1,    -1,
     248,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   248,   249,    -1,   251,    -1,    -1,    77,    78,   260,
     257,    15,    -1,   264,     3,   266,    -1,     6,     7,    15,
      -1,    10,    11,    12,    -1,    14,    -1,   278,    -1,    18,
      -1,    20,    21,    22,    -1,    24,    25,     4,    27,    28,
      -1,    30,    31,    32,    -1,    -1,    35,    36,    15,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,     5,    -1,    -1,    -1,    70,    71,    72,    73,
      74,    -1,    15,    -1,    -1,    79,    72,    73,    74,    -1,
      -1,    -1,    71,    79,    -1,    -1,    -1,    76,    77,    78,
      -1,    58,    -1,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    -1,    -1,
      -1,    -1,    79,    -1,    -1,    58,    -1,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,     4,    -1,    -1,    -1,    79,    80,    -1,    -1,
      -1,    -1,    -1,    15,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     4,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    15,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    58,    -1,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    -1,    -1,    -1,    58,    79,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,     3,    -1,    -1,    -1,    79,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    18,    19,
      -1,    21,    22,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      30,    -1,    -1,    -1,    -1,    35,    -1,    -1,    -1,    39,
      40,    -1,    42,    43,    -1,    -1,    -1,     3,    48,    49,
      50,    -1,    15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    18,    -1,    -1,    21,    22,    -1,    -1,    -1,
      -1,    71,    -1,    -1,    30,    -1,    76,    77,    78,    35,
      15,    -1,    -1,    39,    40,    -1,    42,    43,    -1,    -1,
      -1,    -1,    48,    49,    50,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    15,    -1,    -1,    71,    79,    -1,    -1,    -1,
      76,    77,    78,    58,    -1,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      -1,    -1,    -1,    -1,    79,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    -1,    -1,    -1,    -1,    79,    10,    11,    12,
      13,    14,    -1,    -1,    -1,    18,    -1,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    82,     0,     1,     3,     5,     6,     7,    10,    11,
      12,    14,    18,    20,    21,    22,    24,    25,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    71,    76,    77,    78,    80,    83,    84,    85,    86,
      90,    91,    92,    98,   100,    83,    85,    98,    50,    86,
      95,    98,    96,    98,    96,    96,    21,    19,    98,    99,
      51,    52,    53,    54,    55,    56,    57,    77,    78,     3,
      19,    93,    93,    96,    21,    30,    31,   103,   103,     3,
      19,    19,    21,    40,   106,     3,    93,    93,    19,    51,
      52,    53,    54,    55,    56,    57,    77,    78,    98,    98,
      21,    48,    21,    48,    83,    83,     3,    89,    89,     3,
      15,    58,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    79,    83,    83,
       4,    19,     8,    84,    51,     9,    98,    98,    98,    98,
      98,    98,    98,    98,    83,     3,     3,   101,   102,    21,
      51,    10,    11,    12,    13,    14,    18,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,   110,     3,     3,    98,    98,
      98,    98,    98,    98,    98,    98,    86,    86,    86,    97,
      98,    98,    98,    98,    98,    98,    98,    98,    98,    98,
      98,    98,    98,    98,    98,    98,    98,    98,    86,    98,
      19,    98,     4,    98,   107,   109,   107,     3,     3,     4,
      98,     4,   110,   110,     4,    94,    94,     5,    87,    59,
       4,     9,     4,    21,   104,   105,   104,     9,   108,   108,
      26,    96,    98,    98,     4,     9,     4,   109,     4,     4,
      86,    87,    86,    21,    86,    94,    97,     4,    88,    86,
      94
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    81,    82,    82,    82,    82,    82,    82,    82,    82,
      83,    84,    84,    85,    85,    85,    85,    85,    85,    85,
      85,    85,    85,    85,    85,    85,    85,    85,    85,    85,
      85,    85,    85,    85,    85,    85,    85,    85,    86,    86,
      86,    86,    86,    86,    86,    86,    86,    86,    86,    86,
      86,    86,    86,    86,    86,    86,    86,    86,    86,    86,
      86,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    95,    95,    95,    96,    96,    97,    97,    98,    98,
      98,    98,    98,    98,    98,    98,    98,    98,    98,    98,
      98,    98,    98,    98,    98,    98,    98,    98,    98,    98,
      98,    98,    98,    98,    98,    98,    98,    98,    98,    98,
      98,    99,    99,    99,    99,   101,   100,   102,   100,   103,
     103,   103,   104,   104,   105,   105,   106,   106,   107,   107,
     108,   108,   109,   109,   110,   110,   110,   110,   110,   110,
     110,   110,   110,   110,   110,   110,   110,   110,   110,   110,
     110,   110,   110,   110,   110,   110,   110,   110,   110,   110,
     110,   110,   110,   110,   110,   110,   110,   110
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     3,     3,     3,     3,     4,     3,
       1,     1,     1,     3,     3,     3,     3,     3,     3,     3,
       2,     2,     2,     2,     3,     3,     3,     3,     3,     3,
       3,     2,     2,     2,     2,     4,     2,     4,     1,     2,
       1,     1,     2,     1,     2,     1,     2,     2,     1,     1,
       2,     2,     5,     6,     2,     2,     3,     4,     4,     7,
      10,     3,     1,     1,     3,     1,     1,     1,     0,     0,
       0,     1,     2,     3,     0,     1,     0,     1,     1,     1,
       1,     1,     1,     1,     2,     5,     6,     4,     4,     3,
       3,     3,     3,     3,     3,     3,     3,     2,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     2,     5,
       4,     1,     1,     3,     3,     0,     7,     0,     7,     1,
       1,     1,     0,     1,     1,     3,     1,     1,     0,     1,
       0,     2,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
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
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
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
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
| yyreduce -- Do a reduction.  |
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
        case 2:
#line 88 "hoc.y" /* yacc.c:1646  */
    {showprompt=1;}
#line 1675 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 91 "hoc.y" /* yacc.c:1646  */
    {code2(popandforget,STOP);return 1;}
#line 1681 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 92 "hoc.y" /* yacc.c:1646  */
    {code(STOP);return 1;}
#line 1687 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 93 "hoc.y" /* yacc.c:1646  */
    {code2(print,STOP);return 1;}
#line 1693 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 94 "hoc.y" /* yacc.c:1646  */
    {code3(Include,(Inst)(yyvsp[-1].sym),STOP);return 1;}
#line 1699 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 100 "hoc.y" /* yacc.c:1646  */
    {yyerrok;}
#line 1705 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 102 "hoc.y" /* yacc.c:1646  */
    {showprompt=1;}
#line 1711 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 107 "hoc.y" /* yacc.c:1646  */
    {code3(varpush,(Inst)(yyvsp[-2].sym),assign);(yyval.inst)=(yyvsp[0].inst);}
#line 1717 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 108 "hoc.y" /* yacc.c:1646  */
    {code3(varpush,(Inst)(yyvsp[-2].sym),addeq);(yyval.inst)=(yyvsp[0].inst);}
#line 1723 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 109 "hoc.y" /* yacc.c:1646  */
    {code3(varpush,(Inst)(yyvsp[-2].sym),subeq);(yyval.inst)=(yyvsp[0].inst);}
#line 1729 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 110 "hoc.y" /* yacc.c:1646  */
    {code3(varpush,(Inst)(yyvsp[-2].sym),muleq);(yyval.inst)=(yyvsp[0].inst);}
#line 1735 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 111 "hoc.y" /* yacc.c:1646  */
    {code3(varpush,(Inst)(yyvsp[-2].sym),diveq);(yyval.inst)=(yyvsp[0].inst);}
#line 1741 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 112 "hoc.y" /* yacc.c:1646  */
    {code3(varpush,(Inst)(yyvsp[-2].sym),poweq);(yyval.inst)=(yyvsp[0].inst);}
#line 1747 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 113 "hoc.y" /* yacc.c:1646  */
    {code3(varpush,(Inst)(yyvsp[-2].sym),modeq);(yyval.inst)=(yyvsp[0].inst);}
#line 1753 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 114 "hoc.y" /* yacc.c:1646  */
    {(yyval.inst)=code3(varpush,(Inst)(yyvsp[0].sym),preinc);}
#line 1759 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 115 "hoc.y" /* yacc.c:1646  */
    {(yyval.inst)=code3(varpush,(Inst)(yyvsp[-1].sym),postinc);}
#line 1765 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 116 "hoc.y" /* yacc.c:1646  */
    {(yyval.inst)=code3(varpush,(Inst)(yyvsp[0].sym),predec);}
#line 1771 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 117 "hoc.y" /* yacc.c:1646  */
    {(yyval.inst)=code3(varpush,(Inst)(yyvsp[-1].sym),postdec);}
#line 1777 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 119 "hoc.y" /* yacc.c:1646  */
    {defnonly("$");
		code2(argassign,ITOINST((yyvsp[-2].narg)));(yyval.inst)=(yyvsp[0].inst);}
#line 1784 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 121 "hoc.y" /* yacc.c:1646  */
    {defnonly("$");code2(argaddeq,ITOINST((yyvsp[-2].narg)));(yyval.inst)=(yyvsp[0].inst);}
#line 1790 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 122 "hoc.y" /* yacc.c:1646  */
    {defnonly("$");code2(argsubeq,ITOINST((yyvsp[-2].narg)));(yyval.inst)=(yyvsp[0].inst);}
#line 1796 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 123 "hoc.y" /* yacc.c:1646  */
    {defnonly("$");code2(argmuleq,ITOINST((yyvsp[-2].narg)));(yyval.inst)=(yyvsp[0].inst);}
#line 1802 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 124 "hoc.y" /* yacc.c:1646  */
    {defnonly("$");code2(argdiveq,ITOINST((yyvsp[-2].narg)));(yyval.inst)=(yyvsp[0].inst);}
#line 1808 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 125 "hoc.y" /* yacc.c:1646  */
    {defnonly("$");code2(argpoweq,ITOINST((yyvsp[-2].narg)));(yyval.inst)=(yyvsp[0].inst);}
#line 1814 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 126 "hoc.y" /* yacc.c:1646  */
    {defnonly("$");code2(argmodeq,ITOINST((yyvsp[-2].narg)));(yyval.inst)=(yyvsp[0].inst);}
#line 1820 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 127 "hoc.y" /* yacc.c:1646  */
    {defnonly("$");(yyval.inst)=code2(argpreinc,ITOINST((yyvsp[0].narg)));}
#line 1826 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 128 "hoc.y" /* yacc.c:1646  */
    {defnonly("$");(yyval.inst)=code2(argpostinc,ITOINST((yyvsp[-1].narg)));}
#line 1832 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 129 "hoc.y" /* yacc.c:1646  */
    {defnonly("$");(yyval.inst)=code2(argpredec,ITOINST((yyvsp[0].narg)));}
#line 1838 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 130 "hoc.y" /* yacc.c:1646  */
    {defnonly("$");(yyval.inst)=code2(argpostdec,ITOINST((yyvsp[-1].narg)));}
#line 1844 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 131 "hoc.y" /* yacc.c:1646  */
    {defnonly("local");
				code3(varpush,(Inst)(yyvsp[-2].sym),makelocal);(yyval.inst)=(yyvsp[0].inst);}
#line 1851 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 133 "hoc.y" /* yacc.c:1646  */
    {defnonly("local");
				(yyval.inst)=code2(constpush,(Inst)&zero);
				code3(varpush,(Inst)(yyvsp[0].sym),makelocal);}
#line 1859 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 136 "hoc.y" /* yacc.c:1646  */
    {code3(varpush,(Inst)(yyvsp[-2].sym),makeconst);(yyval.inst)=(yyvsp[0].inst);}
#line 1865 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 138 "hoc.y" /* yacc.c:1646  */
    {code(popandforget);}
#line 1871 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 139 "hoc.y" /* yacc.c:1646  */
    {if((yyval.inst)=(yyvsp[0].inst))code(exitn);else (yyval.inst)=code(exit0);}
#line 1877 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 140 "hoc.y" /* yacc.c:1646  */
    {(yyval.inst)=code(Abort);}
#line 1883 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 141 "hoc.y" /* yacc.c:1646  */
    {(yyval.inst)=code(Doeof);}
#line 1889 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 142 "hoc.y" /* yacc.c:1646  */
    {(yyval.inst)=code2(Chdir,(Inst)(yyvsp[0].sym));}
#line 1895 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 143 "hoc.y" /* yacc.c:1646  */
    {(yyval.inst)=code2(Set,(Inst)0);}
#line 1901 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 144 "hoc.y" /* yacc.c:1646  */
    {int sign=1;char *save2=(char *)(yyvsp[0].sym);
				if(((char *)(yyvsp[0].sym))[0]=='n' && ((char *)(yyvsp[0].sym))[1]=='o'){
					sign= -1;
					(yyvsp[0].sym)=(Symbol *) (((char *)(yyvsp[0].sym))+2);
				}
				if(!strcmp((char *)(yyvsp[0].sym),"ignoreundef")){
					(yyval.inst)=code2(Set,ITOINST(sign*S_IGNOREUNDEF));
					free(save2);
				} else if(!strcmp((char *)(yyvsp[0].sym),"tracecalls")){
					(yyval.inst)=code2(Set,ITOINST(sign*S_TRACECALLS));
					free(save2);
				} else if(!strcmp((char *)(yyvsp[0].sym),"allnames")){
					(yyval.inst)=code2(Set,ITOINST(sign*S_ALLNAMES));
					free(save2);
				}
#if YYDEBUG
				else if(!strncmp((char *)(yyvsp[0].sym),"debug",5)){
					if((*(((char *)(yyvsp[0].sym))+5))=='\0'&&sign!=-1)
						goto SETERROR;
					if(sign==-1){
						if((*(((char*)(yyvsp[0].sym))+5))!='\0')
							goto SETERROR;
						yydebug=0;
					} else {
						yydebug=atoi(((char *)(yyvsp[0].sym))+5);
						free(save2);
					}
					(yyval.inst)=progp;
				}
#endif
				else if(!strcmp((char *)(yyvsp[0].sym),"all")){
					if(sign==-1) goto SETERROR;
					(yyval.inst)=code2(Set,(Inst)S_ALL);
					free(save2);
				} else if(!strcmp((char *)(yyvsp[0].sym),"default")){
					if(sign==-1) goto SETERROR;
					(yyval.inst)=code2(Set,(Inst)S_DEFAULT);
					free(save2);
				} else if(!strncmp((char *)(yyvsp[0].sym),"@=",2)){
					if(sign==-1) goto SETERROR;
					atstring=(char *)(yyvsp[0].sym) + 2;
					(yyval.inst)=progp;
				} else {
SETERROR:				free(save2);execerror("bad set option",(char *)0);
				}}
#line 1951 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 189 "hoc.y" /* yacc.c:1646  */
    {(yyval.inst)=code(Free);}
#line 1957 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 190 "hoc.y" /* yacc.c:1646  */
    {if((yyval.inst)=(yyvsp[0].inst))code(Breakn);else (yyval.inst)=code(Break);}
#line 1963 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 191 "hoc.y" /* yacc.c:1646  */
    {if((yyval.inst)=(yyvsp[0].inst))code(contn);else (yyval.inst)=code(cont);}
#line 1969 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 192 "hoc.y" /* yacc.c:1646  */
    {(yyval.inst)=code(printnames);}
#line 1975 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 193 "hoc.y" /* yacc.c:1646  */
    {(yyval.inst)=code(printversion);}
#line 1981 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 194 "hoc.y" /* yacc.c:1646  */
    {defnonly("return");if((yyval.inst)=(yyvsp[0].inst))code(funcret);
				else (yyval.inst)=code(procret);}
#line 1988 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 197 "hoc.y" /* yacc.c:1646  */
    {(yyval.inst)=(yyvsp[0].inst);
		code4(call,(Inst)(yyvsp[-1].sym),(Inst)0,(Inst)PROCEDURE);}
#line 1995 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 200 "hoc.y" /* yacc.c:1646  */
    {(yyval.inst)=(yyvsp[-3].inst);
		code4(call,(Inst)(yyvsp[-4].sym),ITOINST((yyvsp[-1].narg)),(Inst)PROCEDURE);}
#line 2002 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 203 "hoc.y" /* yacc.c:1646  */
    {(yyval.inst)=(yyvsp[-4].inst);
		code4(call,(Inst)(yyvsp[-2].sym),ITOINST((yyvsp[-1].narg)),(Inst)PROCEDURE);}
#line 2009 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 205 "hoc.y" /* yacc.c:1646  */
    {(yyval.inst)=(yyvsp[0].inst);code(doflush);}
#line 2015 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 206 "hoc.y" /* yacc.c:1646  */
    {(yyval.inst)=code2(System,(Inst)(yyvsp[0].sym));}
#line 2021 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 207 "hoc.y" /* yacc.c:1646  */
    {Line((Inst)(yyvsp[-1].Const),(Inst)(yyvsp[0].sym));(yyval.inst)=progp;}
#line 2027 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 208 "hoc.y" /* yacc.c:1646  */
    {
		((yyvsp[-3].inst))[1] = (Inst)((yyvsp[-1].inst)-((yyvsp[-3].inst)+1));	/* body of loop */
		((yyvsp[-3].inst))[2] = (Inst)((yyvsp[0].inst)-((yyvsp[-3].inst)+1));}
#line 2035 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 211 "hoc.y" /* yacc.c:1646  */
    {		/* else-less if */
		((yyvsp[-3].inst))[1] = (Inst)((yyvsp[-1].inst)-((yyvsp[-3].inst)+1));	/* thenpart */
		((yyvsp[-3].inst))[2]	= (Inst)0;		/* no elsepart */
		((yyvsp[-3].inst))[3] = (Inst)((yyvsp[0].inst)-((yyvsp[-3].inst)+1));}
#line 2044 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 215 "hoc.y" /* yacc.c:1646  */
    {	/* if with else */
		((yyvsp[-6].inst))[1] = (Inst)((yyvsp[-4].inst)-((yyvsp[-6].inst)+1));	/* thenpart */
		((yyvsp[-6].inst))[2] = (Inst)((yyvsp[-1].inst)-((yyvsp[-6].inst)+1));	/* elsepart */
		((yyvsp[-6].inst))[3] = (Inst)((yyvsp[0].inst)-((yyvsp[-6].inst)+1));}
#line 2053 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 219 "hoc.y" /* yacc.c:1646  */
    {
		if((yyvsp[-7].inst)) ((yyvsp[-9].inst))[1]=(Inst)((yyvsp[-7].inst)-((yyvsp[-9].inst)+1)); else ((yyvsp[-9].inst))[1]=(Inst)0;/*1st*/
		if((yyvsp[-5].inst)) ((yyvsp[-9].inst))[2]=(Inst)((yyvsp[-5].inst)-((yyvsp[-9].inst)+1)); else ((yyvsp[-9].inst))[2]=(Inst)0;/*2nd*/
		if((yyvsp[-3].inst)) ((yyvsp[-9].inst))[3]=(Inst)((yyvsp[-3].inst)-((yyvsp[-9].inst)+1)); else ((yyvsp[-9].inst))[3]=(Inst)0;/*3rd*/
		((yyvsp[-9].inst))[4]=(Inst)((yyvsp[-1].inst)-((yyvsp[-9].inst)+1));/*stmt*/
		((yyvsp[-9].inst))[5]=(Inst)((yyvsp[0].inst)-((yyvsp[-9].inst)+1));/*end*/
		}
#line 2065 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 226 "hoc.y" /* yacc.c:1646  */
    {(yyval.inst)=(yyvsp[-1].inst);}
#line 2071 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 228 "hoc.y" /* yacc.c:1646  */
    {code(STOP);	/*for's semi-colon*/}
#line 2077 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 230 "hoc.y" /* yacc.c:1646  */
    {code(STOP);	/*for's right parenthesis*/}
#line 2083 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 232 "hoc.y" /* yacc.c:1646  */
    {code(STOP);(yyval.inst)=(yyvsp[-1].inst);}
#line 2089 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 234 "hoc.y" /* yacc.c:1646  */
    {(yyval.inst)=code3(whilecode,STOP,STOP);}
#line 2095 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 236 "hoc.y" /* yacc.c:1646  */
    {(yyval.inst)=code(ifcode);code3(STOP,STOP,STOP);}
#line 2101 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 238 "hoc.y" /* yacc.c:1646  */
    {(yyval.inst)=code3(forcode,STOP,STOP);
				code3(STOP,STOP,STOP);}
#line 2108 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 241 "hoc.y" /* yacc.c:1646  */
    {(yyval.inst)=progp;}
#line 2114 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 243 "hoc.y" /* yacc.c:1646  */
    {code(STOP);(yyval.inst)=progp;}
#line 2120 "y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 245 "hoc.y" /* yacc.c:1646  */
    {(yyval.inst)=progp;}
#line 2126 "y.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 250 "hoc.y" /* yacc.c:1646  */
    {(yyval.inst)=0;}
#line 2132 "y.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 253 "hoc.y" /* yacc.c:1646  */
    {(yyval.inst)=0;}
#line 2138 "y.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 256 "hoc.y" /* yacc.c:1646  */
    {(yyval.inst)=code2(constpush,(Inst)(yyvsp[0].Const));}
#line 2144 "y.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 257 "hoc.y" /* yacc.c:1646  */
    {(yyval.inst)=code2(constpush,(Inst)(yyvsp[0].sym)->u.Const);}
#line 2150 "y.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 258 "hoc.y" /* yacc.c:1646  */
    {(yyval.inst)=code3(varpush,(Inst)(yyvsp[0].sym),eval);}
#line 2156 "y.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 259 "hoc.y" /* yacc.c:1646  */
    {defnonly("$");
				(yyval.inst)=code2(arg,ITOINST((yyvsp[0].narg)));}
#line 2163 "y.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 261 "hoc.y" /* yacc.c:1646  */
    {defnonly("$");
				(yyval.inst)=code(argcnt);}
#line 2170 "y.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 265 "hoc.y" /* yacc.c:1646  */
    {(yyval.inst)=(yyvsp[0].inst); code4(call,(Inst)(yyvsp[-1].sym),(Inst)0,(Inst)FUNCTION);}
#line 2176 "y.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 267 "hoc.y" /* yacc.c:1646  */
    {(yyval.inst)=(yyvsp[-3].inst);
				code4(call,(Inst)(yyvsp[-4].sym),ITOINST((yyvsp[-1].narg)),(Inst)FUNCTION);}
#line 2183 "y.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 270 "hoc.y" /* yacc.c:1646  */
    {(yyval.inst)=(yyvsp[-4].inst);
				code4(call,(Inst)(yyvsp[-2].sym),ITOINST((yyvsp[-1].narg)),(Inst)FUNCTION);}
#line 2190 "y.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 272 "hoc.y" /* yacc.c:1646  */
    {(yyval.inst)=code2(varread,(Inst)(yyvsp[-1].sym));}
#line 2196 "y.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 273 "hoc.y" /* yacc.c:1646  */
    {(yyval.inst)=(yyvsp[-1].inst);
				code2(bltin,(Inst)(yyvsp[-3].sym)->u.ptr);}
#line 2203 "y.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 275 "hoc.y" /* yacc.c:1646  */
    {(yyval.inst)=(yyvsp[-1].inst);}
#line 2209 "y.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 276 "hoc.y" /* yacc.c:1646  */
    {code(add);}
#line 2215 "y.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 277 "hoc.y" /* yacc.c:1646  */
    {code(sub);}
#line 2221 "y.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 278 "hoc.y" /* yacc.c:1646  */
    {code(mul);}
#line 2227 "y.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 279 "hoc.y" /* yacc.c:1646  */
    {code(Div);}
#line 2233 "y.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 280 "hoc.y" /* yacc.c:1646  */
    {code(mod);}
#line 2239 "y.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 281 "hoc.y" /* yacc.c:1646  */
    {code(Mod);}
#line 2245 "y.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 282 "hoc.y" /* yacc.c:1646  */
    {code(power);}
#line 2251 "y.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 283 "hoc.y" /* yacc.c:1646  */
    {(yyval.inst)=(yyvsp[0].inst);code(negate);}
#line 2257 "y.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 284 "hoc.y" /* yacc.c:1646  */
    {code(gt);}
#line 2263 "y.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 285 "hoc.y" /* yacc.c:1646  */
    {code(ge);}
#line 2269 "y.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 286 "hoc.y" /* yacc.c:1646  */
    {code(lt);}
#line 2275 "y.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 287 "hoc.y" /* yacc.c:1646  */
    {code(le);}
#line 2281 "y.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 288 "hoc.y" /* yacc.c:1646  */
    {code(eq);}
#line 2287 "y.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 289 "hoc.y" /* yacc.c:1646  */
    {code(approxeq);}
#line 2293 "y.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 290 "hoc.y" /* yacc.c:1646  */
    {code(notapproxeq);}
#line 2299 "y.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 291 "hoc.y" /* yacc.c:1646  */
    {code(ne);}
#line 2305 "y.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 292 "hoc.y" /* yacc.c:1646  */
    {
				move((yyval.inst)=(yyvsp[-2].inst),3);
				move((yyvsp[0].inst)+3,1);
				code(STOP);
				((yyvsp[-2].inst))[0]=(Inst)and;
				((yyvsp[-2].inst))[1]=(Inst)(3+(yyvsp[0].inst)-(yyvsp[-2].inst));
				((yyvsp[-2].inst))[2]=(Inst)(progp-(yyvsp[-2].inst)-1);
				((yyvsp[0].inst))[3]=STOP;
				}
#line 2319 "y.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 301 "hoc.y" /* yacc.c:1646  */
    {
				move((yyval.inst)=(yyvsp[-2].inst),3);
				move((yyvsp[0].inst)+3,1);
				code(STOP);
				((yyvsp[-2].inst))[0]=(Inst)or;
				((yyvsp[-2].inst))[1]=(Inst)(3+(yyvsp[0].inst)-(yyvsp[-2].inst));
				((yyvsp[-2].inst))[2]=(Inst)(progp-(yyvsp[-2].inst)-1);
				((yyvsp[0].inst))[3]=STOP;
				}
#line 2333 "y.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 310 "hoc.y" /* yacc.c:1646  */
    {(yyval.inst)=(yyvsp[0].inst);code(not);}
#line 2339 "y.tab.c" /* yacc.c:1646  */
    break;

  case 109:
#line 311 "hoc.y" /* yacc.c:1646  */
    {
				move((yyval.inst)=(yyvsp[-4].inst),4);
				move((yyvsp[-2].inst)+4,1);
				move((yyvsp[0].inst)+5,1);
				code(STOP);
				((yyvsp[-4].inst))[0]=(Inst)conditional;
				((yyvsp[-4].inst))[1]=(Inst)(4+(yyvsp[-2].inst)-(yyvsp[-4].inst));
				((yyvsp[-4].inst))[2]=(Inst)(5+(yyvsp[0].inst)-(yyvsp[-4].inst));
				((yyvsp[-4].inst))[3]=(Inst)(progp-(yyvsp[-4].inst)-1);
				((yyvsp[-2].inst))[4]=STOP;
				((yyvsp[0].inst))[5]=STOP;
				}
#line 2356 "y.tab.c" /* yacc.c:1646  */
    break;

  case 110:
#line 323 "hoc.y" /* yacc.c:1646  */
    {(yyval.inst)=code2(findtype,(Inst)(yyvsp[-1].sym));}
#line 2362 "y.tab.c" /* yacc.c:1646  */
    break;

  case 111:
#line 325 "hoc.y" /* yacc.c:1646  */
    {code(prexpr);}
#line 2368 "y.tab.c" /* yacc.c:1646  */
    break;

  case 112:
#line 326 "hoc.y" /* yacc.c:1646  */
    {(yyval.inst)=code2(prstr,(Inst)(yyvsp[0].sym));}
#line 2374 "y.tab.c" /* yacc.c:1646  */
    break;

  case 113:
#line 327 "hoc.y" /* yacc.c:1646  */
    {code(prexpr);}
#line 2380 "y.tab.c" /* yacc.c:1646  */
    break;

  case 114:
#line 328 "hoc.y" /* yacc.c:1646  */
    {code2(prstr,(Inst)(yyvsp[0].sym));}
#line 2386 "y.tab.c" /* yacc.c:1646  */
    break;

  case 115:
#line 330 "hoc.y" /* yacc.c:1646  */
    {if(!(yyvsp[0].sym)->u.defn)(yyvsp[0].sym)->u.defn=(Inst)deffunc;
				(yyvsp[0].sym)->type=FUNCTION;indef=1;}
#line 2393 "y.tab.c" /* yacc.c:1646  */
    break;

  case 116:
#line 332 "hoc.y" /* yacc.c:1646  */
    {code(procret);define((yyvsp[-5].sym));indef=0;}
#line 2399 "y.tab.c" /* yacc.c:1646  */
    break;

  case 117:
#line 333 "hoc.y" /* yacc.c:1646  */
    {if(!(yyvsp[0].sym)->u.defn)(yyvsp[0].sym)->u.defn=(Inst)defproc;
				(yyvsp[0].sym)->type=PROCEDURE;indef=1;}
#line 2406 "y.tab.c" /* yacc.c:1646  */
    break;

  case 118:
#line 335 "hoc.y" /* yacc.c:1646  */
    {code(procret);define((yyvsp[-5].sym));indef=0;}
#line 2412 "y.tab.c" /* yacc.c:1646  */
    break;

  case 119:
#line 337 "hoc.y" /* yacc.c:1646  */
    {if((yyvsp[0].sym)->type==VAR)
					execerror("attempt to make func/proc with a variable name",(yyvsp[0].sym)->name);}
#line 2419 "y.tab.c" /* yacc.c:1646  */
    break;

  case 124:
#line 351 "hoc.y" /* yacc.c:1646  */
    { (yyval.narg)=1;
		code2(arg, ITOINST((yyval.narg)));
		code2(varpush,(Inst)(yyvsp[0].sym));
		code2(makelocal, popandforget); }
#line 2428 "y.tab.c" /* yacc.c:1646  */
    break;

  case 125:
#line 355 "hoc.y" /* yacc.c:1646  */
    { (yyval.narg)=(yyvsp[-2].narg)+1;
		code2(arg, ITOINST((yyval.narg)));
		code2(varpush, (Inst)(yyvsp[0].sym));
		code2(makelocal, popandforget); }
#line 2437 "y.tab.c" /* yacc.c:1646  */
    break;

  case 126:
#line 361 "hoc.y" /* yacc.c:1646  */
    {if((yyvsp[0].sym)->type==VAR)
					execerror("attempt to make constant with a variable name",(yyvsp[0].sym)->name);}
#line 2444 "y.tab.c" /* yacc.c:1646  */
    break;

  case 128:
#line 365 "hoc.y" /* yacc.c:1646  */
    {(yyval.narg)=0;}
#line 2450 "y.tab.c" /* yacc.c:1646  */
    break;

  case 129:
#line 366 "hoc.y" /* yacc.c:1646  */
    {(yyval.narg)=(yyvsp[0].narg);}
#line 2456 "y.tab.c" /* yacc.c:1646  */
    break;

  case 130:
#line 368 "hoc.y" /* yacc.c:1646  */
    {(yyval.narg)=0;}
#line 2462 "y.tab.c" /* yacc.c:1646  */
    break;

  case 131:
#line 369 "hoc.y" /* yacc.c:1646  */
    {(yyval.narg)=(yyvsp[0].narg);}
#line 2468 "y.tab.c" /* yacc.c:1646  */
    break;

  case 132:
#line 371 "hoc.y" /* yacc.c:1646  */
    {(yyval.narg)=1;}
#line 2474 "y.tab.c" /* yacc.c:1646  */
    break;

  case 133:
#line 372 "hoc.y" /* yacc.c:1646  */
    {(yyval.narg)=(yyvsp[-2].narg)+1;}
#line 2480 "y.tab.c" /* yacc.c:1646  */
    break;


#line 2484 "y.tab.c" /* yacc.c:1646  */
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
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
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 378 "hoc.y" /* yacc.c:1906  */


#include <signal.h>
#include <setjmp.h>
#ifdef HAVE_SIGLONGJMP
sigjmp_buf begin;
#else
jmp_buf begin;
#endif

char **gargv;
int gargc;
char *progname;

int lineno=1;
char *infile;
FILE *fin;
int c,nlstate=1;
static int endfile=0;
int interactive;

static char *SCCSID="@(#)NYH HOC - by Brian Kernighan, Rob Pike, Nadav Har'El";

static int
yylex()
{
	/* On interactive sessions (read file is stdin, and it is connected
	   to a terminal, we show a prompt on new lines.
	   If this is the first lexical symbol in a complete statement,
	   showprompt is still 1 (see yacc code above) and we show a "hoc>"
	   prompt. Otherwise, we output a tab if currently defining a func
	   or proc, or output a ">" otherwise (e.g., in the middle of a
	   stmtlist).
	*/
	if(interactive && nlstate){
		if(showprompt) fprintf(stderr,"hoc> ");
		else if(indef) fprintf(stderr,"\t");
		else fprintf(stderr,"> ");
		showprompt=0;
	}

BEGYYLEX:
#ifdef MSDOS
	/* if in MSDOS there may be junk cr's and ^Z's (eof) */
	while((c=getc(fin))==' '||c=='\t'||c=='\r'||c=='\032')nlstate=0;
#else
	/* there is no need to set nlstate=0 for each and every space character,
	   but we don't care since this such a fast operation
	*/
	while((c=getc(fin))==' '||c=='\t')nlstate=0;
#endif
		;
	if(c==EOF)
		return 0;
	if ((c == '/') && lookahead() == '*'){
		getc(fin); /*throw out the * */
		if(!skipc()){nlstate=0; return 0;}
		nlstate=0;
		goto BEGYYLEX;
	}
	/* If we see a backward slash followed by a \n or \r then
	   we discard the backward slash and all \n or \r's that follow
	   it. Note that \ can not be used to continue, for example, an
	   identifier name on the next line - it can only be used between
	   two different lexical symbols.
	*/
	if(c == '\\'){
		int z;
		if((z=lookahead())=='\r' || z=='\n'){
			z=getc(fin);
			while(z=='\r'||z=='\n'){
				if(z=='\n'){
					lineno++;
					nlstate=1;
				}
				z=getc(fin);
			}
			if(z==EOF) return 0;
			else ungetc(z,fin);
			goto BEGYYLEX;
		}
	}
		
	/* support for nroff commands inside a hoc file is there for historic
	   reasons. at least when in interactive mode we don't have to support
	   it.
	*/
	if(c=='.' && nlstate && !interactive){
		while((c=getc(fin))!='\n'&&c!=EOF)
			;
		lineno++;
		goto BEGYYLEX;
	}
	if( (c=='.' && isdigit(lookahead())) || isdigit(c)){
		double d;
		ungetc(c,fin);
		/* the condition above should guarantee that the following
		   fscanf succeed. However, in the future I should probably
		   check that it indeed succeeds and else print a sanity
		   check error otherwise.
		*/
		fscanf(fin,"%lf",&d);
		yylval.Const=installd(d);
		nlstate=0;return NUMBER;
	}
	if(c=='_'){
		int z;
		if((z=lookahead())!='_'&&!isalnum(z)){
			extern double last;
			yylval.sym=install("_",VAR,last);
			nlstate=0;return VAR;
		}
	}
	if(isalpha(c)||c=='_'|| (c=='@'&&(lookahead()=='_'||isalnum(lookahead()))) ){
		Symbol *s;
		char sbuf[100], *p = sbuf;
		if(c=='@'){
			int i;
			for(i=0;atstring[i];i++){
				if(p>=sbuf+sizeof(sbuf)-1){
					*p='\0';
					execerror("@ string too long", sbuf);
				}
				*p++=atstring[i];
			}
			c=getc(fin);
		}
		do {
			if (p>=sbuf+sizeof(sbuf)-1){
				*p = '\0';
				execerror("name too long", sbuf);
			}
			*p++=c;
		} while ((c=getc(fin))!=EOF&&(isalnum(c)||c=='_'));
		ungetc(c,fin);
		*p='\0';
		if((s=lookup(sbuf))==0)
			s=install(sbuf,UNDEF,0.0);
		yylval.sym=s;
		nlstate=0;return s->type==UNDEF?VAR:s->type;
	}
	if(c=='$'){
		int n=0;
		c=getc(fin);
		if(c=='#'){
			nlstate=0;return ARGCNT;
		} else ungetc(c,fin);
		while (isdigit(c=getc(fin)))
			n=10*n+c-'0';
		ungetc(c,fin);
		/* $0 is invalid. also, if n is large enough it may even
		   become negative (since n is a twos-complement integer),
		   and that is invalid too.
		*/
		if (n<=0)
			execerror("strange $...",(char *)0);
		yylval.narg=n;
		nlstate=0;return ARG;
	}
	if(c=='"'){
		char sbuf[100],*p;
		for(p=sbuf;(c=getc(fin)) != '"'; p++){
			if(c=='\n'||c==EOF)
				execerror("missing quote", (char *)0);
			if(p>=sbuf+sizeof(sbuf)-1){
				*p='\0';
				execerror("string too long", sbuf);
			}
			*p=backslash(c);
		}
		*p=0;
		yylval.sym=(Symbol *)emalloc(strlen(sbuf)+1);
		strcpy((char*)yylval.sym,sbuf);
		nlstate=0;return STRING;
	}
	switch(c){
	case '>':	nlstate=0;
			switch(c=getc(fin)){
			case '=':
				return GE;
			case EOF:
				return GT;
			default:
				ungetc(c,fin);
				return GT;
			}
	case '<':	nlstate=0;
			switch(c=getc(fin)){
			case '=':
				return LE;
			case EOF:
				return LT;
			default:
				ungetc(c,fin);
				return LT;
			}
	case '=':	nlstate=0;
			switch(c=getc(fin)){
			case '=':
				return EQ;
			case EOF:
				return '=';
			default:
				ungetc(c,fin);
				return '=';
			}
	case '!':	nlstate=0;
			switch(c=getc(fin)){
			case '=':
				return NE;
			case '~':
				return NOTAPPROXEQ;
			case EOF:
				return NOT;
			default:
				ungetc(c,fin);
				return NOT;
			}
	case '|':	nlstate=0;
			switch(c=getc(fin)){
			case '|':
				return OR;
			case EOF:
				return '|';
			default:
				ungetc(c,fin);
				return '|';
			}
	case '&':	nlstate=0;
			switch(c=getc(fin)){
			case '&':
				return AND;
			case EOF:
				return '&';
			default:
				ungetc(c,fin);
				return '&';
			}
	case '+':	nlstate=0;
			switch(c=getc(fin)){
			case '+':
				return INCR;
			case '=':
				return ADDEQ;
			case EOF:
				return '+';
			default:
				ungetc(c,fin);
				return '+';
			}
	case '-':	nlstate=0;
			switch(c=getc(fin)){
			case '-':
				return DECR;
			case '=':
				return SUBEQ;
			case EOF:
				return '-';
			default:
				ungetc(c,fin);
				return '-';
			}
	case '*':	nlstate=0;
			switch(c=getc(fin)){
			case '=':
				return MULEQ;
			case EOF:
				return '*';
			default:
				ungetc(c,fin);
				return '*';
			}
	case '/':	nlstate=0;
			switch(c=getc(fin)){
			case '=':
				return DIVEQ;
			case EOF:
				return '/';
			default:
				ungetc(c,fin);
				return '/';
			}
	case '^':	nlstate=0;
			switch(c=getc(fin)){
			case '=':
				return POWEQ;
			case EOF:
				return '^';
			default:
				ungetc(c,fin);
				return '^';
			}
	case '~':	nlstate=0;
			switch(c=getc(fin)){
			case '~':
				return APPROXEQ;
			case EOF:
				return '~';
			default:
				ungetc(c,fin);
				return '~';
			}
	case '%':	nlstate=0;
			switch(c=getc(fin)){
			case '=':
				return REMEQ;
			case EOF:
				return '%';
			default:
				ungetc(c,fin);
				return '%';
			}
	case '\n':	nlstate=1;lineno++;return '\n';
	default:	nlstate=0;return c;
	}
}
static int
backslash(c)
	int c;
{
	static char transtab[]="b\bf\fn\nr\rt\t";
	if(c!='\\')
		return c;
	c=getc(fin);
	if(c>='0' && c<='7'){
		int tmp;
		ungetc(c,fin);
		fscanf(fin,"%3o",&tmp);
		return tmp;
	}
	if(islower(c)&&strchr(transtab,c))
		return strchr(transtab,c)[1];
	return c;
}

static void
defnonly(s)
	char *s;
{
	if(!indef)
		execerror(s,"used outside definition");
}

static void
#ifdef RESEARCH
yyerror(s,t)
	char *s, *t;
#else
yyerror(s)
	char *s;
#endif
{
	initcode();
	*progbase=STOP;
#ifndef RESEARCH
	warning(s,(char *)0);
#else
	fprintf(stderr,"%s: ",progname);
	if(infile)
		fprintf(stderr, "%s: ", infile);
	fprintf(stderr, "%d: ", lineno);
	fprintf(stderr,s,t);
#endif
}
void
execerror(s,t)
	char *s,*t;
{
	Frame *efp;
	for(efp=fp;efp>frame;efp--){
		if(efp->locals){
			/* free all local variables of current function */
			/* same code as in ret() */
			Local *tmp=efp->locals, *tmp1;
			while(tmp1=tmp){
				tmp=tmp1->nextlocal;
				if(!tmp1->nextdef->nextdef){
					/* next one is global/undef */
					tmp1->real->u.val=
						tmp1->nextdef->val;
					tmp1->real->type=
						tmp1->nextdef->p.type;
					FREELOCAL(tmp1->nextdef);
					FREELOCAL(tmp1);
					continue;
				}
				tmp1->real->u.localptr=tmp1->nextdef;
				FREELOCAL(tmp1);
			}
		}
	}
	if(s){	/* regular call */
		warning(s,t);
	} else { /* call by 'eof' */
		endfile=1;
	}
	fseek(fin,0L,2);
#ifdef HAVE_SIGLONGJMP
	siglongjmp(begin, 0);
#else
	longjmp(begin,0);
#endif

}
/* Signal handlers. RETSIGTYPE, defined by configure, is usually void. */
/* Actually, the signal handler normally has an integer parameter, but
   we ignore it.
*/
static RETSIGTYPE
fpecatch(sig)
{
	execerror("floating point exception",(char *)0);
}

static RETSIGTYPE
intcatch(sig)
{
	execerror("interruped",(char *)0);
}
	
int
main(argc,argv)
	char *argv[];
{
#ifdef ALWAYSPRVER
	/* If ALWAYSPRVER, we show the version information every time hoc
	   runs. If it is not defined (the default), we show version
	   information only in interactive hoc sessions.
	*/
	versioninfo();
#endif
	progname=argv[0];
	if(argc==1){
		static char *stdinonly[]={ "-" };

		gargv=stdinonly;
		gargc=1;
	} else {
		gargv=argv+1;
		gargc=argc-1;
	}
	init();
	while(moreinput())
		run();
	/*nalloc_memory_show_fp(stdout);*/
	exit(0);
}
static int
moreinput()
{
MOREINPUT:
	if(gargc--<=0)
		return 0;
	if(fin&&fin!=stdin)
		fclose(fin);
	infile= *gargv++;
	lineno=1;
	interactive=0;
	if(strcmp(infile,"-")==0){
		fin=stdin;
		infile=0;
		/* this is an interactive hoc if we're taking input from
		   stdin, and stdin is connected to a terminal
		*/
		interactive=isatty(fileno(fin));
#ifndef ALWAYSPRVER
		if(interactive) versioninfo();
#endif
		return 1;
	}
	if(infile[0]=='-'&&infile[1]=='l'){
		char *tmp;
#ifdef NOLIBS
		fprintf(stderr,"%s: libraries not available on this system\n",progname);
		goto MOREINPUT;
#else
#ifndef LIBPREFIX
#define LIBPREFIX "/usr/lib/hoclibs/LIB"
#endif
		tmp=malloc(strlen(infile+2)+strlen(LIBPREFIX)+1);
		tmp[0]='\0';
		strcat(tmp,LIBPREFIX);
		strcat(tmp,infile+2);
		infile=tmp;
#endif
	}
	if((fin=fopen(infile,"r"))==NULL){
		fprintf(stderr,"%s: can't open %s\n",progname,infile);
		goto MOREINPUT;
	}
	return 1;
}
void
run()
{
#ifdef HAVE_SIGLONGJMP
	/* In some new systems (like Linux), calling longjmp() from a signal
	   handler (like we do, in fpecatch and intcatch) has a problem: it
	   leaves the caught signal blocked, like it was inside the signal
	   handler! sigsetjmp() and siglongjmp() solve this problem, by also
	   saving and restoring the signal mask.
	*/
	sigsetjmp(begin,1);
#else
	setjmp(begin);
#endif
	if(endfile){	/* if 'eof' was called */
		endfile=0;
		return;
	}
	nlstate=1;
	signal(SIGFPE,fpecatch);
	signal(SIGINT,intcatch);
	for(initcode();yyparse();initcode())
		execute(progbase);
}
void
warning(s,t)
	char *s,*t;
{
	fprintf(stderr,"%s: %s",progname,s);
	if(t)
		fprintf(stderr, " %s",t);
	if(infile)
		fprintf(stderr, " in %s", infile);
	fprintf(stderr, " near line %d\n", lineno);
}

static int
skipc()
{
	/* this function RECURSIVELY skips all characters until a * / is matched */
	char z; /* current character read */
	while(1){
		z=getc(fin);
		if((z=='/')&&(lookahead()=='*')){
			/* recursive skipping of imbedded comments*/
			getc(fin); /* throw out the * */
			if(!skipc())
				return 0;
			continue;
		}
		if((z=='*')&&(lookahead()=='/')){ /* end of comment */
			z=getc(fin); /* throw out the /  */
			return 1;
		}
		if (z=='\n')
			++lineno;
		if (z==EOF)
			return 0;
	}
}
static char
lookahead()
{
	int z;
	z=getc(fin);
	if(z==EOF)
		return 0;
	ungetc(z,fin);
	return((char)z);
}

/* versioninfo() shows version information suitable to be displayed when
   hoc starts running.
   Above, if ALWAYSPRVER, we show the version information every time hoc
   runs. If it is not defined (which is the default), we show version
   information only in interactive hoc sessions.
*/
void versioninfo(){
	fprintf(stderr,"Welcome to the NYH HOC interpreter.\n");
	fprintf(stderr,"By Brian Kernighan and Rob Pike 1984, Nadav Har'El 1986-1997.\n\n");
/*	fprintf(stderr,"%s, %s.\n\n",
  version_array[0]+4,version_array[1]+4);*/
}
