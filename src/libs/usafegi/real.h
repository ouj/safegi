#ifndef _REAL_H_
#define _REAL_H_

#include "std.h"

typedef double real;

const real eps = 1e-6;
const real inf = 1e12;
const real pi = 3.1415926535897932384626433832795;

struct tuple2 {
    real x, y;

    tuple2() : x(0), y(0) { }
    tuple2(const real& x, const real& y) : x(x), y(y) { }
};

struct tuple3 {
	real x, y, z;

    tuple3() : x(0), y(0), z(0) { }
    tuple3(const real& x, const real& y, const real& z) : x(x), y(y), z(z) { }
};

inline real toRadians(const real& a) { return a * pi / 180; }
inline bool iszero(const real& v) { return v == 0; }

inline real urandom() {
    static minstd_rand eng;
    static uniform_real<real> dist;
    return dist(eng);
}

inline real __asreal(const real& a) { return a; }

const real hemisphericalProjectedAngle = pi;
const real sphericalAngle = 4*pi;
const real hemisphericalAngle = 2*pi;

#endif
