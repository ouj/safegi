#ifndef _TYPE_TRAIT_H_
#define _TYPE_TRAIT_H_
#include "common.h"
#include <string>

using std::string;

// dimension
template<typename D>
struct dimension_signature {};
template<int da1, int da2, int da3, int da4, int da5, int da6, int da7, int da8>
struct dimension_signature<dimension<da1,da2,da3,da4,da5,da6,da7,da8>>
{
    static const char sig[];
    static const string get(){ return string(sig); }
};
template<int da1, int da2, int da3, int da4, int da5, int da6, int da7, int da8>
const char dimension_signature<dimension<da1,da2,da3,da4,da5,da6,da7,da8>>::sig[] = 
{ '0' + da1, '0' + da2, '0' + da3, '0' + da4, '0' + da5, '0' + da6, '0' + da7, '0' + da8, 0 };


// space
template<typename S>
struct space_signature
{
    static const char *name_;
    static const string get(){ return string(name_); }
};
#define space_signature_define(NAME_S) template <> const char* space_signature<NAME_S>::name_ = #NAME_S;

space_signature_define(mirror_s);
space_signature_define(local_s);
space_signature_define(world_s);
space_signature_define(shape_s);
space_signature_define(lens_s);
space_signature_define(source_s);
space_signature_define(clip_s);

template <typename S>
struct type_signature {};
#define type_signature_no_annotation(NAME_T) template<> struct type_signature<NAME_T>{  static const string get() { return #NAME_T; }};
#define type_signature_with_dimension(NAME_T) template<typename D> struct type_signature<NAME_T<D>> { static const string get() { return #NAME_T + dimension_signature<D>::get();}};
#define type_signature_one_space(NAME_T) template<typename S> struct type_signature<NAME_T<S>> { static const string get() { return #NAME_T + space_signature<S>::get();}};
#define type_signature_two_space(NAME_T) template<typename S0, typename S1> struct type_signature<NAME_T<S0, S1>> { static const string get() { return #NAME_T + space_signature<S0>::get() + space_signature<S1>::get();}};

type_signature_no_annotation(real);
type_signature_no_annotation(tuple2);
type_signature_no_annotation(tuple3);

type_signature_with_dimension(mreal);
type_signature_with_dimension(mtuple3);
type_signature_with_dimension(spectrum);

type_signature_one_space(point);
type_signature_one_space(vector);
type_signature_one_space(direction);
type_signature_one_space(normal);
type_signature_one_space(ray);
type_signature_one_space(isect);
type_signature_one_space(dirSample);
type_signature_one_space(lensSample);
type_signature_one_space(shapeSample);
type_signature_one_space(shadowSample);

type_signature_two_space(frame);
type_signature_two_space(rigidmap);
type_signature_two_space(projmap);

template<typename T>
struct TexId
{
    GLuint id;
};

template<typename T> 
struct type_signature<TexId<T>>
{ 
    static const string get() 
    { 
        return "sampler2D" + type_signature<T>::get();
    }
};

#endif //_TYPE_TRAIT_H_