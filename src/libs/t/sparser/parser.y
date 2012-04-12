/* Require bison 2.3 or later */
%require "2.3"

    /* add debug output code to generated parser. disable this for release
    * versions. */
    %debug

    /* write out a header file containing the token defines */
    %defines


    %{
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

        %}

%right  '='
    %left  T_EQ T_LE T_GE
    %left  '>' '<'
    %left  '+' '-'
    %left  '*' '/'
    %left UMINUS
    %left  '.'

    %token T_VARY T_UNIF T_ATTR
    %token <str> T_ID
    %token <str> T_LT_INT T_LT_FLT T_LT_BLN

    %token T_IF T_ELSE T_ELSE_IF T_FOR T_WHILE T_DO
    %token T_RETURN
    %token T_IN T_OUT T_INOUT

    %token T_DEFINE
    %token T_TYPEMAP
    %token T_DEF_SPACE_ANO
    %token T_DEF_DIM_ANO
    %token T_OPERATOR

    %token <str> T_VEC T_IVEC T_BVEC T_UVEC
    %token <str> T_VOID T_INT T_FLOAT T_BOOL T_UINT
    %token <str> T_MAT4
    %token <str> T_SAMPLER2D_TYPE

    %token T_GENERIC_SPACE_NOTATION T_GENERIC_DIMEN_NOTATION
    %token T_RESERVED

    %token <space_ano> T_SPACE_ANO
    %token <dimen_ano> T_DIMEN_ANO
    %token <str> T_BASIC_TYPE

    %token T_BUILT_IN T_CONVERNTION 
    %token <str> T_RAW_CODE
    %token <str> T_BUILT_IN_SIG
    %token T_TEXTURE2D

    %union
{
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

};

%type <str>            program
    %type <str>            component
    %type <str>            uniform_decl
    %type <str>            varying_decl
    %type <str>            attribute_decl
    %type <str>            in_decl
    %type <str>            out_decl
    %type <str>            func_decl
    %type <str>            func_def
    %type <str>             define_decl
    %type <str>            statements
    %type <str>            statement
    %type <str>            block
    %type <str>            local_decl
    %type <type>            type
    %type <str>            builtin_type
    %type <str>            scale_type
    %type <str>            tuple_type
    %type <str>            mat_type
    %type <str>            sampler_type

    %type <expression>      expr
    %type <expression>      literal_num
    %type <expression>      cond_expr

    %type <gen_ano_type>         generic_ano_type
    %type <gen_ano_paralist>       generic_ano_paralist  
    %type <gen_ano_para>    generic_ano_para
    %type <paralist>        para_list
    %type <arglist>         arg_list
    %type <anolist>         ano_list
    %type <decl_id>         decl_id
    %type <sig_list>        def_signature_list

    %destructor { SAFE_DELETE($$); } <src> <node> <type> <expression> <paralist> <arglist> <idlist> <anolist> <decl_id> <ano_notation>
    %destructor {
        if(!is_predef)
        {
            if(!context::get_ctx()->built_in_code.empty())
                ouput_src = context::get_ctx()->built_in_code;

            ouput_src += *$$;
            if(g_info)
            {
                g_info->uniforms = context::get_ctx()->uniforms;
                g_info->varyings = context::get_ctx()->varyings;
                g_info->attributes = context::get_ctx()->attributes;
                g_info->samplers = context::get_ctx()->samplers;
            }
            context::get_ctx()->cleanup();
        }
        SAFE_DELETE($$);
} program

    %initial-action { ouput_src.clear(); if(is_predef) context::get_ctx()->cleanup(); }

%%

program: { $$ = new string();}
| program component
{
    $$ = $1;
    if($2)
    {
        *$$ += *$2;
        SAFE_DELETE($2);
    }
}
;

component: uniform_decl { $$ = $1; }
| varying_decl { $$ = $1; }
| attribute_decl { $$ = $1; }
| in_decl { $$ = $1; }
| out_decl { $$ = $1; }
| define_decl { $$ = $1; }
| func_decl { $$ = $1; }
| func_def { $$ = $1; }
| def_space_ano { $$ = 0; }
| def_dim_ano { $$ = 0; }
| typemap_decl { $$ = 0; }
| call_convention { $$ = 0; }
| ano_call_convention { $$ = 0; }
| operater_convention { $$ = 0; }
| ano_operater_convention{ $$ = 0; }
| built_in_func { $$ = 0; }
| built_in_ano_func { $$ = 0; }
;

para_list: 
{ /* empty */
    $$ = new gs_paralist();
}
| type T_ID 
{
    $$ = new gs_paralist();
    $$->list.push_back(t_var($1->type, *$2));
    $$->src = $1->src + " " + *$2;
    SAFE_DELETE($1);
    SAFE_DELETE($2);
}
| para_list ',' type T_ID
{
    $$ = $1;
    $$->list.push_back(t_var($3->type, *$4));
    $$->src += ',' + $3->src + " " + *$4;
    SAFE_DELETE($3);
    SAFE_DELETE($4);
}
;

func_decl: type T_ID '(' para_list ')' ';' 
           {
               $$ = new string();
               *$$ = $1->src + " " + *$2 + '(' + $4->src + ");\n";

               string func_name = *$2;
               shared_ptr<t_ano_type> return_type = $1->type;
               vector<shared_ptr<t_ano_type>> para_typelist = $4->get_type_list();

               context::get_ctx()->functions.push_back(cx_function($1->type, *$2, $4->get_type_list()));

               SAFE_DELETE($1);
               SAFE_DELETE($2);
               SAFE_DELETE($4);
               PRINT_DEBUG("DECLARE FUNCTION: %s\n", $$->c_str());
           }
           ;

func_def: type T_ID '(' para_list ')'
          { 
              context::get_ctx()->push_context();
              vector<t_var> &list = $4->list;
              for(unsigned int i = 0; i < list.size(); i++)
              {
                  t_var &var = list[i];
                  context::get_ctx()->variables[var.name] = var;
              }
              context::get_ctx()->func_rtype = $1->type;
          } 
          '{' statements '}'
          {
              context::get_ctx()->pop_context();
              $$ = new string();
              *$$ = $1->src + " " + *$2 + '(' + $4->src + ")\n" + "{\n" + *$8 + "}\n";

              context::get_ctx()->functions.push_back(cx_function($1->type, *$2, $4->get_type_list()));

              SAFE_DELETE($1);
              SAFE_DELETE($2);
              SAFE_DELETE($4);
              SAFE_DELETE($8);
              PRINT_DEBUG("DEFINE FUNCTION: %s\n", $$->c_str());
          }
          ;


call_convention : T_CONVERNTION type T_ID '(' para_list ')' ';'
                  {
                      context::get_ctx()->functions.push_back(cx_function($2->type, *$3, $5->get_type_list()));
                      PRINT_DEBUG("CALL_CONVENTION: %s %s ( %s );\n", $2->src.c_str(), $3->c_str(), $5->src.c_str());
                      SAFE_DELETE($2);
                      SAFE_DELETE($3);
                      SAFE_DELETE($5);
                  } 
                  ;

built_in_func : T_BUILT_IN type T_ID '(' para_list ')' T_BUILT_IN_SIG T_RAW_CODE
                {
                    context::get_ctx()->bin_functions.push_back(cx_bin_function($2->type, *$3, $5->list, *$7, *$8));
                    PRINT_DEBUG("BUILT_IN: %s %s ( %s ) - %s\n", $2->src.c_str(), $3->c_str(), $5->src.c_str(), $7->c_str());
                    SAFE_DELETE($2);
                    SAFE_DELETE($3);
                    SAFE_DELETE($5);
                    SAFE_DELETE($7);
                    SAFE_DELETE($8);
                } 
                ;

operater_convention : T_CONVERNTION type T_OPERATOR '+' '(' type ',' type  ')' ';'
                      {
                          vector<shared_ptr<t_ano_type>> typelist;
                          typelist.push_back($6->type);
                          typelist.push_back($8->type);
                          context::get_ctx()->functions.push_back(cx_function($2->type, "+", typelist));
                          //// Exchange
                          //shared_ptr<t_ano_type> t = typelist[1];
                          //typelist[1] = typelist[0];
                          //typelist[0] = t;
                          //context::get_ctx()->functions.push_back(cx_function($2->type, "+", typelist));
                          PRINT_DEBUG("OPER_CONV: %s operator+ ( %s,  %s);\n", $2->src.c_str(), $6->src.c_str(), $8->src.c_str());
                          SAFE_DELETE($2);
                          SAFE_DELETE($6);
                          SAFE_DELETE($8);
                      } 
                      | T_CONVERNTION type T_OPERATOR '-' '(' type ',' type  ')' ';'
                      {
                          vector<shared_ptr<t_ano_type>> typelist;
                          typelist.push_back($6->type);
                          typelist.push_back($8->type);
                          context::get_ctx()->functions.push_back(cx_function($2->type, "-", typelist));
                          PRINT_DEBUG("OPER_CONV: %s operator- ( %s,  %s);\n", $2->src.c_str(), $6->src.c_str(), $8->src.c_str());
                          SAFE_DELETE($2);
                          SAFE_DELETE($6);
                          SAFE_DELETE($8);
                      } 
                      | T_CONVERNTION type T_OPERATOR '*' '(' type ',' type  ')' ';'
                      {
                          vector<shared_ptr<t_ano_type>> typelist;
                          typelist.push_back($6->type);
                          typelist.push_back($8->type);
                          context::get_ctx()->functions.push_back(cx_function($2->type, "*", typelist));
                          //// Exchange
                          //shared_ptr<t_ano_type> t = typelist[1];
                          //typelist[1] = typelist[0];
                          //typelist[0] = t;
                          //context::get_ctx()->functions.push_back(cx_function($2->type, "*", typelist));
                          PRINT_DEBUG("OPER_CONV: %s operator *( %s,  %s);\n", $2->src.c_str(), $6->src.c_str(), $8->src.c_str());
                          SAFE_DELETE($2);
                          SAFE_DELETE($6);
                          SAFE_DELETE($8);
                      } 
                      | T_CONVERNTION type T_OPERATOR '/' '(' type ',' type  ')' ';'
                      {
                          vector<shared_ptr<t_ano_type>> typelist;
                          typelist.push_back($6->type);
                          typelist.push_back($8->type);
                          context::get_ctx()->functions.push_back(cx_function($2->type, "/", typelist));
                          PRINT_DEBUG("OPER_CONV: %s operator/ ( %s,  %s);\n", $2->src.c_str(), $6->src.c_str(), $8->src.c_str());
                          SAFE_DELETE($2);
                          SAFE_DELETE($6);
                          SAFE_DELETE($8);
                      } 
                      ;

ano_operater_convention : T_CONVERNTION '<' ano_list '>' generic_ano_type T_OPERATOR '+' '(' generic_ano_para ',' generic_ano_para  ')' ';'
                          {
                              vector<string> ano_list = $3->list;
                              cx_generic_ano_type ret_type = *$5;
                              vector<cx_generic_ano_para> list;
                              list.push_back(*$9);
                              list.push_back(*$11);
                              context::get_ctx()->ano_functions.push_back(cx_ano_function("+", ano_list, ret_type, list));
                              PRINT_DEBUG("OPER_CONV: %s < %s > operator+ ( %s,  %s);\n", $3->src.c_str(), $5->name.c_str(), $9->name.c_str(), $11->name.c_str());
                              SAFE_DELETE($3);
                              SAFE_DELETE($5);
                              SAFE_DELETE($9);
                              SAFE_DELETE($11);
                          }
                          | T_CONVERNTION '<' ano_list '>' generic_ano_type T_OPERATOR '-' '(' generic_ano_para ',' generic_ano_para  ')' ';'
                          {
                              vector<string> ano_list = $3->list;
                              cx_generic_ano_type ret_type = *$5;
                              vector<cx_generic_ano_para> list;
                              list.push_back(*$9);
                              list.push_back(*$11);
                              context::get_ctx()->ano_functions.push_back(cx_ano_function("-", ano_list, ret_type, list));
                              PRINT_DEBUG("OPER_CONV: %s < %s > operator- ( %s,  %s);\n", $3->src.c_str(), $5->name.c_str(), $9->name.c_str(), $11->name.c_str());
                              SAFE_DELETE($3);
                              SAFE_DELETE($5);
                              SAFE_DELETE($9);
                              SAFE_DELETE($11);
                          }
                          | T_CONVERNTION '<' ano_list '>' generic_ano_type T_OPERATOR '*' '(' generic_ano_para ',' generic_ano_para  ')' ';'
                          {
                              vector<string> ano_list = $3->list;
                              cx_generic_ano_type ret_type = *$5;
                              vector<cx_generic_ano_para> list;
                              list.push_back(*$9);
                              list.push_back(*$11);
                              context::get_ctx()->ano_functions.push_back(cx_ano_function("*", ano_list, ret_type, list));
                              PRINT_DEBUG("OPER_CONV: %s < %s > operator* ( %s,  %s);\n", $3->src.c_str(), $5->name.c_str(), $9->name.c_str(), $11->name.c_str());
                              SAFE_DELETE($3);
                              SAFE_DELETE($5);
                              SAFE_DELETE($9);
                              SAFE_DELETE($11);
                          }
                          | T_CONVERNTION '<' ano_list '>' generic_ano_type T_OPERATOR '/' '(' generic_ano_para ',' generic_ano_para  ')' ';'
                          {
                              vector<string> ano_list = $3->list;
                              cx_generic_ano_type ret_type = *$5;
                              vector<cx_generic_ano_para> list;
                              list.push_back(*$9);
                              list.push_back(*$11);
                              context::get_ctx()->ano_functions.push_back(cx_ano_function("/", ano_list, ret_type, list));
                              PRINT_DEBUG("OPER_CONV: %s < %s > operator/ ( %s,  %s);", $3->src.c_str(), $5->name.c_str(), $9->name.c_str(), $11->name.c_str());
                              SAFE_DELETE($3);
                              SAFE_DELETE($5);
                              SAFE_DELETE($9);
                              SAFE_DELETE($11);
                          }
                          ;

generic_ano_type:    T_BASIC_TYPE
                     {
                         $$ = new cx_generic_ano_type(*$1);
                         SAFE_DELETE($1);              
                     }
                     | T_BASIC_TYPE   '<' T_ID '>'
                     {
                         $$ = new cx_generic_ano_type(*$1, *$3);
                         SAFE_DELETE($1);
                         SAFE_DELETE($3);
                     }
                     | T_BASIC_TYPE  '<' T_ID ',' T_ID '>'
                     {
                         $$ = new cx_generic_ano_type(*$1, *$3, *$5);
                         SAFE_DELETE($1);
                         SAFE_DELETE($3);
                         SAFE_DELETE($5);
                     }
                     | T_BASIC_TYPE  '<' T_ID '*' T_ID '>'
                     {
                         $$ = new cx_generic_ano_type(*$1, *$3, *$5, cx_generic_ano_type::MUL);
                         SAFE_DELETE($1);
                         SAFE_DELETE($3);
                         SAFE_DELETE($5);
                     }
                     | T_BASIC_TYPE  '<' T_ID '/' T_ID '>'
                     {
                         $$ = new cx_generic_ano_type(*$1, *$3, *$5, cx_generic_ano_type::DIV);
                         SAFE_DELETE($1);
                         SAFE_DELETE($3);
                         SAFE_DELETE($5);
                     }                    
                     | T_BASIC_TYPE  '<' '#' T_ID '>'
                     {
                         $$ = new cx_generic_ano_type(*$1, *$4, "", cx_generic_ano_type::SQRT);
                         SAFE_DELETE($1);
                         SAFE_DELETE($4);
                     };

generic_ano_para : generic_ano_type T_ID
                   {
                       $$ = new cx_generic_ano_para(*$1, *$2);
                       SAFE_DELETE($1);
                       SAFE_DELETE($2);
                   }
                   | generic_ano_type
                   {
                       $$ = new cx_generic_ano_para(*$1, "");
                       SAFE_DELETE($1);
                   }
                   ;

generic_ano_paralist : generic_ano_para
                       {
                           $$ = new gs_generic_ano_paralist();
                           $$->list.push_back(*$1);
                           SAFE_DELETE($1);
                       }
                       | generic_ano_paralist ',' generic_ano_para
                       {
                           $$ = $1;
                           $$->list.push_back(*$3);
                           SAFE_DELETE($3);
                       }
                       ;

ano_call_convention : T_CONVERNTION '<' ano_list '>' generic_ano_type T_ID '(' generic_ano_paralist ')' ';'
                      {
                          vector<string> ano_list = $3->list;
                          cx_generic_ano_type ret_type = *$5;
                          context::get_ctx()->ano_functions.push_back(cx_ano_function(*$6, ano_list, ret_type, $8->list));
                          PRINT_DEBUG("ANO_CALL_CONV: %s < %s > %s ( %s );", $3->src.c_str(), $5->name.c_str(), $6->c_str(), $8->src.c_str());
                          SAFE_DELETE($3);
                          SAFE_DELETE($5);
                          SAFE_DELETE($6);
                          SAFE_DELETE($8);
                      }
                      ;

built_in_ano_func : T_BUILT_IN 
                    {
                        context::get_ctx()->state = context::SkipAnoId;
                    }
                    '<' ano_list '>' generic_ano_type T_ID '(' generic_ano_paralist ')' T_BUILT_IN_SIG T_RAW_CODE
                    {
                        context::get_ctx()->state = context::Normal;
                        vector<string> ano_list = $4->list;
                        cx_generic_ano_type ret_type = *$6;
                        context::get_ctx()->bin_ano_functions.push_back(cx_bin_ano_function(*$7, ano_list, ret_type, $9->list, *$11, *$12));
                        PRINT_DEBUG("ANO_BUILT_IN: %s < %s > %s ( %s );", $4->src.c_str(), $6->name.c_str(), $7->c_str(), $9->src.c_str());
                        SAFE_DELETE($4);
                        SAFE_DELETE($6);
                        SAFE_DELETE($7);
                        SAFE_DELETE($9);
                        SAFE_DELETE($11);
                        SAFE_DELETE($12);
                    } 
                    ;

ano_list : T_ID
           {
               $$ = new gs_anolist();
               $$->list.push_back(*$1);
               SAFE_DELETE($1);
           }
           | ano_list ',' T_ID
           {
               $$ = $1;
               $$->list.push_back(*$3);
               SAFE_DELETE($3);
           }
           ;


def_space_ano : T_DEF_SPACE_ANO T_ID ';'
                {
                    context::get_ctx()->space_anos[*$2] = t_space_ano(*$2);
                    PRINT_DEBUG("_def_space_ano %s ;\n", $2->c_str());
                    SAFE_DELETE($2);
                }
                ;

def_signature_list: T_LT_INT
                    {
                        int sig = strtol($1->c_str(), NULL, 0);
                        $$ = new gs_signature_list();
                        $$->list.push_back(sig);
                        SAFE_DELETE($1);
                    }
                    | def_signature_list ',' T_LT_INT
                    {
                        $$ = $1;
                        int sig = strtol($3->c_str(), NULL, 0);
                        $$->list.push_back(sig);
                        SAFE_DELETE($3);
                    }
                    ;

def_dim_ano : T_DEF_DIM_ANO T_ID '<' def_signature_list '>' ';'
              {
                  string new_dim = *$2;
                  context::get_ctx()->dim_anos[new_dim] = t_dim_ano(new_dim, $4->list);
                  PRINT_DEBUG("_def_dim_ano %s ;\n", $2->c_str());
                  SAFE_DELETE($2);
                  SAFE_DELETE($4);
              }
              | T_DEF_DIM_ANO T_ID '<' T_DIMEN_ANO '*' T_DIMEN_ANO '>' ';'
              {
                  string new_dim = *$2;
                  t_dim_ano *d1 = $4;
                  t_dim_ano *d2 = $6;
                  context::get_ctx()->dim_anos[new_dim] = (*d1) * (*d2);
                  PRINT_DEBUG("_def_dim_ano %s <%s * %s>;\n", $2->c_str(), $4->name.c_str(), $6->name.c_str());
                  SAFE_DELETE($2);
              }
              | T_DEF_DIM_ANO T_ID '<' T_DIMEN_ANO '/' T_DIMEN_ANO '>' ';'
              {
                  string new_dim = *$2;
                  t_dim_ano *d1 = $4;
                  t_dim_ano *d2 = $6;
                  context::get_ctx()->dim_anos[new_dim] = (*d1) / (*d2);
                  PRINT_DEBUG("_def_dim_ano %s <%s / %s>;\n", $2->c_str(), $4->name.c_str(), $6->name.c_str());
                  SAFE_DELETE($2);
              }
              | T_DEF_DIM_ANO T_ID '<' '#' T_DIMEN_ANO '>' ';'
              {
                  string new_dim = *$2;
                  t_dim_ano *d1 = $5;
                  context::get_ctx()->dim_anos[new_dim] = $5->sqrt();
                  PRINT_DEBUG("_def_dim_ano %s <# %s>;\n", $2->c_str(), $5->name.c_str());
                  SAFE_DELETE($2)
              }
              ;

generic_dim_ano: '<' T_GENERIC_DIMEN_NOTATION '>'
                     ;

generic_space_ano: '<' T_GENERIC_SPACE_NOTATION '>'
                       ;

generic_space_ano_pair: '<' T_GENERIC_SPACE_NOTATION ',' T_GENERIC_SPACE_NOTATION '>'
                            ;

typemap_decl: T_TYPEMAP T_ID scale_type ';'
              {
                  //*** _typemap real 				float;
                  //
                  string newtype_name = *$2;
                  string basictype_name = *$3;
                  context::get_ctx()->typemaps[newtype_name] = shared_ptr<cx_typemap>(new cx_typemap(newtype_name, basictype_name));
                  PRINT_DEBUG("_typemap %s %s\n", $2->c_str(), $3->c_str());
                  SAFE_DELETE($2);
                  SAFE_DELETE($3);
              }
              | T_TYPEMAP T_ID generic_dim_ano scale_type ';'
              {
                  //** _typemap mreal<-dimen-> 	float;
                  //
                  string newtype_name = *$2;
                  string basictype_name = *$4;
                  context::get_ctx()->typemaps[newtype_name] = shared_ptr<cx_typemap>(new cx_scale_typemap(newtype_name, basictype_name));
                  PRINT_DEBUG("_typemap %s<-dimen-> %s\n", $2->c_str(), $4->c_str());
                  SAFE_DELETE($2);
                  SAFE_DELETE($4);
              }
              | T_TYPEMAP T_ID tuple_type '{' T_BASIC_TYPE '}' ';'
              {
                  //** _typemap tuple3				vec3{real};
                  //** 
                  string newtype_name = *$2;
                  string basictype_name = *$3;
                  string membertype_name = *$5; //member type;
                  context::get_ctx()->typemaps[newtype_name] = 
                      shared_ptr<cx_typemap>(new cx_tuple_typemap(newtype_name, basictype_name, context::get_ctx()->typemaps[membertype_name]));
                  PRINT_DEBUG("_typemap %s %s { %s }\n", $2->c_str(), $3->c_str(), $5->c_str());
                  SAFE_DELETE($2);
                  SAFE_DELETE($3);
                  SAFE_DELETE($5);
              }
              | T_TYPEMAP T_ID tuple_type '{' T_BASIC_TYPE generic_dim_ano '}' ';'
              {
                  //** _typemap spectrum			vec3{mreal<-dimen->};
                  string newtype_name = *$2;
                  string basictype_name = *$3;
                  string membertype_name = *$5; //member type;
                  context::get_ctx()->typemaps[newtype_name] = 
                      shared_ptr<cx_typemap>(new cx_tuple_typemap(newtype_name, basictype_name, context::get_ctx()->typemaps[membertype_name]));
                  PRINT_DEBUG("_typemap %s %s { %s<-dimen-> }\n", $2->c_str(), $3->c_str(), $5->c_str());
                  SAFE_DELETE($2);
                  SAFE_DELETE($3);
                  SAFE_DELETE($5);
              }
              | T_TYPEMAP T_ID generic_space_ano tuple_type '{' type '}' ';'
              {
                  //** _typemap direction<-space-> vec3{real};
                  //** _typemap point<-space->		vec3{mreal<length_d>};
                  string newtype_name = *$2;
                  string basictype_name = *$4;
                  shared_ptr<t_ano_type> member_type = $6->type;//member type;

                  context::get_ctx()->typemaps[newtype_name] = 
                      shared_ptr<cx_typemap>(new cx_space_tuple_typemap(newtype_name, basictype_name, member_type));
                  PRINT_DEBUG("_typemap %s %s { %s }\n", $2->c_str(), $4->c_str(), $6->type->name.c_str());
                  SAFE_DELETE($2);
                  SAFE_DELETE($4);
                  SAFE_DELETE($6);
              }
              | T_TYPEMAP T_ID generic_space_ano_pair mat_type '{' type '}' ';'
              {
                  //** _typemap rigidmap<-space-, -space-> mat4{real};
                  string newtype_name = *$2;
                  string basictype_name = *$4;
                  shared_ptr<t_ano_type> member_type = $6->type;//member type;

                  context::get_ctx()->typemaps[newtype_name] = 
                      shared_ptr<cx_typemap>(new cx_mat_typemap(newtype_name, basictype_name, member_type));
                  PRINT_DEBUG("_typemap %s %s { %s }\n", $2->c_str(), $4->c_str(), $6->type->name.c_str());
                  SAFE_DELETE($2);
                  SAFE_DELETE($4);
                  SAFE_DELETE($6);
              }
              ;


block: '{' { context::get_ctx()->push_context(); } statements { context::get_ctx()->pop_context(); }  '}'
       {
           $$ = $3;
           *$$ = '{' + *$3 + '}';
       }
       | T_IF '(' cond_expr ')' statement T_ELSE statement
       {
           $$ = $5;
           *$$ = "if(" + $3->src + ")" + *$5 + "else" + *$7;   
           SAFE_DELETE($3);
           SAFE_DELETE($7);
       }
       | T_IF '(' cond_expr ')' statement
       {
           $$ = $5;
           *$$ = "if(" + $3->src + ")" + *$5;
           SAFE_DELETE($3);
       }

       ;

cond_expr : expr '<' expr
            {
                if(!$1->type->get_member_type().get() && 
                    !$3->type->get_member_type().get())
                {
                    $$ = new gs_expression(shared_ptr<t_ano_type>(new t_ano_type("bool", "bool")));
                    $$->src = $1->src + "<" + $3->src;
                    SAFE_DELETE($1);
                    SAFE_DELETE($3);
                };
            }
            | expr '>' expr
            {
                if(!$1->type->get_member_type().get() && 
                    !$3->type->get_member_type().get())
                {
                    $$ = new gs_expression(shared_ptr<t_ano_type>(new t_ano_type("bool", "bool")));
                    $$->src = $1->src + ">" + $3->src;
                    SAFE_DELETE($1);
                    SAFE_DELETE($3);
                };
            }
            | expr T_EQ expr
            {
                if(!$1->type->get_member_type().get() && 
                    !$3->type->get_member_type().get())
                {
                    $$ = new gs_expression(shared_ptr<t_ano_type>(new t_ano_type("bool", "bool")));
                    $$->src = $1->src + "==" + $3->src;
                    SAFE_DELETE($1);
                    SAFE_DELETE($3);
                };
            }
            | expr T_GE expr
            {
                if(!$1->type->get_member_type().get() && 
                    !$3->type->get_member_type().get())
                {
                    $$ = new gs_expression(shared_ptr<t_ano_type>(new t_ano_type("bool", "bool")));
                    $$->src = $1->src + ">=" + $3->src;
                    SAFE_DELETE($1);
                    SAFE_DELETE($3);
                };
            }
            | expr T_LE expr
            {
                if(!$1->type->get_member_type().get() && 
                    !$3->type->get_member_type().get())
                {
                    $$ = new gs_expression(shared_ptr<t_ano_type>(new t_ano_type("bool", "bool")));
                    $$->src = $1->src + "<=" + $3->src;
                    SAFE_DELETE($1);
                    SAFE_DELETE($3);
                };
            }
            ;

statements: 
            {/* empty */ 
                $$ = new string();
            }
            | statements statement
            {
                $$ = $1;
                *$$ += *$2;
                SAFE_DELETE($2);
            }
            ;

statement: local_decl
           {
               $$ = $1;
           }
           | expr ';'
           {
               $$ = new string($1->src + ";\n");
               SAFE_DELETE($1);
           }
           | T_RETURN expr ';'
           {
               if(*($2->type) != *(context::get_ctx()->func_rtype))
               {
                   PRINT_ERROR("return type don't match, l%d,c%d-l%d,c%d", @1.first_line, @1.first_column, @3.last_line, @3.last_column);
                   YYERROR;
               }
               else
               {
                   $$ = new string("return " + $2->src + ";\n");
                   SAFE_DELETE($2);
               }
           }
           | block
           {
               $$ = $1;
           }
           ;

local_decl: type decl_id ';'
            {
                $$ = new string();
                *$$ = $1->src + " " + $2->src + ";\n";
                if(!append_declaration(*$2, $1->type, context::get_ctx()->variables))
                {
                    PRINT_ERROR("failed to add local variable, l%d,c%d-l%d,c%d", @1.first_line, @1.first_column, @3.last_line, @3.last_column);
                    YYERROR;
                }
                SAFE_DELETE($1);
                SAFE_DELETE($2);
            }
            ;


uniform_decl : T_UNIF type decl_id ';'
               {
                   $$ = new string();
                   if($2->type->get_space_ano2())
                   {
                       // quickly hack it into a matrix array.
                       $3->src += "[2]";
                   }
                   *$$ = "uniform " + $2->src + " " + $3->src + ";\n";
                   if(!append_declaration(*$3, $2->type, context::get_ctx()->uniforms))
                   {
                       PRINT_ERROR ("failed to add uniform, l%d,c%d-l%d,c%d", @1.first_line, @1.first_column, @4.last_line, @4.last_column);
                       YYERROR;
                   }
                   PRINT_DEBUG("UNIFORM: %s %s", $2->src.c_str(), $3->src.c_str());
                   SAFE_DELETE($2);
                   SAFE_DELETE($3);
               }
               //| T_UNIF T_SAMPLER2D_TYPE '<' type '>' T_ID ';'
               //{
               //    $$ = new string();
               //    *$$ = "uniform sampler2D " + *$6 + ";\n";
               //    context::get_ctx()->samplers[*$6] = t_sampler2d($4->type, *$6);
               //    PRINT_DEBUG("UNIFORM: Sampler<%s> %s", $4->src.c_str(), $6->c_str());
               //    SAFE_DELETE($4);
               //    SAFE_DELETE($6);
               //}
               ;

varying_decl : T_VARY type decl_id ';'
               {
                   if($2->type->get_space_ano2())
                   {
                       // no varing matrixs;
                       assert(false);
                   }
                   $$ = new string();
                   *$$ = "varying " + $2->src + " " + $3->src + ";\n";
                   if(!append_declaration(*$3, $2->type, context::get_ctx()->varyings))
                   {
                       PRINT_ERROR("failed to add varying, l%d,c%d-l%d,c%d", @1.first_line, @1.first_column, @4.last_line, @4.last_column);
                       YYERROR;
                   }
                   SAFE_DELETE($2);
                   SAFE_DELETE($3);
               }
               ;

attribute_decl : T_ATTR type decl_id ';'
                 {
                     if($2->type->get_space_ano2())
                     {
                         // quickly hack it into a matrix array.
                         $3->src += "[2]";
                     }
                     $$ = new string();
                     *$$ = "attribute " + $2->src + " " + $3->src + ";\n";
                     if(!append_declaration(*$3, $2->type, context::get_ctx()->attributes))
                     {
                         PRINT_ERROR("failed to add attribute, l%d,c%d-l%d,c%d", @1.first_line, @1.first_column, @4.last_line, @4.last_column);
                         YYERROR;
                     }
                     SAFE_DELETE($2);
                     SAFE_DELETE($3);
                 }
                 ;

in_decl : T_IN type decl_id ';'
          {
              if($2->type->get_space_ano2())
              {
                  // quickly hack it into a matrix array.
                  $3->src += "[2]";
              }
              $$ = new string();
              *$$ = "in " + $2->src + " " + $3->src + ";\n";
              if(!append_declaration(*$3, $2->type, context::get_ctx()->ins))
              {
                  PRINT_ERROR("failed to add in, l%d,c%d-l%d,c%d", @1.first_line, @1.first_column, @4.last_line, @4.last_column);
                  YYERROR;
              }
              SAFE_DELETE($2);
              SAFE_DELETE($3);
          }
          ;

out_decl : T_OUT type decl_id ';'
           {
               if($2->type->get_space_ano2())
               {
                   // quickly hack it into a matrix array.
                   $3->src += "[2]";
               }
               $$ = new string();
               *$$ = "out " + $2->src + " " + $3->src + ";\n";
               if(!append_declaration(*$3, $2->type, context::get_ctx()->outs))
               {
                   PRINT_ERROR("failed to add out, l%d,c%d-l%d,c%d", @1.first_line, @1.first_column, @4.last_line, @4.last_column);
                   YYERROR;
               }
               SAFE_DELETE($2);
               SAFE_DELETE($3);
           }
           ;


define_decl : T_DEFINE type T_ID expr ';'
              {
                  $$ = new string();
                  if(*($2->type) != *($4->type))
                  {
                      PRINT_ERROR("define type do not match, l%d,c%d-l%d,c%d", @1.first_line, @1.first_column, @4.last_line, @4.last_column);
                      YYERROR;
                  }
                  context::get_ctx()->defines.push_back(cx_define($2->type, *$3, $4->src));
                  SAFE_DELETE($2);
                  SAFE_DELETE($3);
                  SAFE_DELETE($4);
              }
              ;

decl_id : T_ID
          {
              $$ = new gs_id_decl(*$1);
              $$->src = *$1;
              SAFE_DELETE($1);
          }
          | decl_id '=' expr
          {
              $$ = $1;
              $$->has_init = true;
              gs_expression *e = $3;
              $$->init_expr = *e;
              $$->src = $1->src + '=' + $3->src;
              SAFE_DELETE($3);
          }
          ;

expr:    T_ID
         {
             shared_ptr<t_ano_type> t = context::get_ctx()->get_variable_type(*$1);
             if(t.get() == 0)
             {
                 PRINT_ERROR("undefined variable %s, l%d,c%d-l%d,c%d", $1->c_str(), @1.first_line, @1.first_column, @1.last_line, @1.last_column);
                 YYERROR;
             }
             else
             {
                 $$ = new gs_expression(t);
                 $$->src = *$1;
                 SAFE_DELETE($1);
             }
         }
         | literal_num { $$ = $1; }
         | '(' expr ')' 
         {
             $$ = $2;
             $$->src = "(" + $2->src + ")"
         }
         | type '(' arg_list ')' 
         {
             if(!context::get_ctx()->check_type_cast($1->type, $3->get_type_list()))
             {
                 PRINT_ERROR("cannot type cast %s, l%d,c%d-l%d,c%d\n", $1->src.c_str(), @1.first_line, @1.first_column, @4.last_line, @4.last_column);
                 YYERROR;
             }
             $$ = new gs_expression($1->type);
             $$->src = $1->src + "(" + $3->src + ")";
             PRINT_DEBUG("type_cast to %s\n", $1->src.c_str());
             SAFE_DELETE($1);
             SAFE_DELETE($3);
         }
         | T_ID '(' arg_list ')' 
         {
             shared_ptr<t_ano_type> rt = 
                 context::get_ctx()->check_function(*$1, $3->get_type_list());
             if(!rt.get())
             {
                 PRINT_ERROR("unknown function call %s, l%d,c%d-l%d,c%d", $1->c_str(), @1.first_line, @1.first_column, @4.last_line, @4.last_column);
                 YYERROR;
             }
             $$ = new gs_expression(rt);
             $$->src = *$1 + "(" + $3->src + ")";
             PRINT_DEBUG("%s(%s)\n", $1->c_str(), $3->src.c_str());
             SAFE_DELETE($1);
             SAFE_DELETE($3);
         }
         | expr '=' expr
         {
             if(*($1->type) != *($3->type))
             {
                 PRINT_ERROR("type different assign, l%d,c%d-l%d,c%d", @1.first_line, @1.first_column, @3.last_line, @3.last_column);
                 YYERROR;
             }
             $$ = new gs_expression($1->type);
             $$->src = $1->src + "=" + $3->src;
             PRINT_DEBUG("%s = %s\n", $1->src.c_str(), $3->src.c_str());
             SAFE_DELETE($1);
             SAFE_DELETE($3);
         }
         | expr '+' expr
         {
             vector<shared_ptr<t_ano_type>> typelist;
             typelist.push_back($1->type);
             typelist.push_back($3->type);
             string op("+");
             shared_ptr<t_ano_type> rt = 
                 context::get_ctx()->check_function(op, typelist);
             if(!rt.get())
             {
                 PRINT_ERROR("type check failed, l%d,c%d-l%d,c%d", @1.first_line, @1.first_column, @3.last_line, @3.last_column);
                 YYERROR;
             }
             $$ = new gs_expression(rt);
             $$->src = $1->src + "+" + $3->src;
             PRINT_DEBUG("%s + %s\n", $1->src.c_str(), $3->src.c_str());
             SAFE_DELETE($1);
             SAFE_DELETE($3);
         }
         | expr '-' expr
         {
             vector<shared_ptr<t_ano_type>> typelist;
             typelist.push_back($1->type);
             typelist.push_back($3->type);
             string op("-");
             shared_ptr<t_ano_type> rt = 
                 context::get_ctx()->check_function(op, typelist);
             if(!rt.get())
             {
                 PRINT_ERROR("type check failed, l%d,c%d-l%d,c%d", @1.first_line, @1.first_column, @3.last_line, @3.last_column);
                 YYERROR;
             }
             $$ = new gs_expression(rt);
             $$->src = $1->src + "-" + $3->src;
             PRINT_DEBUG("%s - %s\n", $1->src.c_str(), $3->src.c_str());
             SAFE_DELETE($1);
             SAFE_DELETE($3);
         }
         | expr '*' expr
         {
             vector<shared_ptr<t_ano_type>> typelist;
             typelist.push_back($1->type);
             typelist.push_back($3->type);
             string op("*");
             shared_ptr<t_ano_type> rt = 
                 context::get_ctx()->check_function(op, typelist);
             if(!rt.get())
             {
                 PRINT_ERROR("type check failed, l%d,c%d-l%d,c%d", @1.first_line, @1.first_column, @3.last_line, @3.last_column);
                 YYERROR;
             }
             $$ = new gs_expression(rt);
             $$->src = $1->src + "*" + $3->src;
             PRINT_DEBUG("%s * %s\n", $1->src.c_str(), $3->src.c_str());
             SAFE_DELETE($1);
             SAFE_DELETE($3);
         }
         | expr '/' expr
         {
             vector<shared_ptr<t_ano_type>> typelist;
             typelist.push_back($1->type);
             typelist.push_back($3->type);
             string op("/");
             shared_ptr<t_ano_type> rt = 
                 context::get_ctx()->check_function(op, typelist);
             if(!rt.get())
             {
                 PRINT_ERROR("type check failed, l%d,c%d-l%d,c%d", @1.first_line, @1.first_column, @3.last_line, @3.last_column);
                 YYERROR;
             }
             $$ = new gs_expression(rt);
             $$->src = $1->src + "/" + $3->src;
             PRINT_DEBUG("%s / %s\n", $1->src.c_str(), $3->src.c_str());
             SAFE_DELETE($1);
             SAFE_DELETE($3);
         }
         | '-' expr %prec UMINUS
         {
             $$ = $2;
             $$->src = "-" + $2->src;
             PRINT_DEBUG("- %s\n", $2->src.c_str());
         }
         | T_TEXTURE2D '(' expr ',' expr  ')'
         {
             if($5->type->builtin_type != "vec2")
             {
                 PRINT_ERROR("textcoord argument %s do not have built in type vec2, l%d,c%d-l%d,c%d\n", $5->src.c_str(), @5.first_line, @5.first_column, @5.last_line, @5.last_column);
                 YYERROR;
             }
             if(!$3->type->is_sampler())
             {
                 PRINT_ERROR ("cannot find sampler %s, l%d,c%d-l%d,c%d", $3->src.c_str(), @3.first_line, @3.first_column, @3.last_line, @3.last_column);
                 YYERROR;
             }
             $$ = new gs_expression($3->type->get_member_type());
             $$->src = "texture2D(" + $3->src + "," + $5->src + ")";
             if(!$3->type->get_member_type()->get_member_type().get())
             {
                 $$->src += ".x"; //hack for non tuple texture.
             }
             PRINT_DEBUG("texture2D(%s,%s)\n", $3->src.c_str(), $5->src.c_str());
             SAFE_DELETE($3);
             SAFE_DELETE($5);
         }
         | expr '.' T_ID
         {
             if(*$3 == "x" || *$3 == "y" || *$3 == "z" || *$3 == "w" || 
                 *$3 == "a" || *$3 == "r" || *$3 == "g" || *$3 == "b")
             {
                 if(!$1->type->get_member_type().get())
                 {
                     PRINT_ERROR ("%s is not tuple type, l%d,c%d-l%d,c%d", $3->c_str(), @3.first_line, @3.first_column, @3.last_line, @3.last_column);
                     YYERROR;
                 }
                 $$ = new gs_expression($1->type->get_member_type());
                 $$->src = $1->src + '.' + *$3;
             }
             else
             {
                 PRINT_ERROR ("only support single member operation for vec type %s, l%d,c%d-l%d,c%d", $3->c_str(), @3.first_line, @3.first_column, @3.last_line, @3.last_column);
                 YYERROR;
             }
             SAFE_DELETE($1);
             SAFE_DELETE($3);
         }
         ;

arg_list:   
         {/* empty */
             $$ = new gs_arglist();
         }
         | expr
         {
             $$ = new gs_arglist();
             $$->src = $1->src;
             $$->list.push_back(*$1);
             SAFE_DELETE($1);
         }
         | arg_list ',' expr 
         {
             $$ = $1;
             $$->src += ',' + $3->src;
             $$->list.push_back(*$3);
             SAFE_DELETE($3);
         }
         ;

literal_num: T_LT_INT
             {
                 $$ = new gs_expression(shared_ptr<t_ano_type>(new t_ano_type("real", "int")));
                 $$->src = *$1;
                 SAFE_DELETE($1);
             }
             | T_LT_FLT
             {
                 $$ = new gs_expression(shared_ptr<t_ano_type>(new t_ano_type("real", "float")));
                 $$->src = *$1;
                 SAFE_DELETE($1);
             }
             | T_LT_BLN
             {
                 $$ = new gs_expression(shared_ptr<t_ano_type>(new t_ano_type("bool", "bool")));
                 $$->src = *$1;
                 SAFE_DELETE($1);
             }
             ;

type: builtin_type 
      { 
          $$ = new gs_type();
          $$->type = shared_ptr<t_ano_type>(new t_ano_type(*$1, *$1));
          $$->src = *$1;
          SAFE_DELETE($1);
      }
      | T_BASIC_TYPE
      {
          $$ = new gs_type();
          string tname = *$1;
          $$->type = context::get_ctx()->deduct_type(tname);
          if(!$$->type.get())
          {
              YYERROR;
          }
          $$->src = $$->type->builtin_type;
          SAFE_DELETE($1);  
      }
      | T_BASIC_TYPE '<' T_DIMEN_ANO '>' 
      {
          $$ = new gs_type();
          string tname = *$1;
          $$->type = context::get_ctx()->deduct_type(tname, $3);
          if(!$$->type.get())
          {
              YYERROR;
          }
          $$->src = $$->type->builtin_type;
          SAFE_DELETE($1);  
      }
      | T_BASIC_TYPE '<' T_SPACE_ANO '>' 
      {
          $$ = new gs_type();
          string tname = *$1;
          $$->type = context::get_ctx()->deduct_type(tname, $3);
          if(!$$->type.get())
          {
              YYERROR;
          }
          $$->src = $$->type->builtin_type;
          SAFE_DELETE($1);  
      }
      | T_BASIC_TYPE '<' T_SPACE_ANO ',' T_SPACE_ANO '>'
      {
          $$ = new gs_type();
          string tname = *$1;
          $$->type = context::get_ctx()->deduct_type(tname, $3, $5);
          if(!$$->type.get())
          {
              YYERROR;
          }
          $$->src = $$->type->builtin_type;
          SAFE_DELETE($1);  
      }
      | T_SAMPLER2D_TYPE '<' type '>'
      {
          $$ = new gs_type();
          shared_ptr<t_sampler_type> st = shared_ptr<t_sampler_type>(new t_sampler_type("sampler2D", "sampler2D"));
          st->member_type = $3->type;
          $$->type = st;
          $$->src = "sampler2D";
          PRINT_DEBUG("sampler2D<%s>\n", $3->src.c_str());
          SAFE_DELETE($3); 
      };

scale_type : T_FLOAT { $$ = $1; }
      | T_INT { $$ = $1; }
      | T_BOOL { $$ = $1; }
      | T_UINT { $$ = $1; }
      ;

tuple_type : T_VEC { $$ = $1; }
      | T_IVEC { $$ = $1; }
      | T_BVEC { $$ = $1; }
      | T_UVEC { $$ = $1; }
      ;

mat_type   : T_MAT4 { $$ = $1; }
      ;

sampler_type : T_SAMPLER2D_TYPE { $$ = $1; }
      ;

builtin_type:T_VOID { $$ = $1; }
      | scale_type { $$ = $1; }
      | tuple_type { $$ = $1; }
      | mat_type { $$ = $1; }
      | sampler_type { $$ = $1; }
      ;

      %%

          /*--------------------------------------------------------*/
          /* Additional C code */
          /* Error processor for yyparse */
#include <stdio.h>
          void yyerror (char const *s)       /* called by yyparse on error */
      {
          fprintf(stderr, "syntax error in some where\n");
      }

