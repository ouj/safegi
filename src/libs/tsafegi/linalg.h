#ifndef _MAT4_H_
#define _MAT4_H_

#include "real.h"

struct vec4 {
    real d[4];

    vec4() { d[0]=0; d[1]=0; d[2]=0; d[3]=0; }
    vec4(real x, real y, real z, real w) { d[0]=x; d[1]=y; d[2]=z; d[3]=w; }
};

struct mat4 {
	real d[4][4];

    mat4() { for(int i=0;i<4;i++) for(int j=0;j<4;j++) d[i][j]=(i==j)?1:0; }
};

inline mat4 transpose(const mat4& m) {
    mat4 t;
    for(int i=0;i<4;i++) {
        for(int j=0;j<4;j++) {
            t.d[i][j] = m.d[j][i];
        }
    }
    return t;
}

inline mat4 translateMat(real x, real y, real z) {
    mat4 m;
    m.d[0][3]=x;
    m.d[1][3]=y;
    m.d[2][3]=z;
    return m;
}

// axis/angle rotation
inline mat4 rotateMat(real x, real y, real z, real a) {
	real c = cos(a); real s = sin(a);
    mat4 m;
    m.d[0][0] = c+(1-c)*x*x;
    m.d[0][1] = (1-c)*x*y-z*s;
    m.d[0][2] = (1-c)*x*z+y*s;
	m.d[1][0] = (1-c)*x*y+z*s;
    m.d[1][1] = c+(1-c)*y*y;
    m.d[1][2] = (1-c)*y*z-x*s;
	m.d[2][0] = (1-c)*x*z-y*s;
    m.d[2][1] = (1-c)*y*z+x*s;
    m.d[2][2] = c+(1-c)*z*z;
    return m;
}

inline vec4 operator% (const mat4& m, const vec4& v) {
    vec4 r;
    for(int i=0;i<4;i++) {
        r.d[i]=0;
        for(int k=0;k<4;k++) {
            r.d[i] += m.d[i][k]*v.d[k];
        }
    }
    return r;
}

inline mat4 operator% (const mat4& a, const mat4& b) {
    mat4 r;
    for(int i=0;i<4;i++) {
        for(int j=0;j<4;j++) {
            r.d[i][j]=0;
            for(int k=0;k<4;k++) {
                r.d[i][j] += a.d[i][k]*b.d[k][j];
            }
        }
    }
    return r;
}

#endif
