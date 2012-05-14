#ifndef _AUX_DATA_H_
#define _AUX_DATA_H_
#include <context.h>
#include <iostream>

using std::tr1::shared_ptr;
// #define REF_COUNT_VERBOSE

struct gs_node
{
    static int ref;
    gs_node() 
    { 
        ref++; 
#ifdef REF_COUNT_VERBOSE
        cout << "C:" << ref<< endl; 
#endif
    }

    virtual ~gs_node() 
    {
        ref --; 
#ifdef REF_COUNT_VERBOSE
        cout << "D:" << ref << endl;
#endif
    }

    gs_node(const gs_node& node)
    {
        src = node.src;  
        ref++; 
#ifdef REF_COUNT_VERBOSE
        cout << "C:" << ref<< endl; 
#endif
    }

    gs_node(string s) : src(s) 
    { 
        ref++; 
#ifdef REF_COUNT_VERBOSE
        cout << "C:" << ref<< endl; 
#endif
    }

    string src;
};

struct gs_type : public gs_node
{
    gs_type() : gs_node(){}
    virtual ~gs_type(){};

    std::tr1::shared_ptr<t_ano_type>  type;
};

struct gs_expression : public gs_node
{
    gs_expression() : gs_node(){}
    gs_expression(const shared_ptr<t_ano_type> t)  : gs_node(), type(t){}
    virtual ~gs_expression() {}

    shared_ptr<t_ano_type>  type;
};

struct gs_id_decl : public gs_node
{
    gs_id_decl() : gs_node() {}
    gs_id_decl(const string& n, bool isa = false, bool init = false) 
        : gs_node(), name(n), is_array(isa), has_init(init) {}
    virtual ~gs_id_decl(){}
    string          name;
    bool            is_array;
    bool            has_init;
    gs_expression   init_expr;
};

struct gs_signature_list : public gs_node
{
    gs_signature_list() : gs_node() {}
    virtual ~gs_signature_list(){}

    vector<int> list;
};

struct gs_id_decl_list : public gs_node
{
    gs_id_decl_list() : gs_node() {}
    virtual ~gs_id_decl_list(){}

    vector<gs_id_decl> list;
};

struct gs_anolist : public gs_node
{
    gs_anolist() : gs_node() {}
    virtual ~gs_anolist(){}

    vector<string> list;
};

struct gs_generic_ano_paralist : public gs_node
{
    gs_generic_ano_paralist() : gs_node() {}
    virtual ~gs_generic_ano_paralist() {};

    vector<cx_generic_ano_para> list;
};

struct gs_paralist : public gs_node
{
    gs_paralist() : gs_node() {}
    virtual ~gs_paralist() {}

    vector<shared_ptr<t_ano_type>> get_type_list()
    {
        vector<shared_ptr<t_ano_type>> tlist;
        vector<t_var>::iterator it = list.begin();
        while(it != list.end())
        {
            tlist.push_back(it->type);
            it++;
        }
        return tlist;
    }
    vector<t_var> list;
};

struct gs_arglist : public gs_node
{
    gs_arglist() : gs_node() {}
    virtual ~gs_arglist() {}

    vector<shared_ptr<t_ano_type>> get_type_list()
    {
        vector<shared_ptr<t_ano_type>> tlist;
        vector<gs_expression>::iterator it = list.begin();
        while(it != list.end())
        {
            tlist.push_back(it->type);
            it++;
        }
        return tlist;
    }
    vector<gs_expression> list;
};


template<typename T>
bool append_declaration(const gs_id_decl& id_decl, shared_ptr<t_ano_type> type, std::map<string, T> &colletion)
{
    if(id_decl.has_init)
    {
        if(*(id_decl.init_expr.type) != *type)
        {
            return false;
        }
    }
    string varname = id_decl.name;
    colletion[varname] = (T(type, id_decl.name));
    return true;
}


#endif // _AUX_DATA_H_