#include "context.h"
#include <iostream>

context* context::p_context = 0;

context* context::get_ctx()
{
    if(p_context == 0)
        p_context = new context();
    return p_context;
}

void context::cleanup()
{
    space_anos.clear();
    dim_anos.clear();
    typemaps.clear();

    uniforms.clear();
    varyings.clear();
    attributes.clear();
    ins.clear();
    outs.clear();

    functions.clear();
    bin_functions.clear();
    ano_functions.clear();
    defines.clear();

    variables.clear();
    context_stack.clear();

    built_in_code.clear();
    built_in_map.clear();

    samplers.clear();
}

const shared_ptr<t_ano_type> context::get_variable_type(const string &vname)
{
    //// local variables have the priority
    variable_it var_it = variables.find(vname);
    if(var_it != variables.end())
    {
        return (var_it->second.type);
    }
    in_it i_it = ins.find(vname);
    if(i_it != ins.end())
    {
        return (i_it->second.type);
    }
    out_it o_it = outs.find(vname);
    if(o_it != outs.end())
    {
        return (o_it->second.type);
    }
    uniform_it uit = uniforms.find(vname);
    if(uit != uniforms.end())
    {
        return (uit->second.type);
    }

    varying_it vit = varyings.find(vname);
    if(vit != varyings.end())
    {
        return (vit->second.type);
    }

    attribute_it ait = attributes.find(vname);
    if(ait != attributes.end())
    {
        return (ait->second.type);
    }

    return shared_ptr<t_ano_type>();
}

shared_ptr<t_ano_type> cx_typemap::substantial(const t_ano *ano1, const t_ano *ano2)
{
    //*** _typemap real 				float;
    //
    if(ano1 || ano2)
    {
        assert(false);
        return shared_ptr<t_ano_type>();
    }
    return shared_ptr<t_ano_type>(new t_ano_type(name, builtin_type));
}

shared_ptr<t_ano_type> cx_scale_typemap::substantial(const t_ano *ano1, const t_ano *ano2)
{
    //** _typemap mreal<-dimen-> 	float;
    //
    if(!ano1 || ano2)
    {
        assert(false);
        return shared_ptr<t_ano_type>();
    }
    t_ano_scale_type *type = new t_ano_scale_type(name, builtin_type);
    const t_dim_ano *dim_ano = dynamic_cast<const t_dim_ano*>(ano1);
    if(!dim_ano)
    {
        assert(false);
        return shared_ptr<t_ano_type>();
    }
    else
    {
        type->dim_ano = *dim_ano;
        return shared_ptr<t_ano_type>(type);
    }
}

shared_ptr<t_ano_type> cx_tuple_typemap::substantial(const t_ano *ano1, const t_ano *ano2)
{
    //** _typemap tuple3				vec3{real};
    //** _typemap spectrum			    vec3{mreal<-dimen->};
    if(ano2)
    {
        assert(false);
        return shared_ptr<t_ano_type>();
    }

    shared_ptr<t_ano_type> mtype = this->member_typemap->substantial(ano1);
    if(!mtype.get())
    {
        assert(false);
        return shared_ptr<t_ano_type>();
    }
    else
    {
        t_ano_tuple_type *type = new t_ano_tuple_type(name, builtin_type);
        type->member_type = mtype;
        return shared_ptr<t_ano_type>(type);
    }
}

shared_ptr<t_ano_type> cx_space_tuple_typemap::substantial(const t_ano *ano1, const t_ano *ano2)
{
    //** _typemap vector<-space-> 	vec3{mreal<length_d>};
    if(!ano1 && ano2)
    {
        assert(false);
        return shared_ptr<t_ano_type>();
    }

    const t_space_ano* space_ano = dynamic_cast<const t_space_ano*>(ano1);
    if(!space_ano)
    {
        assert(false);
        return shared_ptr<t_ano_type>();
    }
    else
    {
        shared_ptr<t_ano_type> mtype = this->member_type;
        if(!mtype.get())
        {
            assert(false);
            return shared_ptr<t_ano_type>();
        }
        else
        {
            t_ano_space_tuple_type *type = new t_ano_space_tuple_type(name, builtin_type);
            type->space_ano1 = *space_ano;
            type->member_type = mtype;
            return shared_ptr<t_ano_type>(type);
        }
    }
}

shared_ptr<t_ano_type> cx_mat_typemap::substantial(const t_ano *ano1, const t_ano *ano2)
{
    //** _typemap vector<-space-> 	vec3{mreal<length_d>};
    if(!ano1 && ano2)
    {
        assert(false);
        return shared_ptr<t_ano_type>();
    }
    
    const t_space_ano* space_ano1 = dynamic_cast<const t_space_ano*>(ano1);
    if(!space_ano1)
    {
        assert(false);
        return shared_ptr<t_ano_type>();
    }
    const t_space_ano* space_ano2 = dynamic_cast<const t_space_ano*>(ano2);
    if(!space_ano2)
    {
        assert(false);
        return shared_ptr<t_ano_type>();
    }

    shared_ptr<t_ano_type> mtype = this->member_type;
    if(!mtype.get())
    {
        assert(false);
        return shared_ptr<t_ano_type>();
    }
    else
    {
        t_ano_mat_type *type = new t_ano_mat_type(name, builtin_type);
        type->space_ano1 = *space_ano1;
        type->space_ano2 = *space_ano2;
        type->member_type = mtype;
        return shared_ptr<t_ano_type>(type);
    }
}

shared_ptr<t_ano_type> context::deduct_type(const string &name, const t_ano* ano1, const t_ano* ano2)
{
    shared_ptr<cx_typemap> typemap = typemaps.find(name)->second;

    if(typemap.get())
        return typemap->substantial(ano1, ano2);
    else
    {
        assert(typemap.get());
        return shared_ptr<t_ano_type>();
    }
}

shared_ptr<t_ano_type> context::check_function(string &fname, const vector<shared_ptr<t_ano_type>> &arg_type_list)
{
    shared_ptr<t_ano_type> type;
    for(unsigned int idx = 0; idx < functions.size(); idx++)
    {
        if(functions[idx].name == fname)
        {
            //number of argument and parameter is the same.
            type = functions[idx].accept(arg_type_list);
            if(type.get())
            {
                return type;
            }
        }
    }

    for(unsigned int idx = 0; idx < ano_functions.size(); idx++)
    {
        if(ano_functions[idx].name == fname)
        {
            //number of argument and parameter is the same.
            type = ano_functions[idx].accept(arg_type_list);
            if(type.get())
            {
                return type;
            }
        }
    }

    for(unsigned int idx = 0; idx < bin_functions.size(); idx++)
    {
        if(bin_functions[idx].name == fname)
        {
            string code;
            //number of argument and parameter is the same.
            type = bin_functions[idx].accept(arg_type_list, &code);
            if(type.get())
            {
                fname = bin_functions[idx].signature;
                if(!code.empty() && !built_in_map[bin_functions[idx].signature])
                {
                    built_in_code += code;
                    built_in_map[bin_functions[idx].signature] = true;
                }
                return type;
            }
        }
    }

    for(unsigned int idx = 0; idx < bin_ano_functions.size(); idx++)
    {
        if(bin_ano_functions[idx].name == fname)
        {
            string code;
            //number of argument and parameter is the same.
            type = bin_ano_functions[idx].accept(arg_type_list, &code);
            if(type.get())
            {
                fname = bin_ano_functions[idx].signature;
                if(!code.empty() && !built_in_map[bin_ano_functions[idx].signature])
                {
                    built_in_code += code;
                    built_in_map[bin_ano_functions[idx].signature] = true;
                }
                return type;
            }
        }
    }
    return type;
}

shared_ptr<t_ano_type> cx_function::accept(const vector<shared_ptr<t_ano_type>> &arg_type_list)
{
    if(tparas.size() != arg_type_list.size())
        return shared_ptr<t_ano_type>();
    for(unsigned int i = 0; i < tparas.size(); i++)
    {
        if((*tparas[i]) != (*arg_type_list[i]))
            return shared_ptr<t_ano_type>();
    }
    return this->type;
}

shared_ptr<t_ano_type> cx_bin_function::accept(const vector<shared_ptr<t_ano_type>> &arg_type_list, string* code)
{
    if(paras.size() != arg_type_list.size())
        return shared_ptr<t_ano_type>();
    
    string func_sig;
    func_sig += this->type->builtin_type + ' ' + signature + '(';
    for(unsigned int i = 0; i < paras.size(); i++)
    {
        if((*paras[i].type) != (*arg_type_list[i]))
            return shared_ptr<t_ano_type>();
        else
        {
            if(i != 0)
                func_sig += ',';
            func_sig += paras[i].type->builtin_type;
            func_sig += ' ' + paras[i].name;
            if(arg_type_list[i]->get_space_ano2())
            {
                func_sig += "[2]"; //hack for matrix array;
            }
        }
    }

    if(code)
    {
        *code = func_sig + ")\n{\n" + raw_code + "\n}\n";
    }

    return this->type;
}


shared_ptr<t_ano_type> cx_ano_function::accept(const vector<shared_ptr<t_ano_type>> &arg_type_list)
{
    if(paralist.size() != arg_type_list.size())
        return shared_ptr<t_ano_type>();
    map<string, const t_ano*> ano_map;
    for(unsigned int i = 0; i < ano_list.size(); i++)
    {
        ano_map[ano_list[i]] = NULL;
    }

    for(unsigned int i = 0; i < this->paralist.size(); i++)
    {
        const shared_ptr<t_ano_type> &arg_type = arg_type_list[i];
        const cx_generic_ano_type& para_type = paralist[i].type;
        if(arg_type->name != para_type.name)
        {
            return shared_ptr<t_ano_type>();
        }

        assert(para_type.op == cx_generic_ano_type::NONE); //argument should not have dim op.

        const t_space_ano* space_ano1 = arg_type->get_space_ano1();
        const t_space_ano* space_ano2 = arg_type->get_space_ano2();
        const t_dim_ano* dim_ano = arg_type->get_dim_ano();

        if(space_ano2 && !para_type.ano2.empty())
        {
            ano_map[para_type.ano2] = space_ano2;
        }
        if(space_ano1 && !para_type.ano1.empty())
        {
            ano_map[para_type.ano1] = space_ano1;
        }
        if(!space_ano1 && !space_ano2 && dim_ano && !para_type.ano1.empty())
        {
            ano_map[para_type.ano1] = dim_ano;
        }
    }

    cx_generic_ano_type &rt = ret_type;
    const t_ano *a1 = NULL;
    const t_ano *a2 = NULL;

    if(!rt.ano1.empty())
    {
        a1 = ano_map[rt.ano1];
        if(!a1) return shared_ptr<t_ano_type>();
    }
    if(!rt.ano2.empty())
    {
        a2 = ano_map[rt.ano2];
        if(!a2) return shared_ptr<t_ano_type>();
    }

    if(rt.op == cx_generic_ano_type::NONE)
    {
        return context::get_ctx()->deduct_type(rt.name, a1, a2);   
    }
    else
    {
        const t_dim_ano *da1 = dynamic_cast<const t_dim_ano*>(a1);
        const t_dim_ano *da2 = dynamic_cast<const t_dim_ano*>(a2);

        switch(rt.op)
        {
        case cx_generic_ano_type::MUL:
            {
                assert(da1 && da2);
                if(!da1 || !da2)
                    return shared_ptr<t_ano_type>();
                t_dim_ano ndim = (*da1) * (*da2);
                return context::get_ctx()->deduct_type(rt.name, &ndim);   
                break;
            }
        case cx_generic_ano_type::DIV:
            {
                assert(da1 && da2);
                if(!da1 || !da2)
                    return shared_ptr<t_ano_type>();
                t_dim_ano ndim = (*da1) / (*da2);
                return context::get_ctx()->deduct_type(rt.name, &ndim);   
                break;
            }
        case cx_generic_ano_type::SQRT:
            {
                assert(da1);
                if(!da1)
                    return shared_ptr<t_ano_type>();
                t_dim_ano ndim = da1->sqrt();
                return context::get_ctx()->deduct_type(rt.name, &ndim);   
                break;
            }
        default:
            assert(false);
        }
    }

    return shared_ptr<t_ano_type>();
}


shared_ptr<t_ano_type> cx_bin_ano_function::accept(const vector<shared_ptr<t_ano_type>> &arg_type_list, string* code)
{
    if(paralist.size() != arg_type_list.size())
        return shared_ptr<t_ano_type>();
    map<string, const t_ano*> ano_map;
    for(unsigned int i = 0; i < ano_list.size(); i++)
    {
        ano_map[ano_list[i]] = NULL;
    }

    string func_sig = signature;
    func_sig += "(";

    for(unsigned int i = 0; i < this->paralist.size(); i++)
    {
        const shared_ptr<t_ano_type> &arg_type = arg_type_list[i];
        const cx_generic_ano_type& para_type = paralist[i].type;
        if(arg_type->name != para_type.name)
        {
            return shared_ptr<t_ano_type>();
        }
        if(i != 0)
            func_sig += ", ";
        func_sig += arg_type->builtin_type + " " + paralist[i].name;

        if(arg_type_list[i]->get_space_ano2())
        {
            func_sig += "[2]"; //hack for matrix array;
        }

        assert(para_type.op == cx_generic_ano_type::NONE); //argument should not have dim op.

        const t_space_ano* space_ano1 = arg_type->get_space_ano1();
        const t_space_ano* space_ano2 = arg_type->get_space_ano2();
        const t_dim_ano* dim_ano = arg_type->get_dim_ano();

        if(space_ano2 && !para_type.ano2.empty())
        {
            ano_map[para_type.ano2] = space_ano2;
        }
        if(space_ano1 && !para_type.ano1.empty())
        {
            ano_map[para_type.ano1] = space_ano1;
        }
        if(!space_ano1 && !space_ano2 && dim_ano && !para_type.ano1.empty())
        {
            ano_map[para_type.ano1] = dim_ano;
        }
    }
    func_sig += ")\n{\n" + raw_code + "\n}\n";
    shared_ptr<t_ano_type> return_type;

    cx_generic_ano_type &rt = ret_type;
    const t_ano *a1 = NULL;
    const t_ano *a2 = NULL;

    if(!rt.ano1.empty())
    {
        a1 = ano_map[rt.ano1];
        if(!a1)
        {
            space_ano_it sit = context::get_ctx()->space_anos.find(rt.ano1);
            if(sit != context::get_ctx()->space_anos.end())
            {
                a1 = &sit->second;
            }
            dim_ano_it dit = context::get_ctx()->dim_anos.find(rt.ano1);
            if(dit != context::get_ctx()->dim_anos.end())
            {
                a1 = &dit->second;
            }
            if(!a1)
            {
                return shared_ptr<t_ano_type>();
            }
        }
    }
    if(!rt.ano2.empty())
    {
        a2 = ano_map[rt.ano2];
        if(!a2) 
        {
            space_ano_it sit = context::get_ctx()->space_anos.find(rt.ano2);
            if(sit != context::get_ctx()->space_anos.end())
            {
                a2 = &sit->second;
            }
            dim_ano_it dit = context::get_ctx()->dim_anos.find(rt.ano2);
            if(dit != context::get_ctx()->dim_anos.end())
            {
                a2 = &dit->second;
            }
            if(!a2)
            {
                return shared_ptr<t_ano_type>();
            }
        }
    }

    if(rt.op == cx_generic_ano_type::NONE)
    {
        return_type = context::get_ctx()->deduct_type(rt.name, a1, a2);   
    }
    else
    {
        const t_dim_ano *da1 = dynamic_cast<const t_dim_ano*>(a1);
        const t_dim_ano *da2 = dynamic_cast<const t_dim_ano*>(a2);

        switch(rt.op)
        {
        case cx_generic_ano_type::MUL:
            {
                assert(da1 && da2);
                if(!da1 || !da2)
                    return shared_ptr<t_ano_type>();
                t_dim_ano ndim = (*da1) * (*da2);
                return_type = context::get_ctx()->deduct_type(rt.name, &ndim);   
                break;
            }
        case cx_generic_ano_type::DIV:
            {
                assert(da1 && da2);
                if(!da1 || !da2)
                    return shared_ptr<t_ano_type>();
                t_dim_ano ndim = (*da1) / (*da2);
                 return_type = context::get_ctx()->deduct_type(rt.name, &ndim);   
                break;
            }
        case cx_generic_ano_type::SQRT:
            {
                assert(da1);
                if(!da1)
                    return shared_ptr<t_ano_type>();
                t_dim_ano ndim = da1->sqrt();
                return_type = context::get_ctx()->deduct_type(rt.name, &ndim);   
                break;
            }
        default:
            assert(false);
        }
    }

    if(return_type.get())
    {
        if(code)
            *code = return_type->builtin_type + " " + func_sig;
        return return_type;
    }
    else
        return shared_ptr<t_ano_type>();
}

bool context::check_type_cast(shared_ptr<t_ano_type> target, const vector<shared_ptr<t_ano_type>> &arg_type_list)
{
    return true;
}