#include <type_checker.h>
#include <iostream>
#include <predef_symbols.h>
#include <string>

t_info         *g_info = NULL; //warning: not multithread.
std::string     ouput_src;
bool            is_predef;

void setup_buf(const std::string &in_src);
std::string get_str();
void release_buf();
int yyparse (void);

bool t_ano_type::operator ==(const t_ano_type& t) const
{
    if(name != t.name)
        return false;
    if(builtin_type != t.builtin_type)
        return false;

    if(get_space_ano2() && t.get_space_ano2())
    {
        if(*get_space_ano2() != *t.get_space_ano2())
            return false;
    }
    else if(get_space_ano2() != t.get_space_ano2())
    {
        return false;
    }


    if(get_space_ano1() && t.get_space_ano1())
    {
        if(*get_space_ano1() != *t.get_space_ano1())
            return false;
    }
    else if(get_space_ano1() != t.get_space_ano1())
    {
        return false;
    }

    if(get_dim_ano() && t.get_dim_ano())
    {
        if(*get_dim_ano() != *t.get_dim_ano())
            return false;
    }
    else if(get_dim_ano() != t.get_dim_ano())
    {
        return false;
    }

    if(get_member_type().get() && t.get_member_type().get())
    {
        if(*get_member_type() != *t.get_member_type())
            return false;
    }
    else if(get_member_type() != t.get_member_type())
    {
        return false;
    }
    return true;
}

bool type_check(const std::string &in_src, std::string &out_src, t_info *info)
{
    if(info != NULL)
        g_info = info;

    // parse pre-define symbols
    is_predef = true;
    setup_buf(predef_symbol_code);
    bool failed = yyparse() != 0;
    assert(!failed);
    release_buf();

    // user source
    is_predef = false;
    setup_buf(in_src);
    bool succeeded = yyparse() == 0;
    if(!succeeded)
    {
        std::cout << "Type check failed!" << std::endl;
    }
    else
    {
        //std::cout << ouput_src << std::endl;
        std::cout << "Type check passed!" << std::endl;
        out_src = ouput_src;
    };
    release_buf();
    return succeeded;
}
