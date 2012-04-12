
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 1



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 12 "parser.y"

#ifdef _WIN32
#pragma warning( disable : 4065 )
#endif
#include "aux_data.h"
#include "context.h"
#include <math.h>
#include <assert.h>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <type_checker.h>
        using std::vector;
        using std::tr1::shared_ptr;
        using std::string;
        int yylex (void);
        void yyerror (char const *s);

#define YYDEBUG 0
#define PRINT_ERROR(...) fprintf (stderr, __VA_ARGS__)
#if YYDEBUG
#define PRINT_DEBUG(...) printf (__VA_ARGS__)
#else
#define PRINT_DEBUG(...)
#endif
        extern t_info *g_info;
        extern string  ouput_src;
        extern bool    is_predef;

#define SAFE_DELETE(P) {if(P !=NULL) {delete P; P = NULL;}}

        

/* Line 189 of yacc.c  */
#line 108 "D:/nprojects/safegi/base/libs/sparser/parser.cpp"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
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


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     T_GE = 258,
     T_LE = 259,
     T_EQ = 260,
     UMINUS = 261,
     T_VARY = 262,
     T_UNIF = 263,
     T_ATTR = 264,
     T_ID = 265,
     T_LT_INT = 266,
     T_LT_FLT = 267,
     T_LT_BLN = 268,
     T_IF = 269,
     T_ELSE = 270,
     T_ELSE_IF = 271,
     T_FOR = 272,
     T_WHILE = 273,
     T_DO = 274,
     T_RETURN = 275,
     T_IN = 276,
     T_OUT = 277,
     T_INOUT = 278,
     T_DEFINE = 279,
     T_TYPEMAP = 280,
     T_DEF_SPACE_ANO = 281,
     T_DEF_DIM_ANO = 282,
     T_OPERATOR = 283,
     T_VEC = 284,
     T_IVEC = 285,
     T_BVEC = 286,
     T_UVEC = 287,
     T_VOID = 288,
     T_INT = 289,
     T_FLOAT = 290,
     T_BOOL = 291,
     T_UINT = 292,
     T_MAT4 = 293,
     T_SAMPLER2D_TYPE = 294,
     T_GENERIC_SPACE_NOTATION = 295,
     T_GENERIC_DIMEN_NOTATION = 296,
     T_RESERVED = 297,
     T_SPACE_ANO = 298,
     T_DIMEN_ANO = 299,
     T_BASIC_TYPE = 300,
     T_BUILT_IN = 301,
     T_CONVERNTION = 302,
     T_RAW_CODE = 303,
     T_BUILT_IN_SIG = 304,
     T_TEXTURE2D = 305
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 86 "parser.y"

    string*                     str;
    t_space_ano*                space_ano;
    t_dim_ano*                  dimen_ano;
    cx_generic_ano_type*        gen_ano_type;
    cx_generic_ano_para*         gen_ano_para;
    gs_generic_ano_paralist*     gen_ano_paralist;
    gs_node*                    node;
    gs_type*                    type;
    gs_id_decl*                 decl_id;
    gs_id_decl_list*            idlist;
    gs_anolist*                 anolist;
    gs_paralist*                paralist;
    gs_arglist*                 arglist;
    gs_expression*              expression;
    gs_signature_list*          sig_list;




/* Line 214 of yacc.c  */
#line 215 "D:/nprojects/safegi/base/libs/sparser/parser.cpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 240 "D:/nprojects/safegi/base/libs/sparser/parser.cpp"

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
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
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
	 || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
	     && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

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
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   469

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  66
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  48
/* YYNRULES -- Number of rules.  */
#define YYNRULES  132
/* YYNRULES -- Number of states.  */
#define YYNSTATES  342

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   305

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,    65,     2,     2,     2,     2,
      60,    61,    11,     9,    59,    10,    14,    12,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    62,
       8,     3,     7,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    63,     2,    64,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     1,     2,     4,     5,
       6,    13,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,     7,     9,    11,    13,    15,    17,
      19,    21,    23,    25,    27,    29,    31,    33,    35,    37,
      39,    41,    42,    45,    50,    57,    58,    68,    76,    85,
      96,   107,   118,   129,   143,   157,   171,   185,   187,   192,
     199,   206,   213,   219,   222,   224,   226,   230,   241,   242,
     255,   257,   261,   265,   267,   271,   278,   287,   296,   304,
     308,   312,   318,   323,   329,   337,   346,   355,   364,   365,
     366,   372,   380,   386,   390,   394,   398,   402,   406,   407,
     410,   412,   415,   419,   421,   425,   430,   435,   440,   445,
     450,   456,   458,   462,   464,   466,   470,   475,   480,   484,
     488,   492,   496,   500,   503,   510,   514,   515,   517,   521,
     523,   525,   527,   529,   531,   536,   541,   548,   553,   555,
     557,   559,   561,   563,   565,   567,   569,   571,   573,   575,
     577,   579,   581
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      67,     0,    -1,    -1,    67,    68,    -1,    98,    -1,    99,
      -1,   100,    -1,   101,    -1,   102,    -1,   103,    -1,    70,
      -1,    71,    -1,    84,    -1,    86,    -1,    90,    -1,    73,
      -1,    80,    -1,    75,    -1,    76,    -1,    74,    -1,    81,
      -1,    -1,   108,    18,    -1,    69,    59,   108,    18,    -1,
     108,    18,    60,    69,    61,    62,    -1,    -1,   108,    18,
      60,    69,    61,    72,    63,    95,    64,    -1,    55,   108,
      18,    60,    69,    61,    62,    -1,    54,   108,    18,    60,
      69,    61,    57,    56,    -1,    55,   108,    36,     9,    60,
     108,    59,   108,    61,    62,    -1,    55,   108,    36,    10,
      60,   108,    59,   108,    61,    62,    -1,    55,   108,    36,
      11,    60,   108,    59,   108,    61,    62,    -1,    55,   108,
      36,    12,    60,   108,    59,   108,    61,    62,    -1,    55,
       8,    83,     7,    77,    36,     9,    60,    78,    59,    78,
      61,    62,    -1,    55,     8,    83,     7,    77,    36,    10,
      60,    78,    59,    78,    61,    62,    -1,    55,     8,    83,
       7,    77,    36,    11,    60,    78,    59,    78,    61,    62,
      -1,    55,     8,    83,     7,    77,    36,    12,    60,    78,
      59,    78,    61,    62,    -1,    53,    -1,    53,     8,    18,
       7,    -1,    53,     8,    18,    59,    18,     7,    -1,    53,
       8,    18,    11,    18,     7,    -1,    53,     8,    18,    12,
      18,     7,    -1,    53,     8,    65,    18,     7,    -1,    77,
      18,    -1,    77,    -1,    78,    -1,    79,    59,    78,    -1,
      55,     8,    83,     7,    77,    18,    60,    79,    61,    62,
      -1,    -1,    54,    82,     8,    83,     7,    77,    18,    60,
      79,    61,    57,    56,    -1,    18,    -1,    83,    59,    18,
      -1,    34,    18,    62,    -1,    19,    -1,    85,    59,    19,
      -1,    35,    18,     8,    85,     7,    62,    -1,    35,    18,
       8,    52,    11,    52,     7,    62,    -1,    35,    18,     8,
      52,    12,    52,     7,    62,    -1,    35,    18,     8,    65,
      52,     7,    62,    -1,     8,    49,     7,    -1,     8,    48,
       7,    -1,     8,    48,    59,    48,     7,    -1,    33,    18,
     109,    62,    -1,    33,    18,    87,   109,    62,    -1,    33,
      18,   110,    63,    53,    64,    62,    -1,    33,    18,   110,
      63,    53,    87,    64,    62,    -1,    33,    18,    88,   110,
      63,   108,    64,    62,    -1,    33,    18,    89,   111,    63,
     108,    64,    62,    -1,    -1,    -1,    63,    92,    95,    93,
      64,    -1,    22,    60,    94,    61,    96,    23,    96,    -1,
      22,    60,    94,    61,    96,    -1,   105,     8,   105,    -1,
     105,     7,   105,    -1,   105,     6,   105,    -1,   105,     4,
     105,    -1,   105,     5,   105,    -1,    -1,    95,    96,    -1,
      97,    -1,   105,    62,    -1,    28,   105,    62,    -1,    91,
      -1,   108,   104,    62,    -1,    16,   108,   104,    62,    -1,
      15,   108,   104,    62,    -1,    17,   108,   104,    62,    -1,
      29,   108,   104,    62,    -1,    30,   108,   104,    62,    -1,
      32,   108,    18,   105,    62,    -1,    18,    -1,   104,     3,
     105,    -1,    18,    -1,   107,    -1,    60,   105,    61,    -1,
     108,    60,   106,    61,    -1,    18,    60,   106,    61,    -1,
     105,     3,   105,    -1,   105,     9,   105,    -1,   105,    10,
     105,    -1,   105,    11,   105,    -1,   105,    12,   105,    -1,
      10,   105,    -1,    58,    60,   105,    59,   105,    61,    -1,
     105,    14,    18,    -1,    -1,   105,    -1,   106,    59,   105,
      -1,    19,    -1,    20,    -1,    21,    -1,   113,    -1,    53,
      -1,    53,     8,    52,     7,    -1,    53,     8,    51,     7,
      -1,    53,     8,    51,    59,    51,     7,    -1,    47,     8,
     108,     7,    -1,    43,    -1,    42,    -1,    44,    -1,    45,
      -1,    37,    -1,    38,    -1,    39,    -1,    40,    -1,    46,
      -1,    47,    -1,    41,    -1,   109,    -1,   110,    -1,   111,
      -1,   112,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   163,   163,   164,   175,   176,   177,   178,   179,   180,
     181,   182,   183,   184,   185,   186,   187,   188,   189,   190,
     191,   195,   198,   206,   216,   235,   234,   262,   272,   284,
     300,   311,   327,   340,   354,   368,   382,   398,   403,   409,
     416,   423,   430,   437,   443,   450,   456,   464,   478,   477,
     497,   503,   512,   520,   527,   536,   544,   553,   562,   572,
     575,   578,   581,   592,   603,   617,   630,   645,   662,   662,
     662,   667,   674,   683,   694,   705,   716,   727,   741,   744,
     752,   756,   761,   774,   780,   795,   824,   843,   862,   881,
     901,   916,   922,   933,   948,   949,   954,   967,   982,   995,
    1014,  1033,  1052,  1071,  1077,  1099,  1123,  1126,  1133,  1142,
    1148,  1154,  1162,  1169,  1181,  1193,  1205,  1217,  1228,  1229,
    1230,  1231,  1234,  1235,  1236,  1237,  1240,  1243,  1246,  1247,
    1248,  1249,  1250
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "'='", "T_GE", "T_LE", "T_EQ", "'>'",
  "'<'", "'+'", "'-'", "'*'", "'/'", "UMINUS", "'.'", "T_VARY", "T_UNIF",
  "T_ATTR", "T_ID", "T_LT_INT", "T_LT_FLT", "T_LT_BLN", "T_IF", "T_ELSE",
  "T_ELSE_IF", "T_FOR", "T_WHILE", "T_DO", "T_RETURN", "T_IN", "T_OUT",
  "T_INOUT", "T_DEFINE", "T_TYPEMAP", "T_DEF_SPACE_ANO", "T_DEF_DIM_ANO",
  "T_OPERATOR", "T_VEC", "T_IVEC", "T_BVEC", "T_UVEC", "T_VOID", "T_INT",
  "T_FLOAT", "T_BOOL", "T_UINT", "T_MAT4", "T_SAMPLER2D_TYPE",
  "T_GENERIC_SPACE_NOTATION", "T_GENERIC_DIMEN_NOTATION", "T_RESERVED",
  "T_SPACE_ANO", "T_DIMEN_ANO", "T_BASIC_TYPE", "T_BUILT_IN",
  "T_CONVERNTION", "T_RAW_CODE", "T_BUILT_IN_SIG", "T_TEXTURE2D", "','",
  "'('", "')'", "';'", "'{'", "'}'", "'#'", "$accept", "program",
  "component", "para_list", "func_decl", "func_def", "$@1",
  "call_convention", "built_in_func", "operater_convention",
  "ano_operater_convention", "generic_ano_type", "generic_ano_para",
  "generic_ano_paralist", "ano_call_convention", "built_in_ano_func",
  "$@2", "ano_list", "def_space_ano", "def_signature_list", "def_dim_ano",
  "generic_dim_ano", "generic_space_ano", "generic_space_ano_pair",
  "typemap_decl", "block", "$@3", "$@4", "cond_expr", "statements",
  "statement", "local_decl", "uniform_decl", "varying_decl",
  "attribute_decl", "in_decl", "out_decl", "define_decl", "decl_id",
  "expr", "arg_list", "literal_num", "type", "scale_type", "tuple_type",
  "mat_type", "sampler_type", "builtin_type", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,    61,   258,   259,   260,    62,    60,    43,
      45,    42,    47,   261,    46,   262,   263,   264,   265,   266,
     267,   268,   269,   270,   271,   272,   273,   274,   275,   276,
     277,   278,   279,   280,   281,   282,   283,   284,   285,   286,
     287,   288,   289,   290,   291,   292,   293,   294,   295,   296,
     297,   298,   299,   300,   301,   302,   303,   304,   305,    44,
      40,    41,    59,   123,   125,    35
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    66,    67,    67,    68,    68,    68,    68,    68,    68,
      68,    68,    68,    68,    68,    68,    68,    68,    68,    68,
      68,    69,    69,    69,    70,    72,    71,    73,    74,    75,
      75,    75,    75,    76,    76,    76,    76,    77,    77,    77,
      77,    77,    77,    78,    78,    79,    79,    80,    82,    81,
      83,    83,    84,    85,    85,    86,    86,    86,    86,    87,
      88,    89,    90,    90,    90,    90,    90,    90,    92,    93,
      91,    91,    91,    94,    94,    94,    94,    94,    95,    95,
      96,    96,    96,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   104,   105,   105,   105,   105,   105,   105,   105,
     105,   105,   105,   105,   105,   105,   106,   106,   106,   107,
     107,   107,   108,   108,   108,   108,   108,   108,   109,   109,
     109,   109,   110,   110,   110,   110,   111,   112,   113,   113,
     113,   113,   113
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     2,     4,     6,     0,     9,     7,     8,    10,
      10,    10,    10,    13,    13,    13,    13,     1,     4,     6,
       6,     6,     5,     2,     1,     1,     3,    10,     0,    12,
       1,     3,     3,     1,     3,     6,     8,     8,     7,     3,
       3,     5,     4,     5,     7,     8,     8,     8,     0,     0,
       5,     7,     5,     3,     3,     3,     3,     3,     0,     2,
       1,     2,     3,     1,     3,     4,     4,     4,     4,     4,
       5,     1,     3,     1,     1,     3,     4,     4,     3,     3,
       3,     3,     3,     2,     6,     3,     0,     1,     3,     1,
       1,     1,     1,     1,     4,     4,     6,     4,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   122,   123,   124,   125,   128,   119,   118,   120,
     121,   126,   127,   113,    48,     0,     3,    10,    11,    15,
      19,    17,    18,    16,    20,    12,    13,    14,     4,     5,
       6,     7,     8,     9,     0,   129,   130,   131,   132,   112,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    91,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    52,
       0,     0,     0,     0,     0,     0,    50,     0,     0,     0,
      21,     0,    86,    85,    87,    88,    89,     0,    93,   109,
     110,   111,     0,     0,     0,    94,     0,     0,     0,     0,
       0,     0,    62,     0,    53,     0,     0,     0,   117,   115,
       0,   114,     0,    21,     0,     0,    21,     0,     0,     0,
       0,     0,     0,    92,   103,   106,     0,     0,     0,     0,
       0,     0,     0,     0,    90,   106,    60,     0,    59,    63,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    37,     0,    51,     0,     0,     0,     0,     0,     0,
      25,    22,   107,     0,     0,    95,    98,    99,   100,   101,
     102,   105,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    55,    54,   116,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    24,     0,     0,    97,
       0,    96,    61,     0,     0,    64,     0,     0,     0,    58,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    27,
       0,     0,     0,     0,    23,    78,   108,     0,    66,    67,
      65,    56,    57,     0,    28,    38,     0,     0,     0,     0,
      44,    45,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   104,     0,     0,     0,     0,    42,    43,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    68,    26,    83,    79,    80,     0,     0,     0,    40,
      41,    39,    46,    47,     0,     0,     0,     0,    29,    30,
      31,    32,     0,     0,    78,    81,     0,     0,     0,     0,
       0,     0,     0,     0,    82,    69,    84,    49,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    33,
      34,    35,    36,    72,    76,    77,    75,    74,    73,    70,
       0,    71
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    26,   131,    27,    28,   207,    29,    30,    31,
      32,   250,   251,   252,    33,    34,    61,    87,    35,   117,
      36,    74,    75,    76,    37,   283,   304,   328,   312,   261,
     284,   285,    38,    39,    40,    41,    42,    43,    67,   286,
     173,   105,   106,    45,    46,    47,    48,    49
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -203
static const yytype_int16 yypact[] =
{
    -203,   140,  -203,   170,   170,   170,   170,   170,   170,    36,
      39,    70,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,
    -203,  -203,    43,   107,   170,    89,  -203,  -203,  -203,  -203,
    -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,
    -203,  -203,  -203,  -203,   135,  -203,  -203,  -203,  -203,  -203,
     153,   153,   153,   153,   153,   174,   182,    96,   110,   170,
      56,   180,   215,   220,    80,   198,  -203,    -2,     5,    19,
      23,    24,   333,    75,   154,   205,   221,   138,   203,  -203,
      30,   280,    31,   283,   220,   232,  -203,    32,   233,   245,
     170,   333,  -203,  -203,  -203,  -203,  -203,   333,   239,  -203,
    -203,  -203,   240,   333,     6,  -203,   241,    33,   295,   242,
     247,   248,  -203,   250,  -203,   194,   260,    35,  -203,  -203,
     262,  -203,    46,   170,   263,   299,   170,   258,   259,   275,
     276,    82,   302,   225,   308,   333,   333,    52,   333,   333,
     333,   333,   333,   305,  -203,   333,  -203,   289,  -203,  -203,
     170,   170,    11,   286,   290,   334,   282,   327,   341,   263,
      93,   357,   101,  -203,   130,   170,   170,   170,   170,   170,
     306,  -203,   225,   187,   100,  -203,   225,   133,   133,   308,
     308,  -203,   224,   342,   303,   317,   320,   321,   318,   377,
     378,   325,  -203,  -203,  -203,   370,   332,    41,   330,   270,
     335,   336,   337,   339,   340,   374,  -203,   331,   333,  -203,
     333,  -203,  -203,   338,   343,  -203,   344,   345,   346,  -203,
     349,   347,    58,   383,   263,   350,   351,   353,   354,  -203,
     170,   170,   170,   170,  -203,  -203,   225,    90,  -203,  -203,
    -203,  -203,  -203,   263,  -203,  -203,   384,   386,   394,   408,
     398,  -203,   227,   263,   263,   263,   263,   356,   358,   359,
     360,   231,  -203,   237,   411,   415,   416,  -203,  -203,   263,
     362,   366,   367,   368,   369,   371,   372,   373,   375,   376,
     333,  -203,  -203,  -203,  -203,  -203,    22,    12,   381,  -203,
    -203,  -203,  -203,  -203,   263,   263,   263,   263,  -203,  -203,
    -203,  -203,   333,    34,  -203,  -203,    25,   385,   379,   382,
     387,   388,   389,   352,  -203,   287,  -203,  -203,   380,   390,
     391,   392,   287,   333,   333,   333,   333,   333,   365,  -203,
    -203,  -203,  -203,   407,   225,   225,   225,   225,   225,  -203,
     287,  -203
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -203,  -203,  -203,   -76,  -203,  -203,  -203,  -203,  -203,  -203,
    -203,  -103,   -93,   188,  -203,  -203,  -203,   348,  -203,  -203,
    -203,   292,  -203,  -203,  -203,  -203,  -203,  -203,  -203,   141,
    -202,  -203,  -203,  -203,  -203,  -203,  -203,  -203,   -40,   -62,
     294,  -203,    -1,    65,    -4,   393,  -203,  -203
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint16 yytable[] =
{
      44,    91,    50,    51,    52,    53,    54,    55,    91,   138,
     104,    68,    69,    70,    71,   139,   140,   141,   142,   186,
     143,   162,    91,    62,    64,   138,    91,    91,    91,   133,
      66,   139,   140,   141,   142,   134,   143,   138,   119,   124,
     146,   137,   156,   139,   140,   141,   142,   160,   143,   114,
     164,    59,    78,   159,    56,   138,   195,    57,    81,   222,
      92,   139,   140,   141,   142,   245,   143,    93,   144,   246,
     247,   110,   145,   172,   174,   187,   176,   177,   178,   179,
     180,    94,   115,   172,   305,    95,    96,   316,    58,   132,
     120,   125,   147,   138,   157,   116,   314,    63,    88,   139,
     140,   141,   142,   138,   143,   125,   223,    82,    83,   139,
     140,   141,   142,   175,   143,    60,    89,   248,    80,   198,
     333,    77,   132,   107,   108,   132,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,   199,   341,   109,
       2,   169,    23,   170,   141,   142,   236,   143,   237,   184,
     185,   262,   169,    65,   196,     3,     4,     5,    79,   210,
     271,   272,   273,   274,   201,   202,   203,   204,   205,     6,
       7,    66,     8,     9,    10,    11,   292,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    84,   169,
      73,   200,    72,    23,    24,    25,    17,    18,    19,    20,
     112,   308,   309,   310,   311,   153,   154,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,   303,    12,
      13,    14,    15,    23,    17,    18,    19,    20,   138,   257,
     258,   259,   260,    85,   139,   140,   141,   142,    86,   143,
     313,    97,    12,    13,    14,    15,   208,   306,   209,    98,
      99,   100,   101,   279,   127,   128,   129,   130,    90,   280,
     287,   334,   335,   336,   337,   338,   113,    21,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,   225,
     226,   227,   228,   208,    23,   211,   269,   118,   270,   102,
     121,   103,   123,   126,   281,   282,   269,    97,   288,   135,
     136,   145,   148,   152,   149,    98,    99,   100,   101,   279,
     150,   151,   155,   158,   287,   280,   161,   163,   165,   166,
     171,   287,   143,   181,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,   167,   168,   183,   189,   287,
      23,   191,   190,    97,   192,   102,   193,   103,   194,   212,
     281,    98,    99,   100,   101,   138,   323,   324,   325,   326,
     327,   139,   140,   141,   142,   197,   143,   213,   206,   108,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,   214,   216,   215,   217,   218,    23,   219,   220,   221,
     224,   102,   234,   103,   235,   230,   231,   229,   232,   233,
     238,   249,   264,   244,   265,   239,   240,   241,   242,   243,
     253,   254,   266,   255,   256,   267,   268,   275,   289,   276,
     277,   278,   290,   291,   293,   294,   295,   296,   297,   339,
     340,   263,   122,   298,   299,   300,   302,   301,   307,   182,
     318,   317,   329,   319,   188,   315,     0,     0,   320,   321,
     322,     0,   330,   331,   332,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   111
};

static const yytype_int16 yycheck[] =
{
       1,     3,     3,     4,     5,     6,     7,     8,     3,     3,
      72,    51,    52,    53,    54,     9,    10,    11,    12,     8,
      14,   124,     3,    24,    25,     3,     3,     3,     3,    91,
      18,     9,    10,    11,    12,    97,    14,     3,     7,     7,
       7,   103,     7,     9,    10,    11,    12,   123,    14,    19,
     126,     8,    56,     7,    18,     3,   159,    18,    59,    18,
      62,     9,    10,    11,    12,     7,    14,    62,    62,    11,
      12,    75,    60,   135,   136,    64,   138,   139,   140,   141,
     142,    62,    52,   145,    62,    62,    62,    62,    18,    90,
      59,    59,    59,     3,    59,    65,    62,     8,    18,     9,
      10,    11,    12,     3,    14,    59,    65,    51,    52,     9,
      10,    11,    12,    61,    14,     8,    36,    59,     8,    18,
     322,    56,   123,    48,    49,   126,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    36,   340,    74,
       0,    59,    53,    61,    11,    12,   208,    14,   210,   150,
     151,    61,    59,    18,    61,    15,    16,    17,    62,    59,
     253,   254,   255,   256,   165,   166,   167,   168,   169,    29,
      30,    18,    32,    33,    34,    35,   269,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,     8,    59,
       8,    61,    18,    53,    54,    55,    42,    43,    44,    45,
      62,   294,   295,   296,   297,    11,    12,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,   280,    37,
      38,    39,    40,    53,    42,    43,    44,    45,     3,   230,
     231,   232,   233,    18,     9,    10,    11,    12,    18,    14,
     302,    10,    37,    38,    39,    40,    59,   287,    61,    18,
      19,    20,    21,    22,     9,    10,    11,    12,    60,    28,
     261,   323,   324,   325,   326,   327,    63,    46,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,     9,
      10,    11,    12,    59,    53,    61,    59,     7,    61,    58,
       7,    60,    60,    60,    63,    64,    59,    10,    61,    60,
      60,    60,     7,    53,    62,    18,    19,    20,    21,    22,
      63,    63,    52,    51,   315,    28,    53,    18,    60,    60,
      18,   322,    14,    18,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    60,    60,    48,    52,   340,
      53,     7,    52,    10,    62,    58,    19,    60,     7,     7,
      63,    18,    19,    20,    21,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,     8,    14,    64,    62,    49,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    64,    64,    62,     7,     7,    53,    62,    18,    57,
      60,    58,    18,    60,    63,    59,    59,    62,    59,    59,
      62,    18,    18,    56,    18,    62,    62,    62,    62,    60,
      60,    60,    18,    60,    60,     7,    18,    61,     7,    61,
      61,    61,     7,     7,    62,    59,    59,    59,    59,    64,
      23,   243,    84,    62,    62,    62,    60,    62,    57,   145,
      61,    56,    62,    61,   152,   304,    -1,    -1,    61,    61,
      61,    -1,    62,    62,    62,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    76
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    67,     0,    15,    16,    17,    29,    30,    32,    33,
      34,    35,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    53,    54,    55,    68,    70,    71,    73,
      74,    75,    76,    80,    81,    84,    86,    90,    98,    99,
     100,   101,   102,   103,   108,   109,   110,   111,   112,   113,
     108,   108,   108,   108,   108,   108,    18,    18,    18,     8,
       8,    82,   108,     8,   108,    18,    18,   104,   104,   104,
     104,   104,    18,     8,    87,    88,    89,   109,   110,    62,
       8,   108,    51,    52,     8,    18,    18,    83,    18,    36,
      60,     3,    62,    62,    62,    62,    62,    10,    18,    19,
      20,    21,    58,    60,   105,   107,   108,    48,    49,   109,
     110,   111,    62,    63,    19,    52,    65,    85,     7,     7,
      59,     7,    83,    60,     7,    59,    60,     9,    10,    11,
      12,    69,   108,   105,   105,    60,    60,   105,     3,     9,
      10,    11,    12,    14,    62,    60,     7,    59,     7,    62,
      63,    63,    53,    11,    12,    52,     7,    59,    51,     7,
      69,    53,    77,    18,    69,    60,    60,    60,    60,    59,
      61,    18,   105,   106,   105,    61,   105,   105,   105,   105,
     105,    18,   106,    48,   108,   108,     8,    64,    87,    52,
      52,     7,    62,    19,     7,    77,    61,     8,    18,    36,
      61,   108,   108,   108,   108,   108,    62,    72,    59,    61,
      59,    61,     7,    64,    64,    62,    64,     7,     7,    62,
      18,    57,    18,    65,    60,     9,    10,    11,    12,    62,
      59,    59,    59,    59,    18,    63,   105,   105,    62,    62,
      62,    62,    62,    60,    56,     7,    11,    12,    59,    18,
      77,    78,    79,    60,    60,    60,    60,   108,   108,   108,
     108,    95,    61,    79,    18,    18,    18,     7,    18,    59,
      61,    78,    78,    78,    78,    61,    61,    61,    61,    22,
      28,    63,    64,    91,    96,    97,   105,   108,    61,     7,
       7,     7,    78,    62,    59,    59,    59,    59,    62,    62,
      62,    62,    60,   105,    92,    62,   104,    57,    78,    78,
      78,    78,    94,   105,    62,    95,    62,    56,    61,    61,
      61,    61,    61,     4,     5,     6,     7,     8,    93,    62,
      62,    62,    62,    96,   105,   105,   105,   105,   105,    64,
      23,    96
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
		  Type, Value, Location); \
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
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (yylocationp);
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
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
yy_reduce_print (YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yylsp, yyrule)
    YYSTYPE *yyvsp;
    YYLTYPE *yylsp;
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
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, yylsp, Rule); \
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yylocationp)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {
      case 67: /* "program" */

/* Line 1000 of yacc.c  */
#line 140 "parser.y"
	{
        if(!is_predef)
        {
            if(!context::get_ctx()->built_in_code.empty())
                ouput_src = context::get_ctx()->built_in_code;

            ouput_src += *(yyvaluep->str);
            if(g_info)
            {
                g_info->uniforms = context::get_ctx()->uniforms;
                g_info->varyings = context::get_ctx()->varyings;
                g_info->attributes = context::get_ctx()->attributes;
                g_info->samplers = context::get_ctx()->samplers;
            }
            context::get_ctx()->cleanup();
        }
        SAFE_DELETE((yyvaluep->str));
};

/* Line 1000 of yacc.c  */
#line 1491 "D:/nprojects/safegi/base/libs/sparser/parser.cpp"
	break;
      case 69: /* "para_list" */

/* Line 1000 of yacc.c  */
#line 139 "parser.y"
	{ SAFE_DELETE((yyvaluep->paralist)); };

/* Line 1000 of yacc.c  */
#line 1500 "D:/nprojects/safegi/base/libs/sparser/parser.cpp"
	break;
      case 83: /* "ano_list" */

/* Line 1000 of yacc.c  */
#line 139 "parser.y"
	{ SAFE_DELETE((yyvaluep->anolist)); };

/* Line 1000 of yacc.c  */
#line 1509 "D:/nprojects/safegi/base/libs/sparser/parser.cpp"
	break;
      case 94: /* "cond_expr" */

/* Line 1000 of yacc.c  */
#line 139 "parser.y"
	{ SAFE_DELETE((yyvaluep->expression)); };

/* Line 1000 of yacc.c  */
#line 1518 "D:/nprojects/safegi/base/libs/sparser/parser.cpp"
	break;
      case 104: /* "decl_id" */

/* Line 1000 of yacc.c  */
#line 139 "parser.y"
	{ SAFE_DELETE((yyvaluep->decl_id)); };

/* Line 1000 of yacc.c  */
#line 1527 "D:/nprojects/safegi/base/libs/sparser/parser.cpp"
	break;
      case 105: /* "expr" */

/* Line 1000 of yacc.c  */
#line 139 "parser.y"
	{ SAFE_DELETE((yyvaluep->expression)); };

/* Line 1000 of yacc.c  */
#line 1536 "D:/nprojects/safegi/base/libs/sparser/parser.cpp"
	break;
      case 106: /* "arg_list" */

/* Line 1000 of yacc.c  */
#line 139 "parser.y"
	{ SAFE_DELETE((yyvaluep->arglist)); };

/* Line 1000 of yacc.c  */
#line 1545 "D:/nprojects/safegi/base/libs/sparser/parser.cpp"
	break;
      case 107: /* "literal_num" */

/* Line 1000 of yacc.c  */
#line 139 "parser.y"
	{ SAFE_DELETE((yyvaluep->expression)); };

/* Line 1000 of yacc.c  */
#line 1554 "D:/nprojects/safegi/base/libs/sparser/parser.cpp"
	break;
      case 108: /* "type" */

/* Line 1000 of yacc.c  */
#line 139 "parser.y"
	{ SAFE_DELETE((yyvaluep->type)); };

/* Line 1000 of yacc.c  */
#line 1563 "D:/nprojects/safegi/base/libs/sparser/parser.cpp"
	break;

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


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Location data for the lookahead symbol.  */
YYLTYPE yylloc;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

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
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.
       `yyls': related to locations.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[2];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;
  yylsp = yyls;

#if YYLTYPE_IS_TRIVIAL
  /* Initialize the default location before parsing starts.  */
  yylloc.first_line   = yylloc.last_line   = 1;
  yylloc.first_column = yylloc.last_column = 1;
#endif

/* User initialization code.  */

/* Line 1242 of yacc.c  */
#line 159 "parser.y"
{ ouput_src.clear(); if(is_predef) context::get_ctx()->cleanup(); }

/* Line 1242 of yacc.c  */
#line 1717 "D:/nprojects/safegi/base/libs/sparser/parser.cpp"

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
	YYLTYPE *yyls1 = yyls;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);

	yyls = yyls1;
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
	YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

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
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
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

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;
  *++yylsp = yylloc;
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

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1455 of yacc.c  */
#line 163 "parser.y"
    { (yyval.str) = new string();;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 165 "parser.y"
    {
    (yyval.str) = (yyvsp[(1) - (2)].str);
    if((yyvsp[(2) - (2)].str))
    {
        *(yyval.str) += *(yyvsp[(2) - (2)].str);
        SAFE_DELETE((yyvsp[(2) - (2)].str));
    }
;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 175 "parser.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 176 "parser.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 177 "parser.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 178 "parser.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 179 "parser.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 180 "parser.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 181 "parser.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 182 "parser.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 183 "parser.y"
    { (yyval.str) = 0; ;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 184 "parser.y"
    { (yyval.str) = 0; ;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 185 "parser.y"
    { (yyval.str) = 0; ;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 186 "parser.y"
    { (yyval.str) = 0; ;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 187 "parser.y"
    { (yyval.str) = 0; ;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 188 "parser.y"
    { (yyval.str) = 0; ;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 189 "parser.y"
    { (yyval.str) = 0; ;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 190 "parser.y"
    { (yyval.str) = 0; ;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 191 "parser.y"
    { (yyval.str) = 0; ;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 195 "parser.y"
    { /* empty */
    (yyval.paralist) = new gs_paralist();
;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 199 "parser.y"
    {
    (yyval.paralist) = new gs_paralist();
    (yyval.paralist)->list.push_back(t_var((yyvsp[(1) - (2)].type)->type, *(yyvsp[(2) - (2)].str)));
    (yyval.paralist)->src = (yyvsp[(1) - (2)].type)->src + " " + *(yyvsp[(2) - (2)].str);
    SAFE_DELETE((yyvsp[(1) - (2)].type));
    SAFE_DELETE((yyvsp[(2) - (2)].str));
;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 207 "parser.y"
    {
    (yyval.paralist) = (yyvsp[(1) - (4)].paralist);
    (yyval.paralist)->list.push_back(t_var((yyvsp[(3) - (4)].type)->type, *(yyvsp[(4) - (4)].str)));
    (yyval.paralist)->src += ',' + (yyvsp[(3) - (4)].type)->src + " " + *(yyvsp[(4) - (4)].str);
    SAFE_DELETE((yyvsp[(3) - (4)].type));
    SAFE_DELETE((yyvsp[(4) - (4)].str));
;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 217 "parser.y"
    {
               (yyval.str) = new string();
               *(yyval.str) = (yyvsp[(1) - (6)].type)->src + " " + *(yyvsp[(2) - (6)].str) + '(' + (yyvsp[(4) - (6)].paralist)->src + ");\n";

               string func_name = *(yyvsp[(2) - (6)].str);
               shared_ptr<t_ano_type> return_type = (yyvsp[(1) - (6)].type)->type;
               vector<shared_ptr<t_ano_type>> para_typelist = (yyvsp[(4) - (6)].paralist)->get_type_list();

               context::get_ctx()->functions.push_back(cx_function((yyvsp[(1) - (6)].type)->type, *(yyvsp[(2) - (6)].str), (yyvsp[(4) - (6)].paralist)->get_type_list()));

               SAFE_DELETE((yyvsp[(1) - (6)].type));
               SAFE_DELETE((yyvsp[(2) - (6)].str));
               SAFE_DELETE((yyvsp[(4) - (6)].paralist));
               PRINT_DEBUG("DECLARE FUNCTION: %s\n", (yyval.str)->c_str());
           ;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 235 "parser.y"
    { 
              context::get_ctx()->push_context();
              vector<t_var> &list = (yyvsp[(4) - (5)].paralist)->list;
              for(unsigned int i = 0; i < list.size(); i++)
              {
                  t_var &var = list[i];
                  context::get_ctx()->variables[var.name] = var;
              }
              context::get_ctx()->func_rtype = (yyvsp[(1) - (5)].type)->type;
          ;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 246 "parser.y"
    {
              context::get_ctx()->pop_context();
              (yyval.str) = new string();
              *(yyval.str) = (yyvsp[(1) - (9)].type)->src + " " + *(yyvsp[(2) - (9)].str) + '(' + (yyvsp[(4) - (9)].paralist)->src + ")\n" + "{\n" + *(yyvsp[(8) - (9)].str) + "}\n";

              context::get_ctx()->functions.push_back(cx_function((yyvsp[(1) - (9)].type)->type, *(yyvsp[(2) - (9)].str), (yyvsp[(4) - (9)].paralist)->get_type_list()));

              SAFE_DELETE((yyvsp[(1) - (9)].type));
              SAFE_DELETE((yyvsp[(2) - (9)].str));
              SAFE_DELETE((yyvsp[(4) - (9)].paralist));
              SAFE_DELETE((yyvsp[(8) - (9)].str));
              PRINT_DEBUG("DEFINE FUNCTION: %s\n", (yyval.str)->c_str());
          ;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 263 "parser.y"
    {
                      context::get_ctx()->functions.push_back(cx_function((yyvsp[(2) - (7)].type)->type, *(yyvsp[(3) - (7)].str), (yyvsp[(5) - (7)].paralist)->get_type_list()));
                      PRINT_DEBUG("CALL_CONVENTION: %s %s ( %s );\n", (yyvsp[(2) - (7)].type)->src.c_str(), (yyvsp[(3) - (7)].str)->c_str(), (yyvsp[(5) - (7)].paralist)->src.c_str());
                      SAFE_DELETE((yyvsp[(2) - (7)].type));
                      SAFE_DELETE((yyvsp[(3) - (7)].str));
                      SAFE_DELETE((yyvsp[(5) - (7)].paralist));
                  ;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 273 "parser.y"
    {
                    context::get_ctx()->bin_functions.push_back(cx_bin_function((yyvsp[(2) - (8)].type)->type, *(yyvsp[(3) - (8)].str), (yyvsp[(5) - (8)].paralist)->list, *(yyvsp[(7) - (8)].str), *(yyvsp[(8) - (8)].str)));
                    PRINT_DEBUG("BUILT_IN: %s %s ( %s ) - %s\n", (yyvsp[(2) - (8)].type)->src.c_str(), (yyvsp[(3) - (8)].str)->c_str(), (yyvsp[(5) - (8)].paralist)->src.c_str(), (yyvsp[(7) - (8)].str)->c_str());
                    SAFE_DELETE((yyvsp[(2) - (8)].type));
                    SAFE_DELETE((yyvsp[(3) - (8)].str));
                    SAFE_DELETE((yyvsp[(5) - (8)].paralist));
                    SAFE_DELETE((yyvsp[(7) - (8)].str));
                    SAFE_DELETE((yyvsp[(8) - (8)].str));
                ;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 285 "parser.y"
    {
                          vector<shared_ptr<t_ano_type>> typelist;
                          typelist.push_back((yyvsp[(6) - (10)].type)->type);
                          typelist.push_back((yyvsp[(8) - (10)].type)->type);
                          context::get_ctx()->functions.push_back(cx_function((yyvsp[(2) - (10)].type)->type, "+", typelist));
                          //// Exchange
                          //shared_ptr<t_ano_type> t = typelist[1];
                          //typelist[1] = typelist[0];
                          //typelist[0] = t;
                          //context::get_ctx()->functions.push_back(cx_function($2->type, "+", typelist));
                          PRINT_DEBUG("OPER_CONV: %s operator+ ( %s,  %s);\n", (yyvsp[(2) - (10)].type)->src.c_str(), (yyvsp[(6) - (10)].type)->src.c_str(), (yyvsp[(8) - (10)].type)->src.c_str());
                          SAFE_DELETE((yyvsp[(2) - (10)].type));
                          SAFE_DELETE((yyvsp[(6) - (10)].type));
                          SAFE_DELETE((yyvsp[(8) - (10)].type));
                      ;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 301 "parser.y"
    {
                          vector<shared_ptr<t_ano_type>> typelist;
                          typelist.push_back((yyvsp[(6) - (10)].type)->type);
                          typelist.push_back((yyvsp[(8) - (10)].type)->type);
                          context::get_ctx()->functions.push_back(cx_function((yyvsp[(2) - (10)].type)->type, "-", typelist));
                          PRINT_DEBUG("OPER_CONV: %s operator- ( %s,  %s);\n", (yyvsp[(2) - (10)].type)->src.c_str(), (yyvsp[(6) - (10)].type)->src.c_str(), (yyvsp[(8) - (10)].type)->src.c_str());
                          SAFE_DELETE((yyvsp[(2) - (10)].type));
                          SAFE_DELETE((yyvsp[(6) - (10)].type));
                          SAFE_DELETE((yyvsp[(8) - (10)].type));
                      ;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 312 "parser.y"
    {
                          vector<shared_ptr<t_ano_type>> typelist;
                          typelist.push_back((yyvsp[(6) - (10)].type)->type);
                          typelist.push_back((yyvsp[(8) - (10)].type)->type);
                          context::get_ctx()->functions.push_back(cx_function((yyvsp[(2) - (10)].type)->type, "*", typelist));
                          //// Exchange
                          //shared_ptr<t_ano_type> t = typelist[1];
                          //typelist[1] = typelist[0];
                          //typelist[0] = t;
                          //context::get_ctx()->functions.push_back(cx_function($2->type, "*", typelist));
                          PRINT_DEBUG("OPER_CONV: %s operator *( %s,  %s);\n", (yyvsp[(2) - (10)].type)->src.c_str(), (yyvsp[(6) - (10)].type)->src.c_str(), (yyvsp[(8) - (10)].type)->src.c_str());
                          SAFE_DELETE((yyvsp[(2) - (10)].type));
                          SAFE_DELETE((yyvsp[(6) - (10)].type));
                          SAFE_DELETE((yyvsp[(8) - (10)].type));
                      ;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 328 "parser.y"
    {
                          vector<shared_ptr<t_ano_type>> typelist;
                          typelist.push_back((yyvsp[(6) - (10)].type)->type);
                          typelist.push_back((yyvsp[(8) - (10)].type)->type);
                          context::get_ctx()->functions.push_back(cx_function((yyvsp[(2) - (10)].type)->type, "/", typelist));
                          PRINT_DEBUG("OPER_CONV: %s operator/ ( %s,  %s);\n", (yyvsp[(2) - (10)].type)->src.c_str(), (yyvsp[(6) - (10)].type)->src.c_str(), (yyvsp[(8) - (10)].type)->src.c_str());
                          SAFE_DELETE((yyvsp[(2) - (10)].type));
                          SAFE_DELETE((yyvsp[(6) - (10)].type));
                          SAFE_DELETE((yyvsp[(8) - (10)].type));
                      ;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 341 "parser.y"
    {
                              vector<string> ano_list = (yyvsp[(3) - (13)].anolist)->list;
                              cx_generic_ano_type ret_type = *(yyvsp[(5) - (13)].gen_ano_type);
                              vector<cx_generic_ano_para> list;
                              list.push_back(*(yyvsp[(9) - (13)].gen_ano_para));
                              list.push_back(*(yyvsp[(11) - (13)].gen_ano_para));
                              context::get_ctx()->ano_functions.push_back(cx_ano_function("+", ano_list, ret_type, list));
                              PRINT_DEBUG("OPER_CONV: %s < %s > operator+ ( %s,  %s);\n", (yyvsp[(3) - (13)].anolist)->src.c_str(), (yyvsp[(5) - (13)].gen_ano_type)->name.c_str(), (yyvsp[(9) - (13)].gen_ano_para)->name.c_str(), (yyvsp[(11) - (13)].gen_ano_para)->name.c_str());
                              SAFE_DELETE((yyvsp[(3) - (13)].anolist));
                              SAFE_DELETE((yyvsp[(5) - (13)].gen_ano_type));
                              SAFE_DELETE((yyvsp[(9) - (13)].gen_ano_para));
                              SAFE_DELETE((yyvsp[(11) - (13)].gen_ano_para));
                          ;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 355 "parser.y"
    {
                              vector<string> ano_list = (yyvsp[(3) - (13)].anolist)->list;
                              cx_generic_ano_type ret_type = *(yyvsp[(5) - (13)].gen_ano_type);
                              vector<cx_generic_ano_para> list;
                              list.push_back(*(yyvsp[(9) - (13)].gen_ano_para));
                              list.push_back(*(yyvsp[(11) - (13)].gen_ano_para));
                              context::get_ctx()->ano_functions.push_back(cx_ano_function("-", ano_list, ret_type, list));
                              PRINT_DEBUG("OPER_CONV: %s < %s > operator- ( %s,  %s);\n", (yyvsp[(3) - (13)].anolist)->src.c_str(), (yyvsp[(5) - (13)].gen_ano_type)->name.c_str(), (yyvsp[(9) - (13)].gen_ano_para)->name.c_str(), (yyvsp[(11) - (13)].gen_ano_para)->name.c_str());
                              SAFE_DELETE((yyvsp[(3) - (13)].anolist));
                              SAFE_DELETE((yyvsp[(5) - (13)].gen_ano_type));
                              SAFE_DELETE((yyvsp[(9) - (13)].gen_ano_para));
                              SAFE_DELETE((yyvsp[(11) - (13)].gen_ano_para));
                          ;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 369 "parser.y"
    {
                              vector<string> ano_list = (yyvsp[(3) - (13)].anolist)->list;
                              cx_generic_ano_type ret_type = *(yyvsp[(5) - (13)].gen_ano_type);
                              vector<cx_generic_ano_para> list;
                              list.push_back(*(yyvsp[(9) - (13)].gen_ano_para));
                              list.push_back(*(yyvsp[(11) - (13)].gen_ano_para));
                              context::get_ctx()->ano_functions.push_back(cx_ano_function("*", ano_list, ret_type, list));
                              PRINT_DEBUG("OPER_CONV: %s < %s > operator* ( %s,  %s);\n", (yyvsp[(3) - (13)].anolist)->src.c_str(), (yyvsp[(5) - (13)].gen_ano_type)->name.c_str(), (yyvsp[(9) - (13)].gen_ano_para)->name.c_str(), (yyvsp[(11) - (13)].gen_ano_para)->name.c_str());
                              SAFE_DELETE((yyvsp[(3) - (13)].anolist));
                              SAFE_DELETE((yyvsp[(5) - (13)].gen_ano_type));
                              SAFE_DELETE((yyvsp[(9) - (13)].gen_ano_para));
                              SAFE_DELETE((yyvsp[(11) - (13)].gen_ano_para));
                          ;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 383 "parser.y"
    {
                              vector<string> ano_list = (yyvsp[(3) - (13)].anolist)->list;
                              cx_generic_ano_type ret_type = *(yyvsp[(5) - (13)].gen_ano_type);
                              vector<cx_generic_ano_para> list;
                              list.push_back(*(yyvsp[(9) - (13)].gen_ano_para));
                              list.push_back(*(yyvsp[(11) - (13)].gen_ano_para));
                              context::get_ctx()->ano_functions.push_back(cx_ano_function("/", ano_list, ret_type, list));
                              PRINT_DEBUG("OPER_CONV: %s < %s > operator/ ( %s,  %s);", (yyvsp[(3) - (13)].anolist)->src.c_str(), (yyvsp[(5) - (13)].gen_ano_type)->name.c_str(), (yyvsp[(9) - (13)].gen_ano_para)->name.c_str(), (yyvsp[(11) - (13)].gen_ano_para)->name.c_str());
                              SAFE_DELETE((yyvsp[(3) - (13)].anolist));
                              SAFE_DELETE((yyvsp[(5) - (13)].gen_ano_type));
                              SAFE_DELETE((yyvsp[(9) - (13)].gen_ano_para));
                              SAFE_DELETE((yyvsp[(11) - (13)].gen_ano_para));
                          ;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 399 "parser.y"
    {
                         (yyval.gen_ano_type) = new cx_generic_ano_type(*(yyvsp[(1) - (1)].str));
                         SAFE_DELETE((yyvsp[(1) - (1)].str));              
                     ;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 404 "parser.y"
    {
                         (yyval.gen_ano_type) = new cx_generic_ano_type(*(yyvsp[(1) - (4)].str), *(yyvsp[(3) - (4)].str));
                         SAFE_DELETE((yyvsp[(1) - (4)].str));
                         SAFE_DELETE((yyvsp[(3) - (4)].str));
                     ;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 410 "parser.y"
    {
                         (yyval.gen_ano_type) = new cx_generic_ano_type(*(yyvsp[(1) - (6)].str), *(yyvsp[(3) - (6)].str), *(yyvsp[(5) - (6)].str));
                         SAFE_DELETE((yyvsp[(1) - (6)].str));
                         SAFE_DELETE((yyvsp[(3) - (6)].str));
                         SAFE_DELETE((yyvsp[(5) - (6)].str));
                     ;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 417 "parser.y"
    {
                         (yyval.gen_ano_type) = new cx_generic_ano_type(*(yyvsp[(1) - (6)].str), *(yyvsp[(3) - (6)].str), *(yyvsp[(5) - (6)].str), cx_generic_ano_type::MUL);
                         SAFE_DELETE((yyvsp[(1) - (6)].str));
                         SAFE_DELETE((yyvsp[(3) - (6)].str));
                         SAFE_DELETE((yyvsp[(5) - (6)].str));
                     ;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 424 "parser.y"
    {
                         (yyval.gen_ano_type) = new cx_generic_ano_type(*(yyvsp[(1) - (6)].str), *(yyvsp[(3) - (6)].str), *(yyvsp[(5) - (6)].str), cx_generic_ano_type::DIV);
                         SAFE_DELETE((yyvsp[(1) - (6)].str));
                         SAFE_DELETE((yyvsp[(3) - (6)].str));
                         SAFE_DELETE((yyvsp[(5) - (6)].str));
                     ;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 431 "parser.y"
    {
                         (yyval.gen_ano_type) = new cx_generic_ano_type(*(yyvsp[(1) - (5)].str), *(yyvsp[(4) - (5)].str), "", cx_generic_ano_type::SQRT);
                         SAFE_DELETE((yyvsp[(1) - (5)].str));
                         SAFE_DELETE((yyvsp[(4) - (5)].str));
                     ;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 438 "parser.y"
    {
                       (yyval.gen_ano_para) = new cx_generic_ano_para(*(yyvsp[(1) - (2)].gen_ano_type), *(yyvsp[(2) - (2)].str));
                       SAFE_DELETE((yyvsp[(1) - (2)].gen_ano_type));
                       SAFE_DELETE((yyvsp[(2) - (2)].str));
                   ;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 444 "parser.y"
    {
                       (yyval.gen_ano_para) = new cx_generic_ano_para(*(yyvsp[(1) - (1)].gen_ano_type), "");
                       SAFE_DELETE((yyvsp[(1) - (1)].gen_ano_type));
                   ;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 451 "parser.y"
    {
                           (yyval.gen_ano_paralist) = new gs_generic_ano_paralist();
                           (yyval.gen_ano_paralist)->list.push_back(*(yyvsp[(1) - (1)].gen_ano_para));
                           SAFE_DELETE((yyvsp[(1) - (1)].gen_ano_para));
                       ;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 457 "parser.y"
    {
                           (yyval.gen_ano_paralist) = (yyvsp[(1) - (3)].gen_ano_paralist);
                           (yyval.gen_ano_paralist)->list.push_back(*(yyvsp[(3) - (3)].gen_ano_para));
                           SAFE_DELETE((yyvsp[(3) - (3)].gen_ano_para));
                       ;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 465 "parser.y"
    {
                          vector<string> ano_list = (yyvsp[(3) - (10)].anolist)->list;
                          cx_generic_ano_type ret_type = *(yyvsp[(5) - (10)].gen_ano_type);
                          context::get_ctx()->ano_functions.push_back(cx_ano_function(*(yyvsp[(6) - (10)].str), ano_list, ret_type, (yyvsp[(8) - (10)].gen_ano_paralist)->list));
                          PRINT_DEBUG("ANO_CALL_CONV: %s < %s > %s ( %s );", (yyvsp[(3) - (10)].anolist)->src.c_str(), (yyvsp[(5) - (10)].gen_ano_type)->name.c_str(), (yyvsp[(6) - (10)].str)->c_str(), (yyvsp[(8) - (10)].gen_ano_paralist)->src.c_str());
                          SAFE_DELETE((yyvsp[(3) - (10)].anolist));
                          SAFE_DELETE((yyvsp[(5) - (10)].gen_ano_type));
                          SAFE_DELETE((yyvsp[(6) - (10)].str));
                          SAFE_DELETE((yyvsp[(8) - (10)].gen_ano_paralist));
                      ;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 478 "parser.y"
    {
                        context::get_ctx()->state = context::SkipAnoId;
                    ;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 482 "parser.y"
    {
                        context::get_ctx()->state = context::Normal;
                        vector<string> ano_list = (yyvsp[(4) - (12)].anolist)->list;
                        cx_generic_ano_type ret_type = *(yyvsp[(6) - (12)].gen_ano_type);
                        context::get_ctx()->bin_ano_functions.push_back(cx_bin_ano_function(*(yyvsp[(7) - (12)].str), ano_list, ret_type, (yyvsp[(9) - (12)].gen_ano_paralist)->list, *(yyvsp[(11) - (12)].str), *(yyvsp[(12) - (12)].str)));
                        PRINT_DEBUG("ANO_BUILT_IN: %s < %s > %s ( %s );", (yyvsp[(4) - (12)].anolist)->src.c_str(), (yyvsp[(6) - (12)].gen_ano_type)->name.c_str(), (yyvsp[(7) - (12)].str)->c_str(), (yyvsp[(9) - (12)].gen_ano_paralist)->src.c_str());
                        SAFE_DELETE((yyvsp[(4) - (12)].anolist));
                        SAFE_DELETE((yyvsp[(6) - (12)].gen_ano_type));
                        SAFE_DELETE((yyvsp[(7) - (12)].str));
                        SAFE_DELETE((yyvsp[(9) - (12)].gen_ano_paralist));
                        SAFE_DELETE((yyvsp[(11) - (12)].str));
                        SAFE_DELETE((yyvsp[(12) - (12)].str));
                    ;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 498 "parser.y"
    {
               (yyval.anolist) = new gs_anolist();
               (yyval.anolist)->list.push_back(*(yyvsp[(1) - (1)].str));
               SAFE_DELETE((yyvsp[(1) - (1)].str));
           ;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 504 "parser.y"
    {
               (yyval.anolist) = (yyvsp[(1) - (3)].anolist);
               (yyval.anolist)->list.push_back(*(yyvsp[(3) - (3)].str));
               SAFE_DELETE((yyvsp[(3) - (3)].str));
           ;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 513 "parser.y"
    {
                    context::get_ctx()->space_anos[*(yyvsp[(2) - (3)].str)] = t_space_ano(*(yyvsp[(2) - (3)].str));
                    PRINT_DEBUG("_def_space_ano %s ;\n", (yyvsp[(2) - (3)].str)->c_str());
                    SAFE_DELETE((yyvsp[(2) - (3)].str));
                ;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 521 "parser.y"
    {
                        int sig = strtol((yyvsp[(1) - (1)].str)->c_str(), NULL, 0);
                        (yyval.sig_list) = new gs_signature_list();
                        (yyval.sig_list)->list.push_back(sig);
                        SAFE_DELETE((yyvsp[(1) - (1)].str));
                    ;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 528 "parser.y"
    {
                        (yyval.sig_list) = (yyvsp[(1) - (3)].sig_list);
                        int sig = strtol((yyvsp[(3) - (3)].str)->c_str(), NULL, 0);
                        (yyval.sig_list)->list.push_back(sig);
                        SAFE_DELETE((yyvsp[(3) - (3)].str));
                    ;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 537 "parser.y"
    {
                  string new_dim = *(yyvsp[(2) - (6)].str);
                  context::get_ctx()->dim_anos[new_dim] = t_dim_ano(new_dim, (yyvsp[(4) - (6)].sig_list)->list);
                  PRINT_DEBUG("_def_dim_ano %s ;\n", (yyvsp[(2) - (6)].str)->c_str());
                  SAFE_DELETE((yyvsp[(2) - (6)].str));
                  SAFE_DELETE((yyvsp[(4) - (6)].sig_list));
              ;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 545 "parser.y"
    {
                  string new_dim = *(yyvsp[(2) - (8)].str);
                  t_dim_ano *d1 = (yyvsp[(4) - (8)].dimen_ano);
                  t_dim_ano *d2 = (yyvsp[(6) - (8)].dimen_ano);
                  context::get_ctx()->dim_anos[new_dim] = (*d1) * (*d2);
                  PRINT_DEBUG("_def_dim_ano %s <%s * %s>;\n", (yyvsp[(2) - (8)].str)->c_str(), (yyvsp[(4) - (8)].dimen_ano)->name.c_str(), (yyvsp[(6) - (8)].dimen_ano)->name.c_str());
                  SAFE_DELETE((yyvsp[(2) - (8)].str));
              ;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 554 "parser.y"
    {
                  string new_dim = *(yyvsp[(2) - (8)].str);
                  t_dim_ano *d1 = (yyvsp[(4) - (8)].dimen_ano);
                  t_dim_ano *d2 = (yyvsp[(6) - (8)].dimen_ano);
                  context::get_ctx()->dim_anos[new_dim] = (*d1) / (*d2);
                  PRINT_DEBUG("_def_dim_ano %s <%s / %s>;\n", (yyvsp[(2) - (8)].str)->c_str(), (yyvsp[(4) - (8)].dimen_ano)->name.c_str(), (yyvsp[(6) - (8)].dimen_ano)->name.c_str());
                  SAFE_DELETE((yyvsp[(2) - (8)].str));
              ;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 563 "parser.y"
    {
                  string new_dim = *(yyvsp[(2) - (7)].str);
                  t_dim_ano *d1 = (yyvsp[(5) - (7)].dimen_ano);
                  context::get_ctx()->dim_anos[new_dim] = (yyvsp[(5) - (7)].dimen_ano)->sqrt();
                  PRINT_DEBUG("_def_dim_ano %s <# %s>;\n", (yyvsp[(2) - (7)].str)->c_str(), (yyvsp[(5) - (7)].dimen_ano)->name.c_str());
                  SAFE_DELETE((yyvsp[(2) - (7)].str))
              ;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 582 "parser.y"
    {
                  //*** _typemap real 				float;
                  //
                  string newtype_name = *(yyvsp[(2) - (4)].str);
                  string basictype_name = *(yyvsp[(3) - (4)].str);
                  context::get_ctx()->typemaps[newtype_name] = shared_ptr<cx_typemap>(new cx_typemap(newtype_name, basictype_name));
                  PRINT_DEBUG("_typemap %s %s\n", (yyvsp[(2) - (4)].str)->c_str(), (yyvsp[(3) - (4)].str)->c_str());
                  SAFE_DELETE((yyvsp[(2) - (4)].str));
                  SAFE_DELETE((yyvsp[(3) - (4)].str));
              ;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 593 "parser.y"
    {
                  //** _typemap mreal<-dimen-> 	float;
                  //
                  string newtype_name = *(yyvsp[(2) - (5)].str);
                  string basictype_name = *(yyvsp[(4) - (5)].str);
                  context::get_ctx()->typemaps[newtype_name] = shared_ptr<cx_typemap>(new cx_scale_typemap(newtype_name, basictype_name));
                  PRINT_DEBUG("_typemap %s<-dimen-> %s\n", (yyvsp[(2) - (5)].str)->c_str(), (yyvsp[(4) - (5)].str)->c_str());
                  SAFE_DELETE((yyvsp[(2) - (5)].str));
                  SAFE_DELETE((yyvsp[(4) - (5)].str));
              ;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 604 "parser.y"
    {
                  //** _typemap tuple3				vec3{real};
                  //** 
                  string newtype_name = *(yyvsp[(2) - (7)].str);
                  string basictype_name = *(yyvsp[(3) - (7)].str);
                  string membertype_name = *(yyvsp[(5) - (7)].str); //member type;
                  context::get_ctx()->typemaps[newtype_name] = 
                      shared_ptr<cx_typemap>(new cx_tuple_typemap(newtype_name, basictype_name, context::get_ctx()->typemaps[membertype_name]));
                  PRINT_DEBUG("_typemap %s %s { %s }\n", (yyvsp[(2) - (7)].str)->c_str(), (yyvsp[(3) - (7)].str)->c_str(), (yyvsp[(5) - (7)].str)->c_str());
                  SAFE_DELETE((yyvsp[(2) - (7)].str));
                  SAFE_DELETE((yyvsp[(3) - (7)].str));
                  SAFE_DELETE((yyvsp[(5) - (7)].str));
              ;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 618 "parser.y"
    {
                  //** _typemap spectrum			vec3{mreal<-dimen->};
                  string newtype_name = *(yyvsp[(2) - (8)].str);
                  string basictype_name = *(yyvsp[(3) - (8)].str);
                  string membertype_name = *(yyvsp[(5) - (8)].str); //member type;
                  context::get_ctx()->typemaps[newtype_name] = 
                      shared_ptr<cx_typemap>(new cx_tuple_typemap(newtype_name, basictype_name, context::get_ctx()->typemaps[membertype_name]));
                  PRINT_DEBUG("_typemap %s %s { %s<-dimen-> }\n", (yyvsp[(2) - (8)].str)->c_str(), (yyvsp[(3) - (8)].str)->c_str(), (yyvsp[(5) - (8)].str)->c_str());
                  SAFE_DELETE((yyvsp[(2) - (8)].str));
                  SAFE_DELETE((yyvsp[(3) - (8)].str));
                  SAFE_DELETE((yyvsp[(5) - (8)].str));
              ;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 631 "parser.y"
    {
                  //** _typemap direction<-space-> vec3{real};
                  //** _typemap point<-space->		vec3{mreal<length_d>};
                  string newtype_name = *(yyvsp[(2) - (8)].str);
                  string basictype_name = *(yyvsp[(4) - (8)].str);
                  shared_ptr<t_ano_type> member_type = (yyvsp[(6) - (8)].type)->type;//member type;

                  context::get_ctx()->typemaps[newtype_name] = 
                      shared_ptr<cx_typemap>(new cx_space_tuple_typemap(newtype_name, basictype_name, member_type));
                  PRINT_DEBUG("_typemap %s %s { %s }\n", (yyvsp[(2) - (8)].str)->c_str(), (yyvsp[(4) - (8)].str)->c_str(), (yyvsp[(6) - (8)].type)->type->name.c_str());
                  SAFE_DELETE((yyvsp[(2) - (8)].str));
                  SAFE_DELETE((yyvsp[(4) - (8)].str));
                  SAFE_DELETE((yyvsp[(6) - (8)].type));
              ;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 646 "parser.y"
    {
                  //** _typemap rigidmap<-space-, -space-> mat4{real};
                  string newtype_name = *(yyvsp[(2) - (8)].str);
                  string basictype_name = *(yyvsp[(4) - (8)].str);
                  shared_ptr<t_ano_type> member_type = (yyvsp[(6) - (8)].type)->type;//member type;

                  context::get_ctx()->typemaps[newtype_name] = 
                      shared_ptr<cx_typemap>(new cx_mat_typemap(newtype_name, basictype_name, member_type));
                  PRINT_DEBUG("_typemap %s %s { %s }\n", (yyvsp[(2) - (8)].str)->c_str(), (yyvsp[(4) - (8)].str)->c_str(), (yyvsp[(6) - (8)].type)->type->name.c_str());
                  SAFE_DELETE((yyvsp[(2) - (8)].str));
                  SAFE_DELETE((yyvsp[(4) - (8)].str));
                  SAFE_DELETE((yyvsp[(6) - (8)].type));
              ;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 662 "parser.y"
    { context::get_ctx()->push_context(); ;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 662 "parser.y"
    { context::get_ctx()->pop_context(); ;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 663 "parser.y"
    {
           (yyval.str) = (yyvsp[(3) - (5)].str);
           *(yyval.str) = '{' + *(yyvsp[(3) - (5)].str) + '}';
       ;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 668 "parser.y"
    {
           (yyval.str) = (yyvsp[(5) - (7)].str);
           *(yyval.str) = "if(" + (yyvsp[(3) - (7)].expression)->src + ")" + *(yyvsp[(5) - (7)].str) + "else" + *(yyvsp[(7) - (7)].str);   
           SAFE_DELETE((yyvsp[(3) - (7)].expression));
           SAFE_DELETE((yyvsp[(7) - (7)].str));
       ;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 675 "parser.y"
    {
           (yyval.str) = (yyvsp[(5) - (5)].str);
           *(yyval.str) = "if(" + (yyvsp[(3) - (5)].expression)->src + ")" + *(yyvsp[(5) - (5)].str);
           SAFE_DELETE((yyvsp[(3) - (5)].expression));
       ;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 684 "parser.y"
    {
                if(!(yyvsp[(1) - (3)].expression)->type->get_member_type().get() && 
                    !(yyvsp[(3) - (3)].expression)->type->get_member_type().get())
                {
                    (yyval.expression) = new gs_expression(shared_ptr<t_ano_type>(new t_ano_type("bool", "bool")));
                    (yyval.expression)->src = (yyvsp[(1) - (3)].expression)->src + "<" + (yyvsp[(3) - (3)].expression)->src;
                    SAFE_DELETE((yyvsp[(1) - (3)].expression));
                    SAFE_DELETE((yyvsp[(3) - (3)].expression));
                };
            ;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 695 "parser.y"
    {
                if(!(yyvsp[(1) - (3)].expression)->type->get_member_type().get() && 
                    !(yyvsp[(3) - (3)].expression)->type->get_member_type().get())
                {
                    (yyval.expression) = new gs_expression(shared_ptr<t_ano_type>(new t_ano_type("bool", "bool")));
                    (yyval.expression)->src = (yyvsp[(1) - (3)].expression)->src + ">" + (yyvsp[(3) - (3)].expression)->src;
                    SAFE_DELETE((yyvsp[(1) - (3)].expression));
                    SAFE_DELETE((yyvsp[(3) - (3)].expression));
                };
            ;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 706 "parser.y"
    {
                if(!(yyvsp[(1) - (3)].expression)->type->get_member_type().get() && 
                    !(yyvsp[(3) - (3)].expression)->type->get_member_type().get())
                {
                    (yyval.expression) = new gs_expression(shared_ptr<t_ano_type>(new t_ano_type("bool", "bool")));
                    (yyval.expression)->src = (yyvsp[(1) - (3)].expression)->src + "==" + (yyvsp[(3) - (3)].expression)->src;
                    SAFE_DELETE((yyvsp[(1) - (3)].expression));
                    SAFE_DELETE((yyvsp[(3) - (3)].expression));
                };
            ;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 717 "parser.y"
    {
                if(!(yyvsp[(1) - (3)].expression)->type->get_member_type().get() && 
                    !(yyvsp[(3) - (3)].expression)->type->get_member_type().get())
                {
                    (yyval.expression) = new gs_expression(shared_ptr<t_ano_type>(new t_ano_type("bool", "bool")));
                    (yyval.expression)->src = (yyvsp[(1) - (3)].expression)->src + ">=" + (yyvsp[(3) - (3)].expression)->src;
                    SAFE_DELETE((yyvsp[(1) - (3)].expression));
                    SAFE_DELETE((yyvsp[(3) - (3)].expression));
                };
            ;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 728 "parser.y"
    {
                if(!(yyvsp[(1) - (3)].expression)->type->get_member_type().get() && 
                    !(yyvsp[(3) - (3)].expression)->type->get_member_type().get())
                {
                    (yyval.expression) = new gs_expression(shared_ptr<t_ano_type>(new t_ano_type("bool", "bool")));
                    (yyval.expression)->src = (yyvsp[(1) - (3)].expression)->src + "<=" + (yyvsp[(3) - (3)].expression)->src;
                    SAFE_DELETE((yyvsp[(1) - (3)].expression));
                    SAFE_DELETE((yyvsp[(3) - (3)].expression));
                };
            ;}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 741 "parser.y"
    {/* empty */ 
                (yyval.str) = new string();
            ;}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 745 "parser.y"
    {
                (yyval.str) = (yyvsp[(1) - (2)].str);
                *(yyval.str) += *(yyvsp[(2) - (2)].str);
                SAFE_DELETE((yyvsp[(2) - (2)].str));
            ;}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 753 "parser.y"
    {
               (yyval.str) = (yyvsp[(1) - (1)].str);
           ;}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 757 "parser.y"
    {
               (yyval.str) = new string((yyvsp[(1) - (2)].expression)->src + ";\n");
               SAFE_DELETE((yyvsp[(1) - (2)].expression));
           ;}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 762 "parser.y"
    {
               if(*((yyvsp[(2) - (3)].expression)->type) != *(context::get_ctx()->func_rtype))
               {
                   PRINT_ERROR("return type don't match, l%d,c%d-l%d,c%d", (yylsp[(1) - (3)]).first_line, (yylsp[(1) - (3)]).first_column, (yylsp[(3) - (3)]).last_line, (yylsp[(3) - (3)]).last_column);
                   YYERROR;
               }
               else
               {
                   (yyval.str) = new string("return " + (yyvsp[(2) - (3)].expression)->src + ";\n");
                   SAFE_DELETE((yyvsp[(2) - (3)].expression));
               }
           ;}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 775 "parser.y"
    {
               (yyval.str) = (yyvsp[(1) - (1)].str);
           ;}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 781 "parser.y"
    {
                (yyval.str) = new string();
                *(yyval.str) = (yyvsp[(1) - (3)].type)->src + " " + (yyvsp[(2) - (3)].decl_id)->src + ";\n";
                if(!append_declaration(*(yyvsp[(2) - (3)].decl_id), (yyvsp[(1) - (3)].type)->type, context::get_ctx()->variables))
                {
                    PRINT_ERROR("failed to add local variable, l%d,c%d-l%d,c%d", (yylsp[(1) - (3)]).first_line, (yylsp[(1) - (3)]).first_column, (yylsp[(3) - (3)]).last_line, (yylsp[(3) - (3)]).last_column);
                    YYERROR;
                }
                SAFE_DELETE((yyvsp[(1) - (3)].type));
                SAFE_DELETE((yyvsp[(2) - (3)].decl_id));
            ;}
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 796 "parser.y"
    {
                   (yyval.str) = new string();
                   if((yyvsp[(2) - (4)].type)->type->get_space_ano2())
                   {
                       // quickly hack it into a matrix array.
                       (yyvsp[(3) - (4)].decl_id)->src += "[2]";
                   }
                   *(yyval.str) = "uniform " + (yyvsp[(2) - (4)].type)->src + " " + (yyvsp[(3) - (4)].decl_id)->src + ";\n";
                   if(!append_declaration(*(yyvsp[(3) - (4)].decl_id), (yyvsp[(2) - (4)].type)->type, context::get_ctx()->uniforms))
                   {
                       PRINT_ERROR ("failed to add uniform, l%d,c%d-l%d,c%d", (yylsp[(1) - (4)]).first_line, (yylsp[(1) - (4)]).first_column, (yylsp[(4) - (4)]).last_line, (yylsp[(4) - (4)]).last_column);
                       YYERROR;
                   }
                   PRINT_DEBUG("UNIFORM: %s %s", (yyvsp[(2) - (4)].type)->src.c_str(), (yyvsp[(3) - (4)].decl_id)->src.c_str());
                   SAFE_DELETE((yyvsp[(2) - (4)].type));
                   SAFE_DELETE((yyvsp[(3) - (4)].decl_id));
               ;}
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 825 "parser.y"
    {
                   if((yyvsp[(2) - (4)].type)->type->get_space_ano2())
                   {
                       // no varing matrixs;
                       assert(false);
                   }
                   (yyval.str) = new string();
                   *(yyval.str) = "varying " + (yyvsp[(2) - (4)].type)->src + " " + (yyvsp[(3) - (4)].decl_id)->src + ";\n";
                   if(!append_declaration(*(yyvsp[(3) - (4)].decl_id), (yyvsp[(2) - (4)].type)->type, context::get_ctx()->varyings))
                   {
                       PRINT_ERROR("failed to add varying, l%d,c%d-l%d,c%d", (yylsp[(1) - (4)]).first_line, (yylsp[(1) - (4)]).first_column, (yylsp[(4) - (4)]).last_line, (yylsp[(4) - (4)]).last_column);
                       YYERROR;
                   }
                   SAFE_DELETE((yyvsp[(2) - (4)].type));
                   SAFE_DELETE((yyvsp[(3) - (4)].decl_id));
               ;}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 844 "parser.y"
    {
                     if((yyvsp[(2) - (4)].type)->type->get_space_ano2())
                     {
                         // quickly hack it into a matrix array.
                         (yyvsp[(3) - (4)].decl_id)->src += "[2]";
                     }
                     (yyval.str) = new string();
                     *(yyval.str) = "attribute " + (yyvsp[(2) - (4)].type)->src + " " + (yyvsp[(3) - (4)].decl_id)->src + ";\n";
                     if(!append_declaration(*(yyvsp[(3) - (4)].decl_id), (yyvsp[(2) - (4)].type)->type, context::get_ctx()->attributes))
                     {
                         PRINT_ERROR("failed to add attribute, l%d,c%d-l%d,c%d", (yylsp[(1) - (4)]).first_line, (yylsp[(1) - (4)]).first_column, (yylsp[(4) - (4)]).last_line, (yylsp[(4) - (4)]).last_column);
                         YYERROR;
                     }
                     SAFE_DELETE((yyvsp[(2) - (4)].type));
                     SAFE_DELETE((yyvsp[(3) - (4)].decl_id));
                 ;}
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 863 "parser.y"
    {
              if((yyvsp[(2) - (4)].type)->type->get_space_ano2())
              {
                  // quickly hack it into a matrix array.
                  (yyvsp[(3) - (4)].decl_id)->src += "[2]";
              }
              (yyval.str) = new string();
              *(yyval.str) = "in " + (yyvsp[(2) - (4)].type)->src + " " + (yyvsp[(3) - (4)].decl_id)->src + ";\n";
              if(!append_declaration(*(yyvsp[(3) - (4)].decl_id), (yyvsp[(2) - (4)].type)->type, context::get_ctx()->ins))
              {
                  PRINT_ERROR("failed to add in, l%d,c%d-l%d,c%d", (yylsp[(1) - (4)]).first_line, (yylsp[(1) - (4)]).first_column, (yylsp[(4) - (4)]).last_line, (yylsp[(4) - (4)]).last_column);
                  YYERROR;
              }
              SAFE_DELETE((yyvsp[(2) - (4)].type));
              SAFE_DELETE((yyvsp[(3) - (4)].decl_id));
          ;}
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 882 "parser.y"
    {
               if((yyvsp[(2) - (4)].type)->type->get_space_ano2())
               {
                   // quickly hack it into a matrix array.
                   (yyvsp[(3) - (4)].decl_id)->src += "[2]";
               }
               (yyval.str) = new string();
               *(yyval.str) = "out " + (yyvsp[(2) - (4)].type)->src + " " + (yyvsp[(3) - (4)].decl_id)->src + ";\n";
               if(!append_declaration(*(yyvsp[(3) - (4)].decl_id), (yyvsp[(2) - (4)].type)->type, context::get_ctx()->outs))
               {
                   PRINT_ERROR("failed to add out, l%d,c%d-l%d,c%d", (yylsp[(1) - (4)]).first_line, (yylsp[(1) - (4)]).first_column, (yylsp[(4) - (4)]).last_line, (yylsp[(4) - (4)]).last_column);
                   YYERROR;
               }
               SAFE_DELETE((yyvsp[(2) - (4)].type));
               SAFE_DELETE((yyvsp[(3) - (4)].decl_id));
           ;}
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 902 "parser.y"
    {
                  (yyval.str) = new string();
                  if(*((yyvsp[(2) - (5)].type)->type) != *((yyvsp[(4) - (5)].expression)->type))
                  {
                      PRINT_ERROR("define type do not match, l%d,c%d-l%d,c%d", (yylsp[(1) - (5)]).first_line, (yylsp[(1) - (5)]).first_column, (yylsp[(4) - (5)]).last_line, (yylsp[(4) - (5)]).last_column);
                      YYERROR;
                  }
                  context::get_ctx()->defines.push_back(cx_define((yyvsp[(2) - (5)].type)->type, *(yyvsp[(3) - (5)].str), (yyvsp[(4) - (5)].expression)->src));
                  SAFE_DELETE((yyvsp[(2) - (5)].type));
                  SAFE_DELETE((yyvsp[(3) - (5)].str));
                  SAFE_DELETE((yyvsp[(4) - (5)].expression));
              ;}
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 917 "parser.y"
    {
              (yyval.decl_id) = new gs_id_decl(*(yyvsp[(1) - (1)].str));
              (yyval.decl_id)->src = *(yyvsp[(1) - (1)].str);
              SAFE_DELETE((yyvsp[(1) - (1)].str));
          ;}
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 923 "parser.y"
    {
              (yyval.decl_id) = (yyvsp[(1) - (3)].decl_id);
              (yyval.decl_id)->has_init = true;
              gs_expression *e = (yyvsp[(3) - (3)].expression);
              (yyval.decl_id)->init_expr = *e;
              (yyval.decl_id)->src = (yyvsp[(1) - (3)].decl_id)->src + '=' + (yyvsp[(3) - (3)].expression)->src;
              SAFE_DELETE((yyvsp[(3) - (3)].expression));
          ;}
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 934 "parser.y"
    {
             shared_ptr<t_ano_type> t = context::get_ctx()->get_variable_type(*(yyvsp[(1) - (1)].str));
             if(t.get() == 0)
             {
                 PRINT_ERROR("undefined variable %s, l%d,c%d-l%d,c%d", (yyvsp[(1) - (1)].str)->c_str(), (yylsp[(1) - (1)]).first_line, (yylsp[(1) - (1)]).first_column, (yylsp[(1) - (1)]).last_line, (yylsp[(1) - (1)]).last_column);
                 YYERROR;
             }
             else
             {
                 (yyval.expression) = new gs_expression(t);
                 (yyval.expression)->src = *(yyvsp[(1) - (1)].str);
                 SAFE_DELETE((yyvsp[(1) - (1)].str));
             }
         ;}
    break;

  case 94:

/* Line 1455 of yacc.c  */
#line 948 "parser.y"
    { (yyval.expression) = (yyvsp[(1) - (1)].expression); ;}
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 950 "parser.y"
    {
             (yyval.expression) = (yyvsp[(2) - (3)].expression);
             (yyval.expression)->src = "(" + (yyvsp[(2) - (3)].expression)->src + ")"
         ;}
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 955 "parser.y"
    {
             if(!context::get_ctx()->check_type_cast((yyvsp[(1) - (4)].type)->type, (yyvsp[(3) - (4)].arglist)->get_type_list()))
             {
                 PRINT_ERROR("cannot type cast %s, l%d,c%d-l%d,c%d\n", (yyvsp[(1) - (4)].type)->src.c_str(), (yylsp[(1) - (4)]).first_line, (yylsp[(1) - (4)]).first_column, (yylsp[(4) - (4)]).last_line, (yylsp[(4) - (4)]).last_column);
                 YYERROR;
             }
             (yyval.expression) = new gs_expression((yyvsp[(1) - (4)].type)->type);
             (yyval.expression)->src = (yyvsp[(1) - (4)].type)->src + "(" + (yyvsp[(3) - (4)].arglist)->src + ")";
             PRINT_DEBUG("type_cast to %s\n", (yyvsp[(1) - (4)].type)->src.c_str());
             SAFE_DELETE((yyvsp[(1) - (4)].type));
             SAFE_DELETE((yyvsp[(3) - (4)].arglist));
         ;}
    break;

  case 97:

/* Line 1455 of yacc.c  */
#line 968 "parser.y"
    {
             shared_ptr<t_ano_type> rt = 
                 context::get_ctx()->check_function(*(yyvsp[(1) - (4)].str), (yyvsp[(3) - (4)].arglist)->get_type_list());
             if(!rt.get())
             {
                 PRINT_ERROR("unknown function call %s, l%d,c%d-l%d,c%d", (yyvsp[(1) - (4)].str)->c_str(), (yylsp[(1) - (4)]).first_line, (yylsp[(1) - (4)]).first_column, (yylsp[(4) - (4)]).last_line, (yylsp[(4) - (4)]).last_column);
                 YYERROR;
             }
             (yyval.expression) = new gs_expression(rt);
             (yyval.expression)->src = *(yyvsp[(1) - (4)].str) + "(" + (yyvsp[(3) - (4)].arglist)->src + ")";
             PRINT_DEBUG("%s(%s)\n", (yyvsp[(1) - (4)].str)->c_str(), (yyvsp[(3) - (4)].arglist)->src.c_str());
             SAFE_DELETE((yyvsp[(1) - (4)].str));
             SAFE_DELETE((yyvsp[(3) - (4)].arglist));
         ;}
    break;

  case 98:

/* Line 1455 of yacc.c  */
#line 983 "parser.y"
    {
             if(*((yyvsp[(1) - (3)].expression)->type) != *((yyvsp[(3) - (3)].expression)->type))
             {
                 PRINT_ERROR("type different assign, l%d,c%d-l%d,c%d", (yylsp[(1) - (3)]).first_line, (yylsp[(1) - (3)]).first_column, (yylsp[(3) - (3)]).last_line, (yylsp[(3) - (3)]).last_column);
                 YYERROR;
             }
             (yyval.expression) = new gs_expression((yyvsp[(1) - (3)].expression)->type);
             (yyval.expression)->src = (yyvsp[(1) - (3)].expression)->src + "=" + (yyvsp[(3) - (3)].expression)->src;
             PRINT_DEBUG("%s = %s\n", (yyvsp[(1) - (3)].expression)->src.c_str(), (yyvsp[(3) - (3)].expression)->src.c_str());
             SAFE_DELETE((yyvsp[(1) - (3)].expression));
             SAFE_DELETE((yyvsp[(3) - (3)].expression));
         ;}
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 996 "parser.y"
    {
             vector<shared_ptr<t_ano_type>> typelist;
             typelist.push_back((yyvsp[(1) - (3)].expression)->type);
             typelist.push_back((yyvsp[(3) - (3)].expression)->type);
             string op("+");
             shared_ptr<t_ano_type> rt = 
                 context::get_ctx()->check_function(op, typelist);
             if(!rt.get())
             {
                 PRINT_ERROR("type check failed, l%d,c%d-l%d,c%d", (yylsp[(1) - (3)]).first_line, (yylsp[(1) - (3)]).first_column, (yylsp[(3) - (3)]).last_line, (yylsp[(3) - (3)]).last_column);
                 YYERROR;
             }
             (yyval.expression) = new gs_expression(rt);
             (yyval.expression)->src = (yyvsp[(1) - (3)].expression)->src + "+" + (yyvsp[(3) - (3)].expression)->src;
             PRINT_DEBUG("%s + %s\n", (yyvsp[(1) - (3)].expression)->src.c_str(), (yyvsp[(3) - (3)].expression)->src.c_str());
             SAFE_DELETE((yyvsp[(1) - (3)].expression));
             SAFE_DELETE((yyvsp[(3) - (3)].expression));
         ;}
    break;

  case 100:

/* Line 1455 of yacc.c  */
#line 1015 "parser.y"
    {
             vector<shared_ptr<t_ano_type>> typelist;
             typelist.push_back((yyvsp[(1) - (3)].expression)->type);
             typelist.push_back((yyvsp[(3) - (3)].expression)->type);
             string op("-");
             shared_ptr<t_ano_type> rt = 
                 context::get_ctx()->check_function(op, typelist);
             if(!rt.get())
             {
                 PRINT_ERROR("type check failed, l%d,c%d-l%d,c%d", (yylsp[(1) - (3)]).first_line, (yylsp[(1) - (3)]).first_column, (yylsp[(3) - (3)]).last_line, (yylsp[(3) - (3)]).last_column);
                 YYERROR;
             }
             (yyval.expression) = new gs_expression(rt);
             (yyval.expression)->src = (yyvsp[(1) - (3)].expression)->src + "-" + (yyvsp[(3) - (3)].expression)->src;
             PRINT_DEBUG("%s - %s\n", (yyvsp[(1) - (3)].expression)->src.c_str(), (yyvsp[(3) - (3)].expression)->src.c_str());
             SAFE_DELETE((yyvsp[(1) - (3)].expression));
             SAFE_DELETE((yyvsp[(3) - (3)].expression));
         ;}
    break;

  case 101:

/* Line 1455 of yacc.c  */
#line 1034 "parser.y"
    {
             vector<shared_ptr<t_ano_type>> typelist;
             typelist.push_back((yyvsp[(1) - (3)].expression)->type);
             typelist.push_back((yyvsp[(3) - (3)].expression)->type);
             string op("*");
             shared_ptr<t_ano_type> rt = 
                 context::get_ctx()->check_function(op, typelist);
             if(!rt.get())
             {
                 PRINT_ERROR("type check failed, l%d,c%d-l%d,c%d", (yylsp[(1) - (3)]).first_line, (yylsp[(1) - (3)]).first_column, (yylsp[(3) - (3)]).last_line, (yylsp[(3) - (3)]).last_column);
                 YYERROR;
             }
             (yyval.expression) = new gs_expression(rt);
             (yyval.expression)->src = (yyvsp[(1) - (3)].expression)->src + "*" + (yyvsp[(3) - (3)].expression)->src;
             PRINT_DEBUG("%s * %s\n", (yyvsp[(1) - (3)].expression)->src.c_str(), (yyvsp[(3) - (3)].expression)->src.c_str());
             SAFE_DELETE((yyvsp[(1) - (3)].expression));
             SAFE_DELETE((yyvsp[(3) - (3)].expression));
         ;}
    break;

  case 102:

/* Line 1455 of yacc.c  */
#line 1053 "parser.y"
    {
             vector<shared_ptr<t_ano_type>> typelist;
             typelist.push_back((yyvsp[(1) - (3)].expression)->type);
             typelist.push_back((yyvsp[(3) - (3)].expression)->type);
             string op("/");
             shared_ptr<t_ano_type> rt = 
                 context::get_ctx()->check_function(op, typelist);
             if(!rt.get())
             {
                 PRINT_ERROR("type check failed, l%d,c%d-l%d,c%d", (yylsp[(1) - (3)]).first_line, (yylsp[(1) - (3)]).first_column, (yylsp[(3) - (3)]).last_line, (yylsp[(3) - (3)]).last_column);
                 YYERROR;
             }
             (yyval.expression) = new gs_expression(rt);
             (yyval.expression)->src = (yyvsp[(1) - (3)].expression)->src + "/" + (yyvsp[(3) - (3)].expression)->src;
             PRINT_DEBUG("%s / %s\n", (yyvsp[(1) - (3)].expression)->src.c_str(), (yyvsp[(3) - (3)].expression)->src.c_str());
             SAFE_DELETE((yyvsp[(1) - (3)].expression));
             SAFE_DELETE((yyvsp[(3) - (3)].expression));
         ;}
    break;

  case 103:

/* Line 1455 of yacc.c  */
#line 1072 "parser.y"
    {
             (yyval.expression) = (yyvsp[(2) - (2)].expression);
             (yyval.expression)->src = "-" + (yyvsp[(2) - (2)].expression)->src;
             PRINT_DEBUG("- %s\n", (yyvsp[(2) - (2)].expression)->src.c_str());
         ;}
    break;

  case 104:

/* Line 1455 of yacc.c  */
#line 1078 "parser.y"
    {
             if((yyvsp[(5) - (6)].expression)->type->builtin_type != "vec2")
             {
                 PRINT_ERROR("textcoord argument %s do not have built in type vec2, l%d,c%d-l%d,c%d\n", (yyvsp[(5) - (6)].expression)->src.c_str(), (yylsp[(5) - (6)]).first_line, (yylsp[(5) - (6)]).first_column, (yylsp[(5) - (6)]).last_line, (yylsp[(5) - (6)]).last_column);
                 YYERROR;
             }
             if(!(yyvsp[(3) - (6)].expression)->type->is_sampler())
             {
                 PRINT_ERROR ("cannot find sampler %s, l%d,c%d-l%d,c%d", (yyvsp[(3) - (6)].expression)->src.c_str(), (yylsp[(3) - (6)]).first_line, (yylsp[(3) - (6)]).first_column, (yylsp[(3) - (6)]).last_line, (yylsp[(3) - (6)]).last_column);
                 YYERROR;
             }
             (yyval.expression) = new gs_expression((yyvsp[(3) - (6)].expression)->type->get_member_type());
             (yyval.expression)->src = "texture2D(" + (yyvsp[(3) - (6)].expression)->src + "," + (yyvsp[(5) - (6)].expression)->src + ")";
             if(!(yyvsp[(3) - (6)].expression)->type->get_member_type()->get_member_type().get())
             {
                 (yyval.expression)->src += ".x"; //hack for non tuple texture.
             }
             PRINT_DEBUG("texture2D(%s,%s)\n", (yyvsp[(3) - (6)].expression)->src.c_str(), (yyvsp[(5) - (6)].expression)->src.c_str());
             SAFE_DELETE((yyvsp[(3) - (6)].expression));
             SAFE_DELETE((yyvsp[(5) - (6)].expression));
         ;}
    break;

  case 105:

/* Line 1455 of yacc.c  */
#line 1100 "parser.y"
    {
             if(*(yyvsp[(3) - (3)].str) == "x" || *(yyvsp[(3) - (3)].str) == "y" || *(yyvsp[(3) - (3)].str) == "z" || *(yyvsp[(3) - (3)].str) == "w" || 
                 *(yyvsp[(3) - (3)].str) == "a" || *(yyvsp[(3) - (3)].str) == "r" || *(yyvsp[(3) - (3)].str) == "g" || *(yyvsp[(3) - (3)].str) == "b")
             {
                 if(!(yyvsp[(1) - (3)].expression)->type->get_member_type().get())
                 {
                     PRINT_ERROR ("%s is not tuple type, l%d,c%d-l%d,c%d", (yyvsp[(3) - (3)].str)->c_str(), (yylsp[(3) - (3)]).first_line, (yylsp[(3) - (3)]).first_column, (yylsp[(3) - (3)]).last_line, (yylsp[(3) - (3)]).last_column);
                     YYERROR;
                 }
                 (yyval.expression) = new gs_expression((yyvsp[(1) - (3)].expression)->type->get_member_type());
                 (yyval.expression)->src = (yyvsp[(1) - (3)].expression)->src + '.' + *(yyvsp[(3) - (3)].str);
             }
             else
             {
                 PRINT_ERROR ("only support single member operation for vec type %s, l%d,c%d-l%d,c%d", (yyvsp[(3) - (3)].str)->c_str(), (yylsp[(3) - (3)]).first_line, (yylsp[(3) - (3)]).first_column, (yylsp[(3) - (3)]).last_line, (yylsp[(3) - (3)]).last_column);
                 YYERROR;
             }
             SAFE_DELETE((yyvsp[(1) - (3)].expression));
             SAFE_DELETE((yyvsp[(3) - (3)].str));
         ;}
    break;

  case 106:

/* Line 1455 of yacc.c  */
#line 1123 "parser.y"
    {/* empty */
             (yyval.arglist) = new gs_arglist();
         ;}
    break;

  case 107:

/* Line 1455 of yacc.c  */
#line 1127 "parser.y"
    {
             (yyval.arglist) = new gs_arglist();
             (yyval.arglist)->src = (yyvsp[(1) - (1)].expression)->src;
             (yyval.arglist)->list.push_back(*(yyvsp[(1) - (1)].expression));
             SAFE_DELETE((yyvsp[(1) - (1)].expression));
         ;}
    break;

  case 108:

/* Line 1455 of yacc.c  */
#line 1134 "parser.y"
    {
             (yyval.arglist) = (yyvsp[(1) - (3)].arglist);
             (yyval.arglist)->src += ',' + (yyvsp[(3) - (3)].expression)->src;
             (yyval.arglist)->list.push_back(*(yyvsp[(3) - (3)].expression));
             SAFE_DELETE((yyvsp[(3) - (3)].expression));
         ;}
    break;

  case 109:

/* Line 1455 of yacc.c  */
#line 1143 "parser.y"
    {
                 (yyval.expression) = new gs_expression(shared_ptr<t_ano_type>(new t_ano_type("real", "int")));
                 (yyval.expression)->src = *(yyvsp[(1) - (1)].str);
                 SAFE_DELETE((yyvsp[(1) - (1)].str));
             ;}
    break;

  case 110:

/* Line 1455 of yacc.c  */
#line 1149 "parser.y"
    {
                 (yyval.expression) = new gs_expression(shared_ptr<t_ano_type>(new t_ano_type("real", "float")));
                 (yyval.expression)->src = *(yyvsp[(1) - (1)].str);
                 SAFE_DELETE((yyvsp[(1) - (1)].str));
             ;}
    break;

  case 111:

/* Line 1455 of yacc.c  */
#line 1155 "parser.y"
    {
                 (yyval.expression) = new gs_expression(shared_ptr<t_ano_type>(new t_ano_type("bool", "bool")));
                 (yyval.expression)->src = *(yyvsp[(1) - (1)].str);
                 SAFE_DELETE((yyvsp[(1) - (1)].str));
             ;}
    break;

  case 112:

/* Line 1455 of yacc.c  */
#line 1163 "parser.y"
    { 
          (yyval.type) = new gs_type();
          (yyval.type)->type = shared_ptr<t_ano_type>(new t_ano_type(*(yyvsp[(1) - (1)].str), *(yyvsp[(1) - (1)].str)));
          (yyval.type)->src = *(yyvsp[(1) - (1)].str);
          SAFE_DELETE((yyvsp[(1) - (1)].str));
      ;}
    break;

  case 113:

/* Line 1455 of yacc.c  */
#line 1170 "parser.y"
    {
          (yyval.type) = new gs_type();
          string tname = *(yyvsp[(1) - (1)].str);
          (yyval.type)->type = context::get_ctx()->deduct_type(tname);
          if(!(yyval.type)->type.get())
          {
              YYERROR;
          }
          (yyval.type)->src = (yyval.type)->type->builtin_type;
          SAFE_DELETE((yyvsp[(1) - (1)].str));  
      ;}
    break;

  case 114:

/* Line 1455 of yacc.c  */
#line 1182 "parser.y"
    {
          (yyval.type) = new gs_type();
          string tname = *(yyvsp[(1) - (4)].str);
          (yyval.type)->type = context::get_ctx()->deduct_type(tname, (yyvsp[(3) - (4)].dimen_ano));
          if(!(yyval.type)->type.get())
          {
              YYERROR;
          }
          (yyval.type)->src = (yyval.type)->type->builtin_type;
          SAFE_DELETE((yyvsp[(1) - (4)].str));  
      ;}
    break;

  case 115:

/* Line 1455 of yacc.c  */
#line 1194 "parser.y"
    {
          (yyval.type) = new gs_type();
          string tname = *(yyvsp[(1) - (4)].str);
          (yyval.type)->type = context::get_ctx()->deduct_type(tname, (yyvsp[(3) - (4)].space_ano));
          if(!(yyval.type)->type.get())
          {
              YYERROR;
          }
          (yyval.type)->src = (yyval.type)->type->builtin_type;
          SAFE_DELETE((yyvsp[(1) - (4)].str));  
      ;}
    break;

  case 116:

/* Line 1455 of yacc.c  */
#line 1206 "parser.y"
    {
          (yyval.type) = new gs_type();
          string tname = *(yyvsp[(1) - (6)].str);
          (yyval.type)->type = context::get_ctx()->deduct_type(tname, (yyvsp[(3) - (6)].space_ano), (yyvsp[(5) - (6)].space_ano));
          if(!(yyval.type)->type.get())
          {
              YYERROR;
          }
          (yyval.type)->src = (yyval.type)->type->builtin_type;
          SAFE_DELETE((yyvsp[(1) - (6)].str));  
      ;}
    break;

  case 117:

/* Line 1455 of yacc.c  */
#line 1218 "parser.y"
    {
          (yyval.type) = new gs_type();
          shared_ptr<t_sampler_type> st = shared_ptr<t_sampler_type>(new t_sampler_type("sampler2D", "sampler2D"));
          st->member_type = (yyvsp[(3) - (4)].type)->type;
          (yyval.type)->type = st;
          (yyval.type)->src = "sampler2D";
          PRINT_DEBUG("sampler2D<%s>\n", (yyvsp[(3) - (4)].type)->src.c_str());
          SAFE_DELETE((yyvsp[(3) - (4)].type)); 
      ;}
    break;

  case 118:

/* Line 1455 of yacc.c  */
#line 1228 "parser.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 119:

/* Line 1455 of yacc.c  */
#line 1229 "parser.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 120:

/* Line 1455 of yacc.c  */
#line 1230 "parser.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 121:

/* Line 1455 of yacc.c  */
#line 1231 "parser.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 122:

/* Line 1455 of yacc.c  */
#line 1234 "parser.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 123:

/* Line 1455 of yacc.c  */
#line 1235 "parser.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 124:

/* Line 1455 of yacc.c  */
#line 1236 "parser.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 125:

/* Line 1455 of yacc.c  */
#line 1237 "parser.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 126:

/* Line 1455 of yacc.c  */
#line 1240 "parser.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 127:

/* Line 1455 of yacc.c  */
#line 1243 "parser.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 128:

/* Line 1455 of yacc.c  */
#line 1246 "parser.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 129:

/* Line 1455 of yacc.c  */
#line 1247 "parser.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 130:

/* Line 1455 of yacc.c  */
#line 1248 "parser.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 131:

/* Line 1455 of yacc.c  */
#line 1249 "parser.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 132:

/* Line 1455 of yacc.c  */
#line 1250 "parser.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;



/* Line 1455 of yacc.c  */
#line 3570 "D:/nprojects/safegi/base/libs/sparser/parser.cpp"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

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

  yyerror_range[0] = yylloc;

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
		      yytoken, &yylval, &yylloc);
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

  yyerror_range[0] = yylsp[1-yylen];
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

      yyerror_range[0] = *yylsp;
      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;

  yyerror_range[1] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, (yyerror_range - 1), 2);
  *++yylsp = yyloc;

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

#if !defined(yyoverflow) || YYERROR_VERBOSE
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
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval, &yylloc);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, yylsp);
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



/* Line 1675 of yacc.c  */
#line 1253 "parser.y"


          /*--------------------------------------------------------*/
          /* Additional C code */
          /* Error processor for yyparse */
#include <stdio.h>
          void yyerror (char const *s)       /* called by yyparse on error */
      {
          fprintf(stderr, "syntax error in some where\n");
      }


