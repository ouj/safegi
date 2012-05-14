#ifndef _M_GEOM_H_
#define _M_GEOM_H_

#include "m_real.h"
#include "linalg.h"
#include "spaces.h"

struct Material;

template<typename S>
struct point : public mtuple3<length_d> {
    point() : mtuple3<length_d>() { }
    point(const mreal<length_d>& x, const mreal<length_d>& y, const mreal<length_d>& z) : mtuple3<length_d>(x,y,z) { }
};

template<typename S>
struct vector : public mtuple3<length_d> {
    vector() : mtuple3<length_d>() { }
    vector(const mreal<length_d>& x, const mreal<length_d>& y, const mreal<length_d>& z) : mtuple3<length_d>(x,y,z) { }
};

template<typename S>
struct direction : public tuple3 {
	direction() : tuple3(0,0,1) { }
    direction(const real& x, const real& y, const real& z) : tuple3(x,y,z) { }
};

template<typename S>
struct normal : public direction<S> {
	normal() : direction<S>() { }
    normal(const real& x, const real& y, const real& z) : direction<S>(x,y,z) { }
    normal(const direction<S>& d) : direction<S>(d) { }
};

template<typename S>
struct boundingbox {
    point<S> m, M;

    boundingbox(const point<S>& m, const point<S>& M) : m(m), M(M) { } 
};

template<typename S>
inline point<S> operator + (const point<S>& a, const vector<S>& b) {
    return point<S>(a.x+b.x,a.y+b.y,a.z+b.z);
}

template<typename S>
inline vector<S> operator - (const point<S>& a, const point<S>& b) {
    return vector<S>(a.x-b.x,a.y-b.y,a.z-b.z);
}

template<typename S>
inline vector<S> asvector(const point<S>& p) {
    return vector<S>(p.x,p.y,p.z);
}

template<typename S>
inline normal<S> asnormal(const direction<S>& d) {
    return normal<S>(d);
}

template<typename S>
inline mreal<area_d> dot(const vector<S>& a, const vector<S>& b) {
    return a.x*b.x+a.y*b.y+a.z*b.z;
}

template<typename S>
inline real dot(const direction<S>& a, const direction<S>& b) {
    return a.x*b.x+a.y*b.y+a.z*b.z;
}

template<typename S>
inline mreal<length_d> dot(const direction<S>& a, const vector<S>& b) {
    return a.x*b.x+a.y*b.y+a.z*b.z;
}

template<typename S>
inline vector<S> operator + (const vector<S>& a, const vector<S>& b) {
    return vector<S>(a.x+b.x,a.y+b.y,a.z+b.z);
}

template<typename S>
inline vector<S> operator * (const vector<S>& a, const real& b) {
    return vector<S>(a.x*b,a.y*b,a.z*b);
}

template<typename S>
inline vector<S> operator * (const direction<S>& a, const mreal<length_d>& b) {
    return vector<S>(a.x*b,a.y*b,a.z*b);
}

template<typename S>
inline direction<S> operator - (const direction<S>& a) {
    return direction<S>(-a.x,-a.y,-a.z);
}

template<typename S>
inline vector<S> operator - (const vector<S>& a) {
    return vector<S>(-a.x,-a.y,-a.z);
}

template<typename S>
inline vector<S> cross(const direction<S>& a, const vector<S>& b) {
    return vector<S>(a.y*b.z-a.z*b.y, -a.x*b.z+a.z*b.x, a.x*b.y-a.y*b.x);
}

template<typename S>
inline vector<S> cross(const direction<S>& a, const direction<S>& b) {
    return vector<S>(mreal<length_d>(a.y*b.z-a.z*b.y), mreal<length_d>(-a.x*b.z+a.z*b.x), mreal<length_d>(a.x*b.y-a.y*b.x));
}

template<typename S>
inline mreal<area_d> lengthSqr(const vector<S>& v) {
    return dot(v,v);
}

template<typename S>
inline mreal<length_d> length(const vector<S>& v) {
    return sqrt(dot(v,v));
}

template<typename S>
inline vector<S> scale(const vector<S>& v, real sx, real sy, real sz) {
    return vector<S>(v.x*sx,v.y*sy,v.z*sz);
}

template<typename S>
inline direction<S> normalize(const vector<S>& v) {
    mreal<length_d> l = length(v); 
    return direction<S>(v.x/l,v.y/l,v.z/l);
}

template<typename S>
inline real cos(const direction<S>& n, const direction<S>& w) {
    return dot(n,w);
}

template<typename S>
inline mreal<proj_d> abscos(const direction<S>& n, const direction<S>& w) {
    return mreal<proj_d>(abs(dot(n,w)));
}

template<typename S>
inline real poscos(const direction<S>& n, const direction<S>& w) {
    return max(dot(n,w),0.0);
}

template<typename S>
inline direction<S> reflect(const direction<S>& wi) {
    return direction<S>(-wi.x,-wi.y,wi.z);
}

template<typename S>
inline direction<S> bisector(const direction<S>& a, const direction<S>& b) {
    tuple3 r(a.x+b.x,a.y+b.y,a.z+b.z);
    real l = sqrt(r.x*r.x+r.y*r.y+r.z*r.z);
    return direction<S>(r.x/l,r.y/l,r.z/l);
}

template<typename S>
inline direction<S> orthogonal(const direction<S>& a, const direction<S>& b) {
    tuple3 r(a.y*b.z-a.z*b.y, -a.x*b.z+a.z*b.x, a.x*b.y-a.y*b.x);
    real l = sqrt(r.x*r.x+r.y*r.y+r.z*r.z);
    return direction<S>(r.x/l,r.y/l,r.z/l);
}

template<typename S>
inline bool contain(const boundingbox<S>& bbox, const point<S>& p) {
    return p.x >= bbox.m.x && p.x <= bbox.M.x && 
           p.y >= bbox.m.y && p.y <= bbox.M.y &&
           p.z >= bbox.m.z && p.z <= bbox.M.z;
}

template<typename S>
inline point<S> center(const boundingbox<S>& bbox) {
    return point<S>((bbox.m.x+bbox.M.x)/2,(bbox.m.y+bbox.M.y)/2,(bbox.m.z+bbox.M.z)/2);
}

template<typename S>
inline vector<S> size(const boundingbox<S>& bbox) {
    return bbox.M - bbox.m;
}

template<typename S>
inline boundingbox<S> grow(const boundingbox<S>& bbox, const point<S>& p) {
    return boundingbox<S>(point<S>(min(bbox.m.x, p.x), min(bbox.m.y, p.y), min(bbox.m.z, p.z)),
                          point<S>(max(bbox.M.x, p.x), max(bbox.M.y, p.y), max(bbox.M.z, p.z)));
}

template<typename S>
inline boundingbox<S> grow(const boundingbox<S>& bbox1, const boundingbox<S>& bbox2) {
    return boundingbox<S>(point<S>(min(bbox1.m.x, bbox2.m.x), min(bbox1.m.y, bbox2.m.y), min(bbox1.m.z, bbox2.m.z)),
                          point<S>(max(bbox1.M.x, bbox2.M.x), max(bbox1.M.y, bbox2.M.y), max(bbox1.M.z, bbox2.M.z)));
}

// S1 -> S2
// matrices stored should only be rigid
template<typename S1, typename S2>
struct rigidmap {
	mat4 m, mi;

    rigidmap() : m(), mi() { } // identity
    rigidmap(const mat4& m, const mat4& mi) : m(m), mi(mi) { }
};

template<typename S1, typename S2>
struct projmap {
	mat4 m, mi;

    projmap() : m(), mi() { } // identity
    projmap(const mat4& m, const mat4& mi) : m(m), mi(mi) { }
};

template<typename S>
struct ray {
	point<S> e;
	direction<S> d;
	mreal<length_d> tmin, tmax;

    ray() : e(), d(0,0,1), tmin(eps), tmax(inf) { }
    ray(const point<S>& e, const direction<S>& d) : e(e), d(d), tmin(eps), tmax(inf) { }
    ray(const point<S>& e, const direction<S>& d, const mreal<length_d>& dist) : e(e), d(d), tmin(eps_length), tmax(dist-eps_length) { }
    ray(const point<S>& e, const direction<S>& d, const mreal<length_d>& tmin, const mreal<length_d>& tmax) : e(e), d(d), tmin(tmin), tmax(tmax) { }
};

// S1 -> S2
template<typename S1, typename S2>
struct frame {
    point<S1> o;
    direction<S1> x, y;
    normal<S1> z;

    frame() : o(), x(1,0,0), y(0,0,1), z(0,0,1) {  }
    frame(const point<S1>& o, const direction<S1>& x, const direction<S1>& y, const normal<S1>& z) : o(o), x(x), y(y), z(z) { }
    frame(const normal<S1>& z) : o(), z(z) { _fromZ(); }
    frame(const point<S1>& o, const normal<S1>& z) : o(o), z(z) { _fromZ(); }

private:
    void _fromZ() {
        if(cos(direction<S1>(0,1,0),z) != 1) x = orthogonal(z,direction<S1>(0,1,0));
        else x = orthogonal(z,direction<S1>(1,0,0));
        y = orthogonal(z, x);
    }
};

template<typename S>
struct isect {
	bool hit;
	mreal<length_d> t;
    tuple2 uv;
    frame<S,local_s> dp;
    shared_ptr<Material> m;

    isect() : hit(false), t(), uv(), dp() { }
    isect(bool hit, const mreal<length_d>& t, const tuple2& uv, const frame<S,local_s>& dp, shared_ptr<Material> m) : hit(hit), t(t), uv(uv), dp(dp), m(m) { }
};

template<typename S>
inline point<S> eval(const ray<S>& r, const mreal<length_d>& t) {
    return r.e + r.d * t;
}

template<typename S1, typename S2>
inline rigidmap<S1,S2> translate(const vector<S2>& v) { 
    return rigidmap<S1,S2>(translateMat(__asreal(v.x),__asreal(v.y),__asreal(v.z)), translateMat(-__asreal(v.x),-__asreal(v.y),-__asreal(v.z))); 
}

template<typename S1, typename S2>
inline rigidmap<S1,S2> rotate(const direction<S2>& axis, const real& angle) {
    return rigidmap<S1,S2>(rotateMat(axis.x,axis.y,axis.z,angle), rotateMat(axis.x,axis.y,axis.z,-angle));
}

template<typename S1, typename S2>
inline rigidmap<S1,S2> invert(const rigidmap<S2,S1>& m) {
    return rigidmap<S1,S2>(m.mi, m.m);
}

template<typename S1, typename S2, typename S3>
inline rigidmap<S1,S3> operator% (const rigidmap<S2,S3>& a, const rigidmap<S1,S2>& b) {
    return rigidmap<S1,S3>(a.m % b.m, b.mi % a.mi);
}

template<typename S1, typename S2>
inline point<S2> transform(const rigidmap<S1,S2>& m, const point<S1>& p) {
    vec4 v4(__asreal(p.x),__asreal(p.y),__asreal(p.z),1);
    vec4 t = m.m % v4;
    return point<S2>(mreal<length_d>(t.d[0]),mreal<length_d>(t.d[1]),mreal<length_d>(t.d[2])); // units do not change, so use defaults
}

template<typename S1, typename S2>
inline vector<S2> transform(const rigidmap<S1,S2>& m, const vector<S1>& v) {
    vec4 v4(__asreal(v.x),__asreal(v.y),__asreal(v.z),0);
    vec4 t = m.m % v4;
    return vector<S2>(mreal<length_d>(t.d[0]),mreal<length_d>(t.d[1]),mreal<length_d>(t.d[2]));
}

template<typename S1, typename S2>
inline direction<S2> transform(const rigidmap<S1,S2>& m, const direction<S1>& v) {
    vec4 v4(v.x,v.y,v.z,0);
    vec4 t = m.m % v4;
    return direction<S2>(t.d[0],t.d[1],t.d[2]);  // it is rigid, so no normalization
}

template<typename S1, typename S2>
inline normal<S2> transform(const rigidmap<S1,S2>& m, const normal<S1>& v) {
    vec4 v4(v.x,v.y,v.z,0);
    vec4 t = m.m % v4;  // it is rigid, so no inverse transpose
    return normal<S2>(t.d[0],t.d[1],t.d[2]);   // it is rigid, so no normalization
}

template<typename S1, typename S2>
inline ray<S2> transform(const rigidmap<S1,S2>& m, const ray<S1>& r) {
    return ray<S2>(transform(m,r.e), transform(m,r.d), r.tmin, r.tmax);
}

template<typename S1, typename S2, typename S3>
inline frame<S2, S3> transform(const rigidmap<S1, S2>& m, const frame<S1, S3>& dp) {
    frame<S2, S3> ret;
    ret.o = transform(m, dp.o);
    ret.x = transform(m, dp.x);
    ret.y = transform(m, dp.y);
    ret.z = transform(m, dp.z);
    // BUG: x,y possibly wrong
    return ret;
}

template<typename S1, typename S2>
inline isect<S2> transform(const rigidmap<S1,S2>& m, const isect<S1>& is) {
    return isect<S2>(is.hit, is.t, is.uv, transform(m,is.dp), is.m);
}

template<typename S1, typename S2>
inline direction<S2> project(const frame<S1,S2>& dp, const direction<S1>& d) {
    return direction<S2>(dot(dp.x, d), dot(dp.y, d), dot(dp.z, d));
}

template<typename S1, typename S2>
inline direction<S1> unproject(const frame<S1,S2>& dp, const direction<S2>& d) {
    return direction<S1>(dp.x.x * d.x + dp.y.x * d.y + dp.z.x * d.z,
                         dp.x.y * d.x + dp.y.y * d.y + dp.z.y * d.z,
                         dp.x.z * d.x + dp.y.z * d.y + dp.z.z * d.z);
}


#endif
