#ifndef _U_SPECTRUM_H_
#define _U_SPECTRUM_H_

//#include "u_real.h"

struct spectrum {
    real r, g, b;

    spectrum() : r(), g(), b() { }
    spectrum(real r, real g, real b) : r(r), g(g), b(b) { }
};

inline bool iszero(const spectrum& s) {
    return s.r == 0 && s.g == 0 && s.b == 0;
}

inline spectrum operator+ (const spectrum& a, const spectrum& b) {
    return spectrum(a.r+b.r,a.g+b.g,a.b+b.b);
}

inline spectrum operator* (const spectrum& a, const spectrum& b) {
    return spectrum(a.r*b.r,a.g*b.g,a.b*b.b);
}

inline spectrum operator* (const spectrum& a, const real& b) {
    return spectrum(a.r*b,a.g*b,a.b*b);
}

inline spectrum operator/ (const spectrum& a, const real& b) {
    real ib = 1.0 / b;
    return a * ib;
}

inline spectrum max(const spectrum& a, const spectrum& b) {
    return spectrum(max(a.r,b.r),max(a.g,b.g),max(a.b,b.b));
}

inline real averageCmp(const spectrum& s) { 
    return (s.r + s.g + s.b) / 3; 
}

inline real maxCmp(const spectrum& s) { 
    return max(s.r, max(s.g, s.b)); 
}

#endif
