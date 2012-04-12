
/* no include is allowed. */
%option noyywrap

%option never-interactive


%{
#include "aux_data.h"
#include<parser.hpp>
#include<assert.h>
//#define PRINT_TOKEN

#define PROCESS_TOKEN(TOKEN) {yylval.str = new string(yytext); PRINT_T(#TOKEN); return TOKEN;}
#define PROCESS_CHAR() {return yytext[0];}
#define PROCESS_NODATA(TOKEN) {return TOKEN;}
//#define PROCESS_TYPE(TYPE) { yylval.type = new gs_type(yytext); yylval.type->src = yytext; PRINT_T(#TYPE); return TYPE;}

#ifdef PRINT_TOKEN
#define PRINT_T(TOKEN) printf("%s: %s\n", TOKEN, yytext)
#else
#define PRINT_T(TOKEN)
#endif

#define T_RESERVED { printf("%s is reserved keyword\n", yytext); }

    string raw_code_source;
%}

%x comment
%x cpp_comment
%x raw_code

%%

"varying"           PROCESS_NODATA(T_VARY)
"uniform"           PROCESS_NODATA(T_UNIF)
"attribute"         PROCESS_NODATA(T_ATTR)

"void"              PROCESS_TOKEN(T_VOID)
"int"               PROCESS_TOKEN(T_INT)
"uint"              PROCESS_TOKEN(T_UINT)
"float"             PROCESS_TOKEN(T_FLOAT)
"bool"              PROCESS_TOKEN(T_BOOL)
vec[2-4]            PROCESS_TOKEN(T_VEC)
mat[4](x4)?         PROCESS_TOKEN(T_MAT4)
"sampler2D"         PROCESS_NODATA(T_SAMPLER2D_TYPE)
"texture2D"         PROCESS_NODATA(T_TEXTURE2D)

ivec[2-4]           T_RESERVED
bvec[2-4]           T_RESERVED
uvec[2-4]           T_RESERVED

mat[2-3](x[2-3])?   T_RESERVED;


sampler1D(Array)?(Shadow)?          T_RESERVED
sampler2D[(Array)+(Shadow)+]        T_RESERVED
sampler3D                           T_RESERVED
samplerCube                         T_RESERVED
sampler2DRect(Shadow)?              T_RESERVED
samplerBuffer                       T_RESERVED
sampler2DMS(Array)?                 T_RESERVED

isampler[1-2]D(Array)?              T_RESERVED
isampler3D                          T_RESERVED
isamplerCube                        T_RESERVED
isampler2DRect                      T_RESERVED
isamplerBuffer                      T_RESERVED
isampler2DMS(Array)?                T_RESERVED

usampler[1-2]D(Array)?              T_RESERVED
usampler3D                          T_RESERVED
usamplerCube                        T_RESERVED
usampler2DRect                      T_RESERVED
usamplerBuffer                      T_RESERVED
usampler2DMS(Array)?                T_RESERVED

"in"                PROCESS_NODATA(T_IN)
"out"               PROCESS_NODATA(T_OUT)
"inout"             PROCESS_NODATA(T_INOUT)

"return"            PROCESS_NODATA(T_RETURN)
"="                 PROCESS_CHAR()

"_operator"          PROCESS_NODATA(T_OPERATOR)
"_typemap"           PROCESS_NODATA(T_TYPEMAP)
"_def_space_ano"     PROCESS_NODATA(T_DEF_SPACE_ANO)
"_def_dimen_ano"     PROCESS_NODATA(T_DEF_DIM_ANO)
"_define"            PROCESS_NODATA(T_DEFINE)
"_built_in"         PROCESS_NODATA(T_BUILT_IN)
"_convention"       PROCESS_NODATA(T_CONVERNTION)

"-dimen-"           PROCESS_NODATA(T_GENERIC_DIMEN_NOTATION)
"-space-"           PROCESS_NODATA(T_GENERIC_SPACE_NOTATION)

"("                 PROCESS_CHAR()
")"                 PROCESS_CHAR()
"["                 PROCESS_CHAR()
"]"                 PROCESS_CHAR()
"{"                 PROCESS_CHAR()
"}"                 PROCESS_CHAR()

"*"                 PROCESS_CHAR()
"+"                 PROCESS_CHAR()
"-"                 PROCESS_CHAR()
"/"                 PROCESS_CHAR()

"=="                PROCESS_NODATA(T_EQ)
"<"                 PROCESS_CHAR()
">"                 PROCESS_CHAR()
"<="                PROCESS_NODATA(T_LE)
">="                PROCESS_NODATA(T_GE)

";"                 PROCESS_CHAR()
","                 PROCESS_CHAR()
"."                 PROCESS_CHAR()
"#"                 PROCESS_CHAR()

"if"                PROCESS_NODATA(T_IF)
"else"              PROCESS_NODATA(T_ELSE)
"for"               PROCESS_NODATA(T_FOR)

[+-]?[1-9][0-9]*[Uu]?                   PROCESS_TOKEN(T_LT_INT)
[+-]?0[0-7]*[Uu]?                       PROCESS_TOKEN(T_LT_INT)
[+-]?0[xX][0-9a-fA-F]+[Uu]?             PROCESS_TOKEN(T_LT_INT)

[+-]?[0-9]+"."[0-9]+([Ee][+-]?[0-9]+)?[Ff]?     PROCESS_TOKEN(T_LT_FLT)
[+-]?[0-9]+"."([Ee][+-]?[0-9]+)?[Ff]?           PROCESS_TOKEN(T_LT_FLT)
[+-]?"."[0-9]+([Ee][+-]?[0-9]+)?[Ff]?           PROCESS_TOKEN(T_LT_FLT)
[+-]?[0-9]+[Ee][+-]?[0-9]+[Ff]?                 PROCESS_TOKEN(T_LT_FLT)

"true"              PROCESS_TOKEN(T_LT_BLN)
"false"             PROCESS_TOKEN(T_LT_BLN)

[a-zA-Z_][a-zA-Z_0-9]* {
    string id = yytext;
    // if space anno?
    if(context::get_ctx()->state != context::SkipAnoId)
    {
        space_ano_it sit = context::get_ctx()->space_anos.find(id);
        if(sit != context::get_ctx()->space_anos.end())
        {
            yylval.space_ano = &sit->second;
            return T_SPACE_ANO;
        }

        dim_ano_it dit = context::get_ctx()->dim_anos.find(id);
        if(dit != context::get_ctx()->dim_anos.end())
        {
            yylval.dimen_ano = &dit->second;
            return T_DIMEN_ANO;
        }
    }
    typemap_it tit = context::get_ctx()->typemaps.find(id);
    if(tit != context::get_ctx()->typemaps.end())
    {
        yylval.str = new string(id);
        return T_BASIC_TYPE;
    }


    yylval.str = new string(id);
    return T_ID;
}

\n          {  }
[ \t]+      { }
.           { assert(false); return yytext[0]; }

"/*"                    BEGIN(comment);
<comment>[^*\n]*        /* eat anything that's not a '*' */
<comment>"*"+[^*/\n]*   /* eat up '*' s not followed by '/'s */
<comment>"*"+"/"        BEGIN(INITIAL);

"//"                    BEGIN(cpp_comment);
<cpp_comment>[^\n]      
<cpp_comment>\n         BEGIN(INITIAL);

"@"[a-zA-Z_][a-zA-Z_0-9]*"@--" { 
    BEGIN(raw_code); 
    raw_code_source = ""; 
    string input = yytext;
    int end = input.find_first_of('@', 1);
    yylval.str = new string(input.substr(1, end-1)); 
    return T_BUILT_IN_SIG; 
}
<raw_code>[ \t\n]+      { raw_code_source += " "; }
<raw_code>[^ \t\n]      { raw_code_source += yytext; }
<raw_code>"--@"         { 
    BEGIN(INITIAL); 
    yylval.str = new string(raw_code_source); 
    //printf("%s\n", raw_code_source.c_str()); 
    return T_RAW_CODE; 
}


%%

void setup_buf(const std::string &in_src)
{
    yy_scan_string(in_src.c_str());
}

std::string get_str()
{
    return std::string(YY_CURRENT_BUFFER->yy_ch_buf);
}

void release_buf()
{
    yy_delete_buffer(YY_CURRENT_BUFFER);
}