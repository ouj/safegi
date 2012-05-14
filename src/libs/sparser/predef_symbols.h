#ifndef _PREDEF_SYMBOLS_H_
#define _PREDEF_SYMBOLS_H_
#include <string>

#define PREDEF_SYMBOL_CODE(...) #__VA_ARGS__

const std::string predef_symbol_code = PREDEF_SYMBOL_CODE( /*Phone vertex shader code*/
_def_space_ano mirror_s;
_def_space_ano local_s;
_def_space_ano world_s;
_def_space_ano shape_s;
_def_space_ano lens_s;
_def_space_ano source_s;
_def_space_ano clip_s;

_def_dimen_ano unit_d 		<0, 0, 0, 0, 0, 0, 0, 0>;
_def_dimen_ano rho_d		<0, 0, 0, 0, 0, 0, 0, 0>;
_def_dimen_ano length_d		<0, 0, 0, 0, 0, 0, 0, 1>;
_def_dimen_ano time_d 		<0, 0, 0, 0, 0, 0, 1, 0>;
_def_dimen_ano energy_d		<0, 0, 0, 0, 0, 1, 0, 0>;
_def_dimen_ano solidangle_d	<0, 0, 0, 0, 1, 0, 0, 0>;
_def_dimen_ano angle_d 		<0, 0, 0, 1, 0, 0, 0, 0>;
_def_dimen_ano proj_d 		<0, 0, 1, 0, 0, 0, 0, 0>;

_def_dimen_ano area_d							<length_d * length_d>;
_def_dimen_ano invsolidangle_d					<unit_d / solidangle_d>;
_def_dimen_ano invproj_d						<unit_d / proj_d>;
_def_dimen_ano invtime_d						<unit_d / time_d>;
_def_dimen_ano projsolidangle_d					<proj_d * solidangle_d>;
_def_dimen_ano invarea_d						<unit_d / area_d>;
_def_dimen_ano invprojarea_d					<invarea_d * invproj_d>;
_def_dimen_ano power_d							<energy_d * invtime_d>;
_def_dimen_ano irradiance_d						<power_d * invarea_d>;
_def_dimen_ano intensity_d						<power_d * invsolidangle_d>;
// _def_dimen_ano radiance_d					<irradiance_d * invsolidangle_d>;
_def_dimen_ano invsolidangle_d_irradiance_d 	<irradiance_d * invsolidangle_d>;
_def_dimen_ano radiance_d						<invsolidangle_d_irradiance_d * invproj_d>;
_def_dimen_ano brdf_d							<radiance_d / irradiance_d>;
_def_dimen_ano invradiance_d					<unit_d / radiance_d>;

_typemap real 				float;
_typemap mreal<-dimen-> 	float;
_typemap tuple3				vec3{real};
_typemap tuple2 			vec2{real};
_typemap mtuple3 			vec3{mreal<-dimen->};
_typemap spectrum			vec3{mreal<-dimen->};
_typemap alpha_spectrum 	vec4{mreal<-dimen->};

_typemap rigidmap<-space-, -space-> mat4{real};
_typemap projmap<-space-, -space-> mat4{real};

_typemap direction<-space-> vec3{real};
_typemap normal<-space->    vec3{real};
_typemap point<-space->		vec3{mreal<length_d>};
_typemap vector<-space-> 	vec3{mreal<length_d>};
_typemap hpoint<-space->	vec4{mreal<length_d>};

_built_in <S1>
point<S1> get_point(hpoint<S1> wp)
@get_point@--
return vec3(wp.xyz);
--@

_built_in <S1>
point<S1> homogenize(hpoint<S1> hp)
@homogenize@--
return vec3(hp.xyz) / hp.w;
--@

_built_in <S1>
normal<S1> __asnormal(direction<S1> wp)
@as_normal@--
return vec3(wp.xyz);
--@

_built_in <S1>
hpoint<clip_s> project(projmap<S1, clip_s> m, point<S1> p)
@project@--
    return m[0] * vec4(p.xyz, 1.0);
--@

_built_in
alpha_spectrum<radiance_d> attach_alpha(spectrum<radiance_d> c, real a)
@attach_alpha@--
    return  vec4(c.xyz, a);
--@

_built_in<S1, S2>
point<S2> transform(rigidmap<S1,S2> m, point<S1> p)
@transform_point@--
    return (m[0] * vec4(p.xyz, 1.0)).xyz;
--@

_built_in<S1, S2>
direction<S2> transform(rigidmap<S1,S2> m, direction<S1> p)
@transform_direction@--
    return (m[0] * vec4(p.xyz, 0.0)).xyz;
--@

_built_in<S1, S2>
normal<S2> transform(rigidmap<S1,S2> m, normal<S1> p)
@transform_normal@--
    return (m[0] * vec4(p.xyz, 0.0)).xyz;
--@

_built_in<S1, S2>
vector<S2> transform(rigidmap<S1,S2> m, vector<S1> p)
@transform_vector@--
    return (m[0] * vec4(p.xyz, 0.0)).xyz;
--@

_built_in<S1, S2>
point<S2> invert_transform(rigidmap<S1,S2> m, point<S1> p)
@invert_transform_point@--
    return (m[1] * vec4(p.xyz, 1.0)).xyz;
--@

_built_in<S1, S2>
direction<S2> invert_transform(rigidmap<S1,S2> m, direction<S1> p)
@invert_transform_direction@--
    return (m[1] * vec4(p.xyz, 0.0)).xyz;
--@

_built_in<S1, S2>
normal<S2> invert_transform(rigidmap<S1,S2> m, normal<S1> p)
@invert_transform_normal@--
    return (m[1] * vec4(p.xyz, 0.0)).xyz;
--@

_built_in<S1, S2>
vector<S2> invert_transform(rigidmap<S1,S2> m, vector<S1> p)
@invert_transform_vector@--
    return (m[1] * vec4(p.xyz, 0.0)).xyz;
--@

_built_in<S1>
real cos(direction<S1> n, direction<S1> w) 
@cos_direction@--
    return dot(n,w);
--@

_built_in<S1>
real cos(normal<S1> n, direction<S1> w) 
@cos_direction@--
    return dot(n,w);
--@

_built_in<S1>
real cos(direction<S1> n, normal<S1> w) 
@cos_normal@--
    return dot(n,w);
--@

_built_in<S1>
real cos(normal<S1> n, normal<S1> w) 
@cos_normal@--
    return dot(n,w);
--@

_built_in<S1>
real abscos(direction<S1> n, direction<S1> w)
@abscos_direction@--
    return abs(dot(n,w));
--@

_built_in<S1>
real abscos(normal<S1> n, direction<S1> w)
@abscos_normal@--
    return abs(dot(n,w));
--@

_built_in<S1>
real abscos(direction<S1> n, normal<S1> w)
@abscos_direction@--
    return abs(dot(n,w));
--@

_built_in<S1>
real abscos(normal<S1> n, normal<S1> w)
@abscos_normal@--
    return abs(dot(n,w));
--@

_built_in<S1>
mreal<proj_d> poscos(direction<S1> n, direction<S1> w)
@poscos_direction@--
    return max(dot(n,w),0.0);
--@

_built_in<S1>
mreal<proj_d> poscos(normal<S1> n, direction<S1> w)
@poscos_direction@--
    return max(dot(n,w),0.0);
--@

_built_in<S1>
mreal<proj_d> poscos(direction<S1> n, normal<S1> w)
@poscos_normal@--
    return max(dot(n,w),0.0);
--@

_built_in<S1>
mreal<proj_d> poscos(normal<S1> n, normal<S1> w)
@poscos_normal@--
    return max(dot(n,w),0.0);
--@

_built_in<S1>
mreal<area_d> lengthSqr(vector<S1> v)
@vector_lengthSqr@--
    return dot(v,v);
--@

_convention
real _operator + (real, real);
_convention
real _operator - (real, real);
_convention
real _operator * (real, real);
_convention
real _operator / (real, real);

_convention<D1>
mreal<D1> _operator + (mreal<D1>, mreal<D1>);
_convention<D1>
mreal<D1> _operator - (mreal<D1>, mreal<D1>);
_convention<D1, D2>
mreal<D1*D2> _operator * (mreal<D1>, mreal<D2>);
_convention<D1, D2>
mreal<D1/D2> _operator / (mreal<D1>, mreal<D2>);
_convention<D1>
real _operator / (mreal<D1>, mreal<D1>);
_convention<D1>
mreal<D1> _operator * (mreal<D1>, real);
_convention<D1>
mreal<D1> _operator / (mreal<D1>, real);
_convention<D1>
spectrum<D1> _operator + (spectrum<D1>, spectrum<D1>);
_convention<D1>
spectrum<D1> _operator - (spectrum<D1>, spectrum<D1>);
_convention<D1, D2>
spectrum<D1*D2> _operator * (spectrum<D1>, spectrum<D2>);
_convention<D1, D2>
spectrum<D1/D2> _operator / (spectrum<D1>, spectrum<D2>);
_convention<D1>
spectrum<D1> _operator* (spectrum<D1>, real);
_convention<D1>
spectrum<D1> _operator/ (spectrum<D1>, real);
_convention<D1, D2>
spectrum<D1*D2> _operator* (spectrum<D1>, mreal<D2>);
_convention<D1, D2>
spectrum<D1/D2> _operator/ (spectrum<D1>, mreal<D2>);

_convention
real max(real a, real b);
_convention
real min(real c, real d);
_convention
real pow(real n, real u);
_convention
real abs(real n);

_convention<S1>
vector<S1> _operator - (point<S1>, point<S1>);
_convention<S1>
direction<S1> normalize(vector<S1>);
_convention<S1>
direction<S1> reflect(direction<S1>, direction<S1>);
_convention<S1>
normal<S1> reflect(normal<S1>, normal<S1>);
_convention<S1>
direction<S1> reflect(direction<S1>, normal<S1>);
_convention<S1>
real dot(direction<S1>, direction<S1>);
_convention<S1>
real dot(normal<S1>, normal<S1>);
_convention<S1>
real dot(normal<S1>, direction<S1>);


in hpoint<shape_s> gl_Vertex;
in direction<shape_s> gl_Normal;
out hpoint<clip_s> gl_Position;
out alpha_spectrum<radiance_d> gl_FragColor;
);


#endif // _PREDEF_SYMBOLS_H_