#ifndef _TRACERUTILS_H_
#define _TRACERUTILS_H_

#include "scene.h"

struct lightSample {
    shared_ptr<Light> light;
    real pdf;

    lightSample() : light(), pdf(0) { }
    lightSample(shared_ptr<Light> light, const real& pdf) : light(light), pdf(pdf) { }
};

// roussian roulette
struct rrSample {
    bool stop;
    real pdf;

    rrSample() : stop(false), pdf(1) { }
    rrSample(bool strop, const real& pdf) : stop(stop), pdf(pdf) { }
};

inline lightSample uniformsample(const std::vector<shared_ptr<Light>>& lights) {
    return lightSample(lights[int(urandom() * lights.size())], 1.0 / lights.size());
}

inline rrSample roussianRoulette(real r, real p) {
    if(r <= p) return rrSample(false,p);
    else return rrSample(true,p);
}

inline bool isvalid(const lightSample& s) { return s.light != shared_ptr<Light>() && !iszero(s.pdf); }
inline bool isvalid(const shadowSample& s) { return !iszero(s.le) && !iszero(s.pdf); }
inline bool isvalid(const brdfSample& s) { return !iszero(s.f) && !iszero(s.pdf); }
inline bool isvalid(const rrSample& s) { return !s.stop && s.pdf != 0; }

#endif
