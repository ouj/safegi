#ifndef _PARSER_CONTEXT_H_
#define _PARSER_CONTEXT_H_
#include <string>
#include <vector>
#include <map>
#include <assert.h>
#include <type_checker.h>

using std::vector;
using std::string;
using std::map;
using std::tr1::shared_ptr;

struct cx_node {};

typedef t_var cx_in;
typedef t_var cx_out;

struct cx_function : public cx_node
{
    cx_function(const shared_ptr<t_ano_type> returnt, const string &fn) 
        : cx_node(), name(fn), type(returnt) {}
    cx_function(const shared_ptr<t_ano_type> returnt, const string &fn, const vector<shared_ptr<t_ano_type>> &tp) 
        : cx_node(), name(fn), type(returnt), tparas(tp) {}
    virtual ~cx_function() {}

    shared_ptr<t_ano_type> accept(const vector<shared_ptr<t_ano_type>> &arg_type_list);

    string                                 name;
    shared_ptr<t_ano_type>                 type;
    vector<shared_ptr<t_ano_type>>         tparas;
};

struct cx_bin_function : public cx_node
{
    cx_bin_function(const shared_ptr<t_ano_type> returnt, const string &fn, 
        const vector<t_var> &p, const string &sig, const string& rc) 
        : cx_node(), name(fn), type(returnt), paras(p), raw_code(rc), signature(sig) {}
    virtual ~cx_bin_function() {}

    shared_ptr<t_ano_type> accept(const vector<shared_ptr<t_ano_type>> &arg_type_list, string *inject_code = NULL);

    string                                 name;
    shared_ptr<t_ano_type>                 type;
    vector<t_var>                          paras;
    string                                 raw_code;
    string                                 signature;
};

struct cx_generic_ano_type : public cx_node
{
    enum ano_op
    {
        NONE,
        MUL,
        DIV,
        SQRT
    };

    cx_generic_ano_type(const string &t_name, const string &a1 = "", const string &a2 = "", const ano_op &oper = cx_generic_ano_type::NONE) 
        : cx_node(), name(t_name), ano1(a1), ano2(a2), op(oper) {}
    virtual ~cx_generic_ano_type() {} 
    string name;
    string ano1;
    string ano2;
    ano_op op;
};

struct cx_generic_ano_para : public cx_node
{
    cx_generic_ano_para(const cx_generic_ano_type &t, const string& n) 
        : cx_node(), name(n), type(t) {}
    virtual ~cx_generic_ano_para() {}

    string              name;
    cx_generic_ano_type type;
};

struct cx_ano_function : public cx_node
{
    cx_ano_function(const string &fname, const vector<string> &ano_list, const cx_generic_ano_type &rtype, const vector<cx_generic_ano_para> &plist) 
        : cx_node(), name(fname), ano_list(ano_list), ret_type(rtype), paralist(plist) {} 

    virtual ~cx_ano_function() {}
    shared_ptr<t_ano_type> accept(const vector<shared_ptr<t_ano_type>> &arg_type_list);

    string name;
    vector<string> ano_list;
    cx_generic_ano_type ret_type;
    vector<cx_generic_ano_para> paralist;
};

struct cx_bin_ano_function : public cx_node
{
    cx_bin_ano_function(const string &fname, const vector<string> &ano_list, const cx_generic_ano_type &rtype, 
        const vector<cx_generic_ano_para> &plist, const string& sig, const string& rc) 
        : cx_node(), name(fname), ano_list(ano_list), ret_type(rtype), paralist(plist), raw_code(rc), signature(sig) {} 

    virtual ~cx_bin_ano_function() {}
    shared_ptr<t_ano_type> accept(const vector<shared_ptr<t_ano_type>> &arg_type_list, string *code = NULL);

    string                      name;
    vector<string>              ano_list;
    cx_generic_ano_type         ret_type;
    vector<cx_generic_ano_para> paralist;
    string                      raw_code;
    string                      signature;
};

struct cx_define : public cx_node
{
    cx_define(const shared_ptr<t_ano_type> t,const string &vn) 
        : cx_node(), type(t), name(vn){}
    cx_define(const shared_ptr<t_ano_type> t,const string &vn, const string &e) 
        : cx_node(), type(t), name(vn), expr(e){}

    virtual ~cx_define() {};
    shared_ptr<t_ano_type> type;
    string name;
    string expr;
};


struct cx_typemap
{
    cx_typemap() {};
    cx_typemap(const string& n, const string& bt) 
        : name(n), builtin_type(bt) {}
    virtual ~cx_typemap() {}
    virtual shared_ptr<t_ano_type>   substantial(const t_ano *ano1 = NULL, const t_ano *ano2 = NULL);
    string                 name;
    string                 builtin_type;
};

struct cx_scale_typemap : public cx_typemap
{
    cx_scale_typemap() {}
    cx_scale_typemap(const string& n, const string& bt) 
        : cx_typemap(n, bt){}

    virtual shared_ptr<t_ano_type>   substantial(const t_ano *ano1 = NULL, const t_ano *ano2 = NULL);
    virtual ~cx_scale_typemap() {}
};

struct cx_tuple_typemap : public cx_scale_typemap
{
    cx_tuple_typemap() {}
    cx_tuple_typemap(const string& n, const string& bt) 
        : cx_scale_typemap(n, bt){}
    cx_tuple_typemap(const string& n, const string& bt, shared_ptr<cx_typemap> mem_typemap) 
        : cx_scale_typemap(n, bt), member_typemap(mem_typemap){}
    virtual ~cx_tuple_typemap() {}

    virtual shared_ptr<t_ano_type>   substantial(const t_ano *ano1 = NULL, const t_ano *ano2 = NULL);
    shared_ptr<cx_typemap>            member_typemap;
};


struct cx_space_tuple_typemap : public cx_typemap
{
    cx_space_tuple_typemap() {}
    cx_space_tuple_typemap(const string& n, const string& bt) 
        : cx_typemap(n, bt){}
    cx_space_tuple_typemap(const string& n, const string& bt, shared_ptr<t_ano_type> mt) 
        : cx_typemap(n, bt), member_type(mt){}
    virtual ~cx_space_tuple_typemap() {}

    virtual shared_ptr<t_ano_type>   substantial(const t_ano *ano1 = NULL, const t_ano *ano2 = NULL);
    shared_ptr<t_ano_type>            member_type;
};

struct cx_mat_typemap : public cx_typemap
{
    cx_mat_typemap() {}
    cx_mat_typemap(const string& n, const string& bt, shared_ptr<t_ano_type> mt) 
        : cx_typemap(n, bt), member_type(mt){}
    virtual ~cx_mat_typemap() {}

    virtual shared_ptr<t_ano_type>   substantial(const t_ano *ano1 = NULL, const t_ano *ano2 = NULL);
    shared_ptr<t_ano_type>           member_type;
};

typedef map<string, shared_ptr<cx_typemap>>::iterator   typemap_it;
typedef map<string, t_space_ano>::iterator              space_ano_it;
typedef map<string, t_dim_ano>::iterator                dim_ano_it;
typedef map<string, t_uniform>::iterator                uniform_it;
typedef map<string, t_varying>::iterator                varying_it;
typedef map<string, t_attribute>::iterator              attribute_it;
typedef map<string, t_var>::iterator                   variable_it;
typedef map<string, cx_in>::iterator                    in_it;
typedef map<string, cx_out>::iterator                   out_it;
typedef map<string, t_sampler2d>::iterator            sampler_it;

struct context
{
    enum parsing_state
    {
        Normal,
        SkipAnoId,
    };

    parsing_state state;

    context()
    {
        cleanup();
        state = Normal;
    }

    static context* p_context;
    static context* get_ctx();

    void cleanup();

    inline void push_context();
    inline void pop_context();

    const shared_ptr<t_ano_type> get_variable_type(const string &vname);
    shared_ptr<t_ano_type> check_function(string &fname, const vector<shared_ptr<t_ano_type>> &arg_type_list);
    bool  check_type_cast(shared_ptr<t_ano_type> target, const vector<shared_ptr<t_ano_type>> &arg_type_list);

    map<string, t_space_ano>             space_anos;
    map<string, t_dim_ano>               dim_anos;
    map<string, shared_ptr<cx_typemap>>  typemaps;

    shared_ptr<t_ano_type> deduct_type(const string &name, const t_ano* ano1 = NULL, const t_ano* ano2 = NULL);

    map<string, t_uniform>          uniforms;
    map<string, t_varying>          varyings;
    map<string, t_attribute>        attributes;
    map<string, cx_in>              ins;
    map<string, cx_out>             outs;
    map<string, t_sampler2d>        samplers;

    map<string, bool>               built_in_map;

    vector<cx_function>             functions;
    vector<cx_bin_function>         bin_functions;
    vector<cx_ano_function>         ano_functions;
    vector<cx_bin_ano_function>     bin_ano_functions;
    vector<cx_define>               defines;

    typedef map<string, t_var>      var_list;
    var_list                        variables;
    vector<var_list>                context_stack;

    shared_ptr<t_ano_type>          func_rtype;
    string                          built_in_code;
};

inline void context::push_context()
{
    context_stack.push_back(variables);
}

inline void context::pop_context()
{
    variables = context_stack.back();
    context_stack.pop_back();
}


#endif // _PARSER_CONTEXT_H_