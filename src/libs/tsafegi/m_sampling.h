#ifndef _M_SAMPLING_H_
#define _M_SAMPLING_H_

#include "m_geom.h"

// const real samplingeps = 1e-8;

template<typename S>
struct dirSample {
    direction<S> w;
    mreal<invsolidangle_d> pdf;

    dirSample(const direction<S>& w, const mreal<invsolidangle_d>& pdf) : w(w), pdf(pdf) { }
};

template<typename S>
struct lensSample {
    point<S> o;
    direction<S> w;

    lensSample(const point<S>& o, const direction<S>& w) : o(o), w(w) { }
};

template<typename S>
struct brdfSample {
    spectrum<brdf_d> f;
    direction<S> wi;
    mreal<invsolidangle_d> pdf;
    bool delta;

    brdfSample() : f(), wi(), pdf(0), delta(false) { }
    brdfSample(const spectrum<brdf_d>& f, const direction<S>& wi, const mreal<invsolidangle_d>& pdf, bool delta) : f(f), wi(wi), pdf(pdf), delta(delta) { }
};

template<typename S>
struct shadowSample {
    spectrum<radiance_d> le;
    mreal<length_d> dist;
    direction<S> wi;
    mreal<invsolidangle_d> pdf;

    shadowSample() : le(), dist(), wi(), pdf() { }
    shadowSample(const spectrum<radiance_d>& le, const mreal<length_d>& dist, const direction<S>& wi, const mreal<invsolidangle_d>& pdf) : le(le), dist(dist), wi(wi), pdf(pdf) { }
};

template<typename S>
struct shapeSample {
    point<S> p;
    normal<S> n;
    mreal<area_d> area;

    shapeSample() : p(), n(), area() { }
    shapeSample(const point<S>& p, const normal<S>& n, const mreal<area_d>& area) : p(p), n(n), area(area) { }
};

inline real powerHeuristic(const mreal<invsolidangle_d>& fPdf, const mreal<invsolidangle_d>& gPdf) {
    auto nf = 1; auto ng = 1;
    auto f = nf * fPdf; auto g = ng * gPdf;
	return (f*f) / (f*f + g*g);
}

inline mreal<invsolidangle_d> pdfHemisphericalCos(const direction<local_s>& w) {
    return w.z / (sphericalAngle / 4);
}

inline dirSample<local_s> sampleHemisphericalCos(const tuple2& ruv) {
    real z = sqrt(ruv.y);
    real r = sqrt(1-z*z);
    real phi = 2 * pi * ruv.x;
    direction<local_s> w = direction<local_s>(r*cos(phi), r*sin(phi), z);
    return dirSample<local_s>(w, pdfHemisphericalCos(w));
}

inline mreal<invsolidangle_d> pdfHemisphericalCosPower(const direction<local_s>& w, real n) {
    return pow(w.z,n) * (n+1) / hemisphericalAngle;
}

inline dirSample<local_s> sampleHemisphericalCosPower(const tuple2& ruv, real n) {
    real z = pow(ruv.y,1.0/(n+1.0));
    real r = sqrt(1-z*z);
    real phi = 2 * pi * ruv.x;
    direction<local_s> w = direction<local_s>(r*cos(phi), r*sin(phi), z);
    return dirSample<local_s>(w, pdfHemisphericalCosPower(w,n));
}

inline mreal<invsolidangle_d> pdfSpherical(const direction<local_s>& w) {
    return 1.0 / sphericalAngle;
}

inline dirSample<local_s> sampleSpherical(const tuple2& ruv) {
    real z = 2*ruv.y-1;
    real r = sqrt(1-z*z);
    real phi = 2 * pi * ruv.x;
    direction<local_s> w = direction<local_s>(r*cos(phi), r*sin(phi), z);
    return dirSample<local_s>(w, pdfSpherical(w));
}

inline mreal<invsolidangle_d> pdfHemispherical(const direction<local_s>& w) {
    return 1.0 / hemisphericalAngle;
}

inline dirSample<local_s> sampleHemispherical(const tuple2& ruv) {
    real z = ruv.y;
    real r = sqrt(1-z*z);
    real phi = 2 * pi * ruv.x;
    direction<local_s> w = direction<local_s>(r*cos(phi), r*sin(phi), z);
    return dirSample<local_s>(w, pdfHemispherical(w));
}

#endif
