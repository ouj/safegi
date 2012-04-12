#ifndef _U_GEOM_H_
#define _U_GEOM_H_

#include "real.h"
#include "linalg.h"

struct Material;

struct point : public tuple3 {
    point() : tuple3() { }
    point(const real& x, const real& y, const real& z) : tuple3(x,y,z) { }
};

struct vector : public tuple3 {
    vector() : tuple3() { }
    vector(const real& x, const real& y, const real& z) : tuple3(x,y,z) { }
};

struct direction : public tuple3 {
	direction() : tuple3(0,0,1) { }
    direction(const real& x, const real& y, const real& z) : tuple3(x,y,z) { }
};

struct normal : public direction {
	normal() : direction() { }
    normal(const real& x, const real& y, const real& z) : direction(x,y,z) { }
    normal(const direction& d) : direction(d) { }
};

struct boundingbox {
    point m, M;

    boundingbox(const point& m, const point& M) : m(m), M(M) { } 
};

inline point operator + (const point& a, const vector& b) {
    return point(a.x+b.x,a.y+b.y,a.z+b.z);
}

inline vector operator - (const point& a, const point& b) {
    return vector(a.x-b.x,a.y-b.y,a.z-b.z);
}

inline vector asvector(const point& p) {
    return vector(p.x,p.y,p.z);
}

inline normal asnormal(const direction& d) {
    return normal(d);
}

inline real dot(const vector& a, const vector& b) {
    return a.x*b.x+a.y*b.y+a.z*b.z;
}

inline real dot(const direction& a, const direction& b) {
    return a.x*b.x+a.y*b.y+a.z*b.z;
}

inline real dot(const direction& a, const vector& b) {
    return a.x*b.x+a.y*b.y+a.z*b.z;
}

inline vector operator + (const vector& a, const vector& b) {
    return vector(a.x+b.x,a.y+b.y,a.z+b.z);
}

inline vector operator * (const vector& a, const real& b) {
    return vector(a.x*b,a.y*b,a.z*b);
}

inline vector operator * (const direction& a, const real& b) {
    return vector(a.x*b,a.y*b,a.z*b);
}

inline direction operator - (const direction& a) {
    return direction(-a.x,-a.y,-a.z);
}

inline vector operator - (const vector& a) {
    return vector(-a.x,-a.y,-a.z);
}

inline vector cross(const direction& a, const direction& b) {
    return vector(a.y*b.z-a.z*b.y, -a.x*b.z+a.z*b.x, a.x*b.y-a.y*b.x);
}

inline real lengthSqr(const vector& v) {
    return dot(v,v);
}

inline real length(const vector& v) {
    return sqrt(dot(v,v));
}

inline vector scale(const vector& v, real sx, real sy, real sz) {
    return vector(v.x*sx,v.y*sy,v.z*sz);
}

inline direction normalize(const vector& v) {
    real l = length(v);
    return direction(v.x/l,v.y/l,v.z/l);
}

inline real cos(const direction& n, const direction& w) {
    return dot(n,w);
}

inline real abscos(const direction& n, const direction& w) {
    return abs(dot(n,w));
}

inline real poscos(const direction& n, const direction& w) {
    return max(dot(n,w),0.0);
}

inline direction reflect(const direction& wi) {
    return direction(-wi.x,-wi.y,wi.z);
}

inline direction bisector(const direction& a, const direction& b) {
    tuple3 r(a.x+b.x,a.y+b.y,a.z+b.z);
    real l = sqrt(r.x*r.x+r.y*r.y+r.z*r.z);
    return direction(r.x/l,r.y/l,r.z/l);
}

inline direction orthogonal(const direction& a, const direction& b) {
    tuple3 r(a.y*b.z-a.z*b.y, -a.x*b.z+a.z*b.x, a.x*b.y-a.y*b.x);
    real l = sqrt(r.x*r.x+r.y*r.y+r.z*r.z);
    return direction(r.x/l,r.y/l,r.z/l);
}

inline bool contain(const boundingbox& bbox, const point& p) {
    return p.x >= bbox.m.x && p.x <= bbox.M.x && 
           p.y >= bbox.m.y && p.y <= bbox.M.y &&
           p.z >= bbox.m.z && p.z <= bbox.M.z;
}

inline point center(const boundingbox& bbox) {
    return point((bbox.m.x+bbox.M.x)/2,(bbox.m.y+bbox.M.y)/2,(bbox.m.z+bbox.M.z)/2);
}

inline vector size(const boundingbox& bbox) {
    return bbox.M - bbox.m;
}

inline boundingbox grow(const boundingbox& bbox, const point& p) {
    return boundingbox(point(min(bbox.m.x, p.x), min(bbox.m.y, p.y), min(bbox.m.z, p.z)),
                       point(max(bbox.M.x, p.x), max(bbox.M.y, p.y), max(bbox.M.z, p.z)));
}

inline boundingbox grow(const boundingbox& bbox1, const boundingbox& bbox2) {
    return boundingbox(point(min(bbox1.m.x, bbox2.m.x), min(bbox1.m.y, bbox2.m.y), min(bbox1.m.z, bbox2.m.z)),
                       point(max(bbox1.M.x, bbox2.M.x), max(bbox1.M.y, bbox2.M.y), max(bbox1.M.z, bbox2.M.z)));
}

struct rigidmap {
	mat4 m, mi;

    rigidmap() : m(), mi() { } // identity
    rigidmap(const mat4& m, const mat4& mi) : m(m), mi(mi) { }
};

struct projmap {
	mat4 m, mi;

    projmap() : m(), mi() { } // identity
    projmap(const mat4& m, const mat4& mi) : m(m), mi(mi) { }
};

struct ray {
	point e;
	direction d;
	real tmin, tmax;

    ray() : e(), d(0,0,1), tmin(eps), tmax(inf) { }
    ray(const point& e, const direction& d) : e(e), d(d), tmin(eps), tmax(inf) { }
    ray(const point& e, const direction& d, const real& dist) : e(e), d(d), tmin(eps), tmax(dist-eps) { }
    ray(const point& e, const direction& d, const real& tmin, const real& tmax) : e(e), d(d), tmin(tmin), tmax(tmax) { }
};

struct frame {
    point o;
    direction x, y;
    normal z;

    frame() : o(), x(1,0,0), y(0,0,1), z(0,0,1) {  }
    frame(const point& o, const direction& x, const direction& y, const normal& z) : o(o), x(x), y(y), z(z) { }
    frame(const normal& z) : o(), z(z) { _fromZ(); }
    frame(const point& o, const normal& z) : o(o), z(z) { _fromZ(); }

private:
    void _fromZ() {
        if(cos(direction(0,1,0),z) != 1) x = orthogonal(z,direction(0,1,0));
        else x = orthogonal(z,direction(1,0,0));
        y = orthogonal(z, x);
    }
};

struct isect {
	bool hit;
	real t;
    tuple2 uv;
    frame dp;
    shared_ptr<Material> m;

    isect() : hit(false), t(), uv(), dp() { }
    isect(bool hit, const real& t, const tuple2& uv, const frame& dp, shared_ptr<Material> m) : hit(hit), t(t), uv(uv), dp(dp), m(m) { }
};

inline point eval(const ray& r, const real& t) {
    return r.e + r.d * t;
}

inline rigidmap translate(const vector& v) { 
    return rigidmap(translateMat(v.x,v.y,v.z), translateMat(-v.x,-v.y,-v.z)); 
}

inline rigidmap rotate(const direction& axis, const real& angle) {
    return rigidmap(rotateMat(axis.x,axis.y,axis.z,angle), rotateMat(axis.x,axis.y,axis.z,-angle));
}

inline rigidmap invert(const rigidmap& m) {
    return rigidmap(m.mi, m.m);
}

inline rigidmap operator% (const rigidmap& a, const rigidmap& b) {
    return rigidmap(a.m % b.m, b.mi % a.mi);
}

inline point transform(const rigidmap& m, const point& p) {
    vec4 v4(p.x,p.y,p.z,1);
    vec4 t = m.m % v4;
    return point(t.d[0],t.d[1],t.d[2]);
}

inline vector transform(const rigidmap& m, const vector& v) {
    vec4 v4(v.x,v.y,v.z,0);
    vec4 t = m.m % v4;
    return vector(t.d[0],t.d[1],t.d[2]);
}

inline direction transform(const rigidmap& m, const direction& v) {
    vec4 v4(v.x,v.y,v.z,0);
    vec4 t = m.m % v4;
    // return normalize(vector(t.d[0],t.d[1],t.d[2]));
    return direction(t.d[0],t.d[1],t.d[2]); // it is rigid, so no normalization
}

inline normal transform(const rigidmap& m, const normal& v) {
    vec4 v4(v.x,v.y,v.z,0);
    //vec4 t = transpose(m.mi) % v4;
    //return normal(normalize(vector(t.d[0],t.d[1],t.d[2])));
    vec4 t = m.m % v4;  // it is rigid, so no inverse transpose
    return normal(t.d[0],t.d[1],t.d[2]);  // it is rigid, so no normalization
}

inline ray transform(const rigidmap& m, const ray& r) {
    return ray(transform(m,r.e), transform(m,r.d), r.tmin, r.tmax);
}

inline frame transform(const rigidmap& m, const frame& dp) {
    frame ret;
    ret.o = transform(m, dp.o);
    ret.x = transform(m, dp.x);
    ret.y = transform(m, dp.y);
    ret.z = transform(m, dp.z);
    // BUG: x,y possibly wrong
    return ret;
}

inline isect transform(const rigidmap& m, const isect& is) {
    return isect(is.hit, is.t, is.uv, transform(m,is.dp), is.m);
}

inline direction project(const frame& dp, const direction& d) {
    return direction(dot(dp.x, d), dot(dp.y, d), dot(dp.z, d));
}

inline direction unproject(const frame& dp, const direction& d) {
    return direction(dp.x.x * d.x + dp.y.x * d.y + dp.z.x * d.z,
                     dp.x.y * d.x + dp.y.y * d.y + dp.z.y * d.z,
                     dp.x.z * d.x + dp.y.z * d.y + dp.z.z * d.z);
}

#endif
