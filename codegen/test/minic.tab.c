/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     NUM = 258,
     ID = 259,
     VOID = 260,
     INT = 261,
     COMMA = 262,
     SEMICOLON = 263,
     LPAREN = 264,
     RPAREN = 265,
     LBRACKET = 266,
     RBRACKET = 267,
     LBRACE = 268,
     RBRACE = 269,
     IF = 270,
     ELSE = 271,
     WHILE = 272,
     FOR = 273,
     ASSIGN = 274,
     RETURN = 275,
     ADD = 276,
     SUB = 277,
     MULT = 278,
     DIV = 279,
     LESS = 280,
     LESSEQUAL = 281,
     GREAT = 282,
     GREATEQUAL = 283,
     EQUAL = 284,
     NOTEQUAL = 285,
     UMINUS = 286
   };
#endif
/* Tokens.  */
#define NUM 258
#define ID 259
#define VOID 260
#define INT 261
#define COMMA 262
#define SEMICOLON 263
#define LPAREN 264
#define RPAREN 265
#define LBRACKET 266
#define RBRACKET 267
#define LBRACE 268
#define RBRACE 269
#define IF 270
#define ELSE 271
#define WHILE 272
#define FOR 273
#define ASSIGN 274
#define RETURN 275
#define ADD 276
#define SUB 277
#define MULT 278
#define DIV 279
#define LESS 280
#define LESSEQUAL 281
#define GREAT 282
#define GREATEQUAL 283
#define EQUAL 284
#define NOTEQUAL 285
#define UMINUS 286




/* Copy the first part of user declarations.  */
#line 1 "minic.y"

#include "ast.h"
#include "global.h"
#include <stdio.h>
extern char *yytext;
A_program program;
void print(int, char*);
int yylex(void);
void yyerror(char *s)
{
	printf("%s near line %d\n", s, linenumber);
}


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 14 "minic.y"
{
	char*			str;
	int				num;
	A_program		program;
	A_declarationlist	declarationlist;
	A_declaration		declaration;
	A_vardeclaration	vardeclaration;
	A_typespecifier		typespecifier;
	A_fundeclaration	fundeclaration;
	A_params		params;
	A_paramlist		paramlist;
	A_param			param;
	A_compoundstmt		compoundstmt;
	A_localdeclarations	localdeclarations;
	A_statementlist		statementlist;
	A_statement		statement;
	A_expressionstmt	expressionstmt;
	A_selectionstmt		selectionstmt;
	A_iterationstmt		iterationstmt;
	A_returnstmt		returnstmt;
	A_expression		expression;
	A_var			var;
	A_simpleexpression	simpleexpression;
	int			relop;
	A_additiveexpression	additiveexpression;
	int			addop;
	A_term			term;
	int			mulop;
	A_factor		factor;
	A_call			call;
	A_args			args;
	A_arglist		arglist;
}
/* Line 187 of yacc.c.  */
#line 206 "minic.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 219 "minic.tab.c"

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
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
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
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  9
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   123

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  32
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  30
/* YYNRULES -- Number of rules.  */
#define YYNRULES  66
/* YYNRULES -- Number of states.  */
#define YYNSTATES  113

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   286

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
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
      25,    26,    27,    28,    29,    30,    31
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     8,    10,    12,    14,    18,    25,
      27,    29,    36,    38,    40,    44,    46,    49,    54,    55,
      60,    63,    64,    67,    68,    70,    72,    74,    76,    78,
      81,    83,    89,    97,   103,   113,   116,   120,   124,   126,
     128,   133,   137,   139,   141,   143,   145,   147,   149,   151,
     155,   157,   159,   161,   165,   167,   170,   172,   174,   178,
     180,   182,   184,   189,   191,   192,   196
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      33,     0,    -1,    34,    -1,    34,    35,    -1,    35,    -1,
      36,    -1,    38,    -1,    37,     4,     8,    -1,    37,     4,
      11,     3,    12,     8,    -1,     6,    -1,     5,    -1,    37,
       4,     9,    39,    10,    42,    -1,    40,    -1,     5,    -1,
      40,     7,    41,    -1,    41,    -1,    37,     4,    -1,    37,
       4,    11,    12,    -1,    -1,    13,    43,    44,    14,    -1,
      43,    36,    -1,    -1,    44,    45,    -1,    -1,    46,    -1,
      42,    -1,    47,    -1,    48,    -1,    49,    -1,    50,     8,
      -1,     8,    -1,    15,     9,    50,    10,    45,    -1,    15,
       9,    50,    10,    45,    16,    45,    -1,    17,     9,    50,
      10,    45,    -1,    18,     9,    50,     8,    50,     8,    50,
      10,    45,    -1,    20,     8,    -1,    20,    50,     8,    -1,
      51,    19,    50,    -1,    52,    -1,     4,    -1,     4,    11,
      50,    12,    -1,    54,    53,    54,    -1,    54,    -1,    26,
      -1,    25,    -1,    27,    -1,    28,    -1,    29,    -1,    30,
      -1,    54,    55,    56,    -1,    56,    -1,    21,    -1,    22,
      -1,    56,    57,    58,    -1,    58,    -1,    22,    58,    -1,
      23,    -1,    24,    -1,     9,    50,    10,    -1,    51,    -1,
      59,    -1,     3,    -1,     4,     9,    60,    10,    -1,    61,
      -1,    -1,    61,     7,    50,    -1,    50,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    87,    87,    91,    93,    97,    99,   103,   105,   109,
     111,   115,   119,   121,   125,   127,   131,   133,   136,   139,
     143,   146,   149,   152,   155,   157,   159,   161,   163,   167,
     169,   173,   175,   179,   181,   185,   187,   191,   193,   197,
     199,   203,   205,   209,   211,   213,   215,   217,   219,   223,
     225,   229,   231,   235,   237,   239,   243,   245,   249,   251,
     253,   255,   259,   263,   266,   269,   271
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NUM", "ID", "VOID", "INT", "COMMA",
  "SEMICOLON", "LPAREN", "RPAREN", "LBRACKET", "RBRACKET", "LBRACE",
  "RBRACE", "IF", "ELSE", "WHILE", "FOR", "ASSIGN", "RETURN", "ADD", "SUB",
  "MULT", "DIV", "LESS", "LESSEQUAL", "GREAT", "GREATEQUAL", "EQUAL",
  "NOTEQUAL", "UMINUS", "$accept", "program", "declarationlist",
  "declaration", "vardeclaration", "typespecifier", "fundeclaration",
  "params", "paramlist", "param", "compoundstmt", "localdeclarations",
  "statementlist", "statement", "expressionstmt", "selectionstmt",
  "iterationstmt", "returnstmt", "expression", "var", "simpleexpression",
  "relop", "additiveexpression", "addop", "term", "mulop", "factor",
  "call", "args", "arglist", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    32,    33,    34,    34,    35,    35,    36,    36,    37,
      37,    38,    39,    39,    40,    40,    41,    41,    41,    42,
      43,    43,    44,    44,    45,    45,    45,    45,    45,    46,
      46,    47,    47,    48,    48,    49,    49,    50,    50,    51,
      51,    52,    52,    53,    53,    53,    53,    53,    53,    54,
      54,    55,    55,    56,    56,    56,    57,    57,    58,    58,
      58,    58,    59,    60,    60,    61,    61
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     3,     6,     1,
       1,     6,     1,     1,     3,     1,     2,     4,     0,     4,
       2,     0,     2,     0,     1,     1,     1,     1,     1,     2,
       1,     5,     7,     5,     9,     2,     3,     3,     1,     1,
       4,     3,     1,     1,     1,     1,     1,     1,     1,     3,
       1,     1,     1,     3,     1,     2,     1,     1,     3,     1,
       1,     1,     4,     1,     0,     3,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    10,     9,     0,     2,     4,     5,     0,     6,     1,
       3,     0,     7,    18,     0,    10,     0,     0,    12,    15,
       0,    16,     0,    18,     0,     0,    21,    11,    14,     8,
      17,    23,    20,     0,     0,     0,    61,    39,    30,     0,
      19,     0,     0,     0,     0,     0,    25,    22,    24,    26,
      27,    28,     0,    59,    38,    42,    50,    54,    60,    64,
       0,     0,     0,     0,     0,    35,     0,    59,    55,    29,
       0,    51,    52,    44,    43,    45,    46,    47,    48,     0,
       0,    56,    57,     0,    66,     0,    63,     0,    58,     0,
       0,     0,    36,    37,    41,    49,    53,    62,     0,    40,
       0,     0,     0,    65,    31,    33,     0,     0,     0,    32,
       0,     0,    34
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     3,     4,     5,     6,     7,     8,    17,    18,    19,
      46,    31,    34,    47,    48,    49,    50,    51,    52,    53,
      54,    79,    55,    80,    56,    83,    57,    58,    85,    86
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -95
static const yytype_int8 yypact[] =
{
      13,   -95,   -95,    14,    13,   -95,   -95,    22,   -95,   -95,
     -95,    19,   -95,    73,    31,    35,    37,    45,    58,   -95,
      48,    56,    61,    13,    82,    79,   -95,   -95,   -95,   -95,
     -95,    13,   -95,    88,    29,     4,   -95,    39,   -95,     7,
     -95,    84,    85,    86,     0,    49,   -95,   -95,   -95,   -95,
     -95,   -95,    89,    77,   -95,    55,    63,   -95,   -95,     7,
       7,    90,     7,     7,     7,   -95,    91,   -95,   -95,   -95,
       7,   -95,   -95,   -95,   -95,   -95,   -95,   -95,   -95,     7,
       7,   -95,   -95,    49,   -95,    92,    94,    93,   -95,    96,
      97,    95,   -95,   -95,    67,    63,   -95,   -95,     7,   -95,
      53,    53,     7,   -95,    98,   -95,   100,    53,     7,   -95,
      99,    53,   -95
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -95,   -95,   -95,   106,    80,    41,   -95,   -95,   -95,    75,
     101,   -95,   -95,   -94,   -95,   -95,   -95,   -95,   -39,   -44,
     -95,   -95,    25,   -95,    32,   -95,   -43,   -95,   -95,   -95
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -14
static const yytype_int8 yytable[] =
{
      61,    67,    68,    36,    37,    66,   104,   105,    65,    39,
      36,    37,    12,   109,     9,    14,    39,   112,     1,     2,
      84,    87,    45,    89,    90,    91,    11,    12,    13,    45,
      14,    93,    36,    37,    20,    67,    67,    38,    39,    67,
      96,    21,    26,    40,    41,   -13,    42,    43,    59,    44,
      60,    45,    36,    37,    16,    22,    36,    37,    39,   103,
      24,    38,    39,   106,    16,    23,    26,    25,    41,   110,
      42,    43,    33,    44,    26,    45,    71,    72,    15,     2,
      73,    74,    75,    76,    77,    78,    81,    82,    71,    72,
      29,    30,    35,    62,    63,    64,    70,    69,    28,    92,
      88,    98,    97,   102,    94,    99,   100,   101,   108,   111,
      10,    32,    95,     0,   107,     0,     0,     0,     0,     0,
       0,     0,     0,    27
};

static const yytype_int8 yycheck[] =
{
      39,    45,    45,     3,     4,    44,   100,   101,     8,     9,
       3,     4,     8,   107,     0,    11,     9,   111,     5,     6,
      59,    60,    22,    62,    63,    64,     4,     8,     9,    22,
      11,    70,     3,     4,     3,    79,    80,     8,     9,    83,
      83,     4,    13,    14,    15,    10,    17,    18,     9,    20,
      11,    22,     3,     4,    13,    10,     3,     4,     9,    98,
      12,     8,     9,   102,    23,     7,    13,    11,    15,   108,
      17,    18,    31,    20,    13,    22,    21,    22,     5,     6,
      25,    26,    27,    28,    29,    30,    23,    24,    21,    22,
       8,    12,     4,     9,     9,     9,    19,     8,    23,     8,
      10,     7,    10,     8,    79,    12,    10,    10,     8,    10,
       4,    31,    80,    -1,    16,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    22
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     5,     6,    33,    34,    35,    36,    37,    38,     0,
      35,     4,     8,     9,    11,     5,    37,    39,    40,    41,
       3,     4,    10,     7,    12,    11,    13,    42,    41,     8,
      12,    43,    36,    37,    44,     4,     3,     4,     8,     9,
      14,    15,    17,    18,    20,    22,    42,    45,    46,    47,
      48,    49,    50,    51,    52,    54,    56,    58,    59,     9,
      11,    50,     9,     9,     9,     8,    50,    51,    58,     8,
      19,    21,    22,    25,    26,    27,    28,    29,    30,    53,
      55,    23,    24,    57,    50,    60,    61,    50,    10,    50,
      50,    50,     8,    50,    54,    56,    58,    10,     7,    12,
      10,    10,     8,    50,    45,    45,    50,    16,     8,    45,
      50,    10,    45
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

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
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

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

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

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
     `$$ = $1'.

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
#line 88 "minic.y"
    { (yyval.program) = F_declarationlist2program((yyvsp[(1) - (1)].declarationlist)); program = (yyval.program);;}
    break;

  case 3:
#line 92 "minic.y"
    { (yyval.declarationlist) = F_declarationlist2declarationlist((yyvsp[(1) - (2)].declarationlist), (yyvsp[(2) - (2)].declaration));;}
    break;

  case 4:
#line 94 "minic.y"
    { (yyval.declarationlist) = F_declaration2declarationlist((yyvsp[(1) - (1)].declaration));;}
    break;

  case 5:
#line 98 "minic.y"
    { (yyval.declaration)= F_vardeclaration2declaration((yyvsp[(1) - (1)].vardeclaration));;}
    break;

  case 6:
#line 100 "minic.y"
    { (yyval.declaration) = F_fundeclaration2declaration((yyvsp[(1) - (1)].fundeclaration));;}
    break;

  case 7:
#line 104 "minic.y"
    { (yyval.vardeclaration) = F_typespecifier2vardeclaration((yyvsp[(1) - (3)].typespecifier), (yyvsp[(2) - (3)].str));;}
    break;

  case 8:
#line 106 "minic.y"
    { (yyval.vardeclaration) = F_typespecifierNUM2vardeclaration((yyvsp[(1) - (6)].typespecifier), (yyvsp[(2) - (6)].str), (yyvsp[(4) - (6)].num));;}
    break;

  case 9:
#line 110 "minic.y"
    { (yyval.typespecifier) = F_typespecifier("int", INT);;}
    break;

  case 10:
#line 112 "minic.y"
    { (yyval.typespecifier) = F_typespecifier("void", VOID);;}
    break;

  case 11:
#line 116 "minic.y"
    { (yyval.fundeclaration) = F_typespecifier2fundeclaration((yyvsp[(1) - (6)].typespecifier), (yyvsp[(2) - (6)].str), (yyvsp[(4) - (6)].params), (yyvsp[(6) - (6)].compoundstmt));;}
    break;

  case 12:
#line 120 "minic.y"
    { (yyval.params) = F_paramlist2params((yyvsp[(1) - (1)].paramlist));;}
    break;

  case 13:
#line 122 "minic.y"
    { (yyval.params) = F_void2params();;}
    break;

  case 14:
#line 126 "minic.y"
    { (yyval.paramlist) = F_paramlist2paramlist((yyvsp[(1) - (3)].paramlist), (yyvsp[(3) - (3)].param));;}
    break;

  case 15:
#line 128 "minic.y"
    { (yyval.paramlist) = F_param2paramlist((yyvsp[(1) - (1)].param));;}
    break;

  case 16:
#line 132 "minic.y"
    { (yyval.param) = F_typespecifier2param((yyvsp[(1) - (2)].typespecifier), (yyvsp[(2) - (2)].str));;}
    break;

  case 17:
#line 134 "minic.y"
    { (yyval.param) = F_typespecifierArray2param((yyvsp[(1) - (4)].typespecifier), (yyvsp[(2) - (4)].str));;}
    break;

  case 18:
#line 136 "minic.y"
    { (yyval.param) = F_null2param();;}
    break;

  case 19:
#line 140 "minic.y"
    { (yyval.compoundstmt) = F_localdeclarations2compoundstmt((yyvsp[(2) - (4)].localdeclarations), (yyvsp[(3) - (4)].statementlist));;}
    break;

  case 20:
#line 144 "minic.y"
    { (yyval.localdeclarations) = F_localdeclarations2localdeclarations((yyvsp[(1) - (2)].localdeclarations), (yyvsp[(2) - (2)].vardeclaration));;}
    break;

  case 21:
#line 146 "minic.y"
    { (yyval.localdeclarations) = F_null2localdeclaration();;}
    break;

  case 22:
#line 150 "minic.y"
    { (yyval.statementlist) = F_statementlist2statementlist((yyvsp[(1) - (2)].statementlist), (yyvsp[(2) - (2)].statement));;}
    break;

  case 23:
#line 152 "minic.y"
    { (yyval.statementlist) = F_null2statementlist();;}
    break;

  case 24:
#line 156 "minic.y"
    { (yyval.statement) = F_expressionstmt2statement((yyvsp[(1) - (1)].expressionstmt));;}
    break;

  case 25:
#line 158 "minic.y"
    { (yyval.statement) = F_compoundstmt2statement((yyvsp[(1) - (1)].compoundstmt));;}
    break;

  case 26:
#line 160 "minic.y"
    { (yyval.statement) = F_selectionstmt2statement((yyvsp[(1) - (1)].selectionstmt));;}
    break;

  case 27:
#line 162 "minic.y"
    { (yyval.statement) = F_iterationstmt2statement((yyvsp[(1) - (1)].iterationstmt));;}
    break;

  case 28:
#line 164 "minic.y"
    { (yyval.statement) = F_returnstmt2statement((yyvsp[(1) - (1)].returnstmt));;}
    break;

  case 29:
#line 168 "minic.y"
    { (yyval.expressionstmt) = F_expression2expressionstmt((yyvsp[(1) - (2)].expression));;}
    break;

  case 30:
#line 170 "minic.y"
    { (yyval.expressionstmt) = F_null2expressionstmt();;}
    break;

  case 31:
#line 174 "minic.y"
    { (yyval.selectionstmt) = F_if2selectionstmt((yyvsp[(3) - (5)].expression), (yyvsp[(5) - (5)].statement));;}
    break;

  case 32:
#line 176 "minic.y"
    { (yyval.selectionstmt) = F_ifelse2selectionstmt((yyvsp[(3) - (7)].expression), (yyvsp[(5) - (7)].statement), (yyvsp[(7) - (7)].statement));;}
    break;

  case 33:
#line 180 "minic.y"
    { (yyval.iterationstmt) = F_while2iterationstmt((yyvsp[(3) - (5)].expression), (yyvsp[(5) - (5)].statement));;}
    break;

  case 34:
#line 182 "minic.y"
    { (yyval.iterationstmt) = F_for2iterationstmt((yyvsp[(3) - (9)].expression), (yyvsp[(5) - (9)].expression), (yyvsp[(7) - (9)].expression), (yyvsp[(9) - (9)].statement));;}
    break;

  case 35:
#line 186 "minic.y"
    { (yyval.returnstmt) = F_null2returnstmt();;}
    break;

  case 36:
#line 188 "minic.y"
    { (yyval.returnstmt) = F_expression2returnstmt((yyvsp[(2) - (3)].expression));;}
    break;

  case 37:
#line 192 "minic.y"
    { (yyval.expression) = F_var2expression((yyvsp[(1) - (3)].var), (yyvsp[(3) - (3)].expression));;}
    break;

  case 38:
#line 194 "minic.y"
    { (yyval.expression) = F_simpleexpression2expression((yyvsp[(1) - (1)].simpleexpression));;}
    break;

  case 39:
#line 198 "minic.y"
    { (yyval.var) = F_id2var((yyvsp[(1) - (1)].str));;}
    break;

  case 40:
#line 200 "minic.y"
    { (yyval.var) = F_array2var((yyvsp[(1) - (4)].str), (yyvsp[(3) - (4)].expression));;}
    break;

  case 41:
#line 204 "minic.y"
    { (yyval.simpleexpression) = F_additiveexpressionrelop2simpleexpression((yyvsp[(1) - (3)].additiveexpression), (yyvsp[(2) - (3)].relop), (yyvsp[(3) - (3)].additiveexpression));;}
    break;

  case 42:
#line 206 "minic.y"
    { (yyval.simpleexpression) = F_additiveexpression2simpleexpression((yyvsp[(1) - (1)].additiveexpression));;}
    break;

  case 43:
#line 210 "minic.y"
    { (yyval.relop) = LESSEQUAL;;}
    break;

  case 44:
#line 212 "minic.y"
    { (yyval.relop) = LESS;;}
    break;

  case 45:
#line 214 "minic.y"
    { (yyval.relop) = GREAT;;}
    break;

  case 46:
#line 216 "minic.y"
    { (yyval.relop) = GREATEQUAL;;}
    break;

  case 47:
#line 218 "minic.y"
    { (yyval.relop) = EQUAL;;}
    break;

  case 48:
#line 220 "minic.y"
    { (yyval.relop) = NOTEQUAL;;}
    break;

  case 49:
#line 224 "minic.y"
    { (yyval.additiveexpression) = F_additiveexpression2additiveexpression((yyvsp[(1) - (3)].additiveexpression), (yyvsp[(2) - (3)].relop), (yyvsp[(3) - (3)].term));;}
    break;

  case 50:
#line 226 "minic.y"
    { (yyval.additiveexpression) = F_term2additiveexpression((yyvsp[(1) - (1)].term));;}
    break;

  case 51:
#line 230 "minic.y"
    { (yyval.relop) = ADD;;}
    break;

  case 52:
#line 232 "minic.y"
    { (yyval.relop) = SUB;;}
    break;

  case 53:
#line 236 "minic.y"
    { (yyval.term) = F_term2term((yyvsp[(1) - (3)].term), (yyvsp[(2) - (3)].mulop), (yyvsp[(3) - (3)].factor));;}
    break;

  case 54:
#line 238 "minic.y"
    { (yyval.term) = F_factor2term((yyvsp[(1) - (1)].factor));;}
    break;

  case 55:
#line 240 "minic.y"
    { (yyval.term) = F_uminus2term((yyvsp[(2) - (2)].factor));;}
    break;

  case 56:
#line 244 "minic.y"
    { (yyval.mulop) = MULT;;}
    break;

  case 57:
#line 246 "minic.y"
    { (yyval.mulop) = DIV;;}
    break;

  case 58:
#line 250 "minic.y"
    { (yyval.factor) = F_expression2factor((yyvsp[(2) - (3)].expression));;}
    break;

  case 59:
#line 252 "minic.y"
    { (yyval.factor) = F_var2factor((yyvsp[(1) - (1)].var));;}
    break;

  case 60:
#line 254 "minic.y"
    { (yyval.factor) = F_call2factor((yyvsp[(1) - (1)].call));;}
    break;

  case 61:
#line 256 "minic.y"
    { (yyval.factor) = F_num2factor((yyvsp[(1) - (1)].num));;}
    break;

  case 62:
#line 260 "minic.y"
    { (yyval.call) = F_id2call((yyvsp[(1) - (4)].str), (yyvsp[(3) - (4)].args)); ;}
    break;

  case 63:
#line 264 "minic.y"
    { (yyval.args) = F_arglist2args((yyvsp[(1) - (1)].arglist));;}
    break;

  case 64:
#line 266 "minic.y"
    { (yyval.args) = F_null2args();;}
    break;

  case 65:
#line 270 "minic.y"
    { (yyval.arglist) = F_arglist2arglist((yyvsp[(1) - (3)].arglist), (yyvsp[(3) - (3)].expression));;}
    break;

  case 66:
#line 272 "minic.y"
    { (yyval.arglist) = F_expression2arglist((yyvsp[(1) - (1)].expression));;}
    break;


/* Line 1267 of yacc.c.  */
#line 1842 "minic.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
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

  /* Else will try to reuse look-ahead token after shifting the error
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

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
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

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


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

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 274 "minic.y"

int main()
{
	linenumber = 1;
	yyparse();
	//S_program(program);
	return 0;
}

void print(int rulenumber, char *s)
{
	printf("rulenumber %d : %s\n", rulenumber, s);
}

