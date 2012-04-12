#ifndef _M_REAL_H_
#define _M_REAL_H_

#include "real.h"
#include "dimensions.h"

template<typename D>
struct mreal {
    real v;

    mreal<D>() : v(0) { }
    explicit mreal<D>(const real& v) : v(v) { }
};

template<>
struct mreal<unit_d> {
    real v;

    mreal() : v(0) { }
    mreal(const real& v) : v(v) { }

    operator real() { return v; }
};

template<typename D>
inline mreal<D> operator+ (const mreal<D>& a, const mreal<D>& b) {
    return mreal<D>(a.v+b.v);
}

template<typename D>
inline mreal<D> operator- (const mreal<D>& a, const mreal<D>& b) {
    return mreal<D>(a.v-b.v);
}

template<typename D>
inline mreal<D> operator- (const mreal<D>& a) {
    return mreal<D>(-a.v);
}

template<typename D>
inline mreal<D> operator* (const mreal<D>& a, const real& b) {
    return mreal<D>(a.v*b);
}

template<typename D>
inline mreal<D> operator* (const real& a, const mreal<D>& b) {
    return mreal<D>(a*b.v);
}

template<typename D>
inline mreal<D> operator/ (const mreal<D>& a, const real& b) {
    return mreal<D>(a.v/b);
}

template<typename D>
inline bool operator == (const mreal<D>& a, const mreal<D>& b) {
    return a.v == b.v;
}

template<typename D>
inline bool iszero(const mreal<D>& a) {
    return a.v == 0;
}

template<typename D>
inline bool operator> (const mreal<D>& a, const mreal<D>& b) {
    return a.v > b.v;
}

template<typename D>
inline bool operator< (const mreal<D>& a, const mreal<D>& b) {
    return a.v < b.v;
}

template<typename D>
inline bool operator>= (const mreal<D>& a, const mreal<D>& b) {
    return a.v >= b.v;
}

template<typename D>
inline bool operator<= (const mreal<D>& a, const mreal<D>& b) {
    return a.v <= b.v;
}

template<typename D1, typename D2>
inline mreal<typename dimension_product<D1,D2>::type> operator* (const mreal<D1>& a, const mreal<D2>& b) {
    return mreal<typename dimension_product<D1,D2>::type>(a.v*b.v);
}

template<typename D1, typename D2>
inline mreal<typename dimension_division<D1,D2>::type> operator/ (const mreal<D1>& a, const mreal<D2>& b) {
    return mreal<typename dimension_division<D1,D2>::type>(a.v/b.v);
}

template<typename D>
inline real operator/ (const mreal<D>& a, const mreal<D>& b) {
    return a.v/b.v;
}

template<typename D>
inline mreal<typename dimension_division<unit_d,D>::type> operator/ (const real& a, const mreal<D>& b) {
    return mreal<typename dimension_division<unit_d,D>::type>(a/b.v);
}

template<typename D>
inline mreal<typename dimension_sqrt<D>::type> sqrt(const mreal<D>& a) {
    return mreal<typename dimension_sqrt<D>::type>(sqrt(a.v));
}

inline mreal<unit_d> tan(const mreal<angle_d>& a) {
    return tan(a.v);
}

inline mreal<angle_d> _acos(const mreal<unit_d> &a) {
    return mreal<angle_d>(acos(a.v));
}

inline mreal<unit_d> _sin(const mreal<angle_d> &a) {
    return sin(a.v);
}

inline mreal<unit_d> _cos(const mreal<angle_d> &a) {
    return cos(a.v);
}


template<typename D>
struct mtuple3 {
	mreal<D> x, y, z;

    mtuple3() : x(), y(), z() { }
    mtuple3(const mreal<D>& x, const mreal<D>& y, const mreal<D>& z) : x(x), y(y), z(z) { }
};

template<typename D>
inline real __asreal(mreal<D>& a) { return a.v; }
template<typename D>
inline const real __asreal(const mreal<D>& a) { return a.v; }

const mreal<length_d> eps_length = mreal<length_d>(eps);
const mreal<length_d> inf_length = mreal<length_d>(inf);

const mreal<projsolidangle_d> hemisphericalProjectedAngle = mreal<projsolidangle_d>(pi);
const mreal<solidangle_d> sphericalAngle = mreal<solidangle_d>(4.0*pi);
const mreal<solidangle_d> hemisphericalAngle = mreal<solidangle_d>(2.0*pi);
const mreal<angle_d> circleAngle = mreal<angle_d>(2.0*pi);
const mreal<angle_d> halfCircleAngle = mreal<angle_d>(pi);

#endif
