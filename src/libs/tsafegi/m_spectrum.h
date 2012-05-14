#ifndef _M_SPECTRUM_H_
#define _M_SPECTRUM_H_

#include "m_real.h"

template<typename D>
struct spectrum {
    mreal<D> r, g, b;

    spectrum() : r(), g(), b() { }
    spectrum(const mreal<D>& r, const mreal<D>& g, const mreal<D>& b) : r(r), g(g), b(b) { }
};

template<typename D>
inline bool iszero(const spectrum<D>& s) {
    return iszero(s.r) && iszero(s.g) && iszero(s.b);
}

template<typename D>
inline spectrum<D> operator+ (const spectrum<D>& a, const spectrum<D>& b) {
    return spectrum<D>(a.r+b.r,a.g+b.g,a.b+b.b);
}

template<typename D1, typename D2>
inline spectrum<typename dimension_product<D1,D2>::type> operator* (const spectrum<D1>& a, const spectrum<D2>& b) {
    return spectrum<typename dimension_product<D1,D2>::type>(a.r*b.r,a.g*b.g,a.b*b.b);
}

template<typename D>
inline spectrum<D> operator* (const spectrum<D>& a, const real& b) {
    return spectrum<D>(a.r*b,a.g*b,a.b*b);
}

template<typename D1, typename D2>
inline spectrum<typename dimension_product<D1,D2>::type> operator* (const spectrum<D1>& a, const mreal<D2>& b) {
    return spectrum<typename dimension_product<D1,D2>::type>(a.r*b,a.g*b,a.b*b);
}

template<typename D>
inline spectrum<D> operator/ (const spectrum<D>& a, const real& b) {
    real ib = 1.0 / b;
    return a * ib;
}

template<typename D1, typename D2>
inline spectrum<typename dimension_division<D1,D2>::type> operator/ (const spectrum<D1>& a, const mreal<D2>& b) {
    auto ib = 1.0 / b;
    return a * ib;
}

template<typename D>
inline spectrum<D> max(const spectrum<D>& a, const spectrum<D>& b) {
    return spectrum<D>(max(a.r,b.r),max(a.g,b.g),max(a.b,b.b));
}

template<typename D>
inline mreal<D> averageCmp(const spectrum<D>& s) { 
    return (s.r + s.g + s.b) / 3.0; 
}

template<typename D>
inline mreal<D> maxCmp(const spectrum<D>& s) { 
    return max(s.r, max(s.g, s.b)); 
}

#endif
