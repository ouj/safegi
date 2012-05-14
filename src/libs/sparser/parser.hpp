
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
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

/* Line 1676 of yacc.c  */
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




/* Line 1676 of yacc.c  */
#line 123 "D:/nprojects/safegi/base/libs/sparser/parser.hpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

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

extern YYLTYPE yylloc;

