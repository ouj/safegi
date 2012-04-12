#ifndef _SAFE_GLSL_TYPE_CHECKER_H_
#define _SAFE_GLSL_TYPE_CHECKER_H_

#include<string>
#include<vector>
#include<map>
#include<assert.h>

#ifdef _WIN32
#include <memory>
#else
#include <tr1/memory>
#endif

using std::string;
using std::tr1::shared_ptr;
using std::tr1::dynamic_pointer_cast;

struct t_ano
{
    t_ano() {}
    t_ano(const string &n) : name(n) {}
    virtual ~t_ano() {};

    bool operator == (const t_ano &t) const { return t.name == name; }
    bool operator != (const t_ano &t) const { return t.name != name; }

    virtual const string get_signature() const { return name; }

    string name;
};

struct t_space_ano : public t_ano
{
    t_space_ano() : t_ano() {}
    t_space_ano(const string &vn) : t_ano(vn){}
    virtual ~t_space_ano() {};
};

struct t_dim_ano : public t_ano
{
    t_dim_ano() {}
    t_dim_ano(const string &vn) : t_ano(vn) {}
    t_dim_ano(const string &vn, const std::vector<int> &sig) : t_ano(vn), signature(sig) {}

    virtual ~t_dim_ano() {};

    bool operator == (const t_dim_ano &t) const { return t.signature == signature; }
    bool operator != (const t_dim_ano &t) const { return t.signature != signature; }

    t_dim_ano operator* (const t_dim_ano &t1) const
    { 
        t_dim_ano ndim(name + "*" + t1.name);
        for(unsigned int i = 0; i < signature.size(); i++)
        {
            ndim.signature.push_back(signature[i] + t1.signature[i]);
        }
        return ndim;       
    }

    t_dim_ano operator/ (const t_dim_ano &t1) const
    { 
        t_dim_ano ndim(name + "*" + t1.name);
        for(unsigned int i = 0; i < signature.size(); i++)
        {
            ndim.signature.push_back(signature[i] - t1.signature[i]);
        }
        return ndim;       
    }

    t_dim_ano sqrt () const
    { 
        t_dim_ano ndim("#" + name);
        for(unsigned int i = 0; i < signature.size(); i++)
        {
            ndim.signature.push_back(signature[i]/2);
        }
        return ndim;       
    }

    virtual const string get_signature() const 
    {
        string::size_type c = signature.size();
        string sig(c, '0');
        for(unsigned int i = 0; i < signature.size(); i++)
        {
            sig[i] += signature[signature.size() - i - 1];
        }
        return sig; 
    }
    std::vector<int>    signature;
};

struct t_ano_type
{
    t_ano_type() {};
    t_ano_type(const string& n, const string& bt) 
        : name(n), builtin_type(bt) {}

    virtual const shared_ptr<t_ano_type> get_member_type() const { return shared_ptr<t_ano_type>(); };
    virtual const t_dim_ano* get_dim_ano() const { return 0; };
    virtual const t_space_ano* get_space_ano1() const { return 0; };
    virtual const t_space_ano* get_space_ano2() const { return 0; };
    virtual const bool  is_sampler() const { return false; };


    virtual bool operator ==(const t_ano_type& t) const;
    virtual bool operator !=(const t_ano_type& t) const
    {
        return !(*this == t);
    }

    virtual const string get_signature() const 
    {
        string sig = name;
        if(get_space_ano1())
            sig += get_space_ano1()->get_signature();
        if(get_space_ano2())
            sig += get_space_ano2()->get_signature();
        if(!get_space_ano1() && !get_space_ano2())
        {
            if(get_dim_ano())
            {
                sig += get_dim_ano()->get_signature();
            }
        }
        return sig;
    }
    std::string                 name;
    std::string                 builtin_type;
};

struct t_sampler_type : public t_ano_type
{
    t_sampler_type(const string& n, const string& bt) 
        : t_ano_type(n, bt) {}
    virtual ~t_sampler_type() {}

    virtual const shared_ptr<t_ano_type> get_member_type() const {  return member_type; }
    virtual const bool is_sampler() const { return true; };
    virtual const string get_signature() const 
    {
        return "sampler2D" + member_type->get_signature();
    }
    shared_ptr<t_ano_type>            member_type;
};

struct t_ano_scale_type : public t_ano_type
{
    t_ano_scale_type() : t_ano_type() {}
    t_ano_scale_type(const string& n, const string& bt) 
        : t_ano_type(n, bt){}
    virtual ~t_ano_scale_type() {}
    virtual const shared_ptr<t_ano_type> get_member_type() const {  return shared_ptr<t_ano_type>();  }
    virtual const t_dim_ano* get_dim_ano() const { return &dim_ano; }
    t_dim_ano                   dim_ano;
};

struct t_ano_tuple_type : public t_ano_type
{
    t_ano_tuple_type() : t_ano_type() {}
    t_ano_tuple_type(const string& n, const string& bt) 
        : t_ano_type(n, bt){}
    virtual ~t_ano_tuple_type() {}

    virtual const shared_ptr<t_ano_type> get_member_type() const {  return member_type; }
    virtual const t_dim_ano* get_dim_ano() const { return member_type->get_dim_ano(); }
    shared_ptr<t_ano_type>            member_type;
};


struct t_ano_space_tuple_type : public t_ano_tuple_type
{
    t_ano_space_tuple_type() : t_ano_tuple_type() {}
    t_ano_space_tuple_type(const string& n, const string& bt) 
        : t_ano_tuple_type(n, bt){}
    virtual ~t_ano_space_tuple_type() {}
    virtual const t_space_ano* get_space_ano1() const { return &space_ano1; };
    t_space_ano                 space_ano1;
};

struct t_ano_mat_type : public t_ano_space_tuple_type
{
    t_ano_mat_type() {}
    t_ano_mat_type(const string& n, const string& bt) 
        : t_ano_space_tuple_type(n, bt){}
    virtual ~t_ano_mat_type() {}
    virtual const t_space_ano* get_space_ano2() const { return &space_ano2; };
    t_space_ano                 space_ano2;
};

struct t_var
{
    t_var() {}
    t_var(const std::string &vn) : name(vn) {} 
    t_var(const shared_ptr<t_ano_type> t,const string &vn) 
        : type(t), name(vn) {}
    virtual ~t_var() {};
    shared_ptr<t_ano_type> type;
    string name;
};

struct t_sampler : public t_var
{
    t_sampler() : t_var() {}
    t_sampler(const shared_ptr<t_ano_type> t,const string &vn) 
        : t_var(t, vn) {}
};

typedef t_sampler t_sampler2d;

typedef t_var t_uniform;
typedef t_var t_varying;
typedef t_var t_attribute;

struct t_info
{
    std::map<string, t_uniform> uniforms;
    std::map<string, t_varying> varyings;
    std::map<string, t_attribute> attributes;
    std::map<string, t_sampler> samplers;
};

bool type_check(const std::string &in_src, std::string &out_src, t_info *info = NULL);

#endif //_SAFE_GLSL_TYPE_CHECKER_H_