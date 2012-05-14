#ifndef _U_SAMPLING_H_
#define _U_SAMPLING_H_

#include "u_geom.h"
#include "u_spectrum.h"

// const real samplingeps = 1e-8;

struct dirSample {
    direction w;
    real pdf;

    dirSample(const direction& w, const real& pdf) : w(w), pdf(pdf) { }
};

struct lensSample {
    point o;
    direction w;

    lensSample(const point& o, const direction& w) : o(o), w(w) { }
};

struct brdfSample {
    spectrum f;
    direction wi;
    real pdf;
    bool delta;

    brdfSample() : f(), wi(), pdf(0), delta(false) { }
    brdfSample(const spectrum& f, const direction& wi, const real& pdf, bool delta) : f(f), wi(wi), pdf(pdf), delta(delta) { }
};

struct shadowSample {
    spectrum le;
    real dist;
    direction wi;
    real pdf;

    shadowSample() : le(), dist(), wi(), pdf() { }
    shadowSample(const spectrum& le, const real& dist, const direction& wi, const real& pdf) : le(le), dist(dist), wi(wi), pdf(pdf) { }
};

struct shapeSample {
    point p;
    normal n;
    real area;

    shapeSample() : p(), n(), area(0) { }
    shapeSample(const point& p, const normal& n, const real& area) : p(p), n(n), area(area) { }
};

inline real powerHeuristic(const real& fPdf, const real& gPdf) {
    auto nf = 1; auto ng = 1;
    auto f = nf * fPdf; auto g = ng * gPdf;
	return (f*f) / (f*f + g*g);
}

inline real pdfHemisphericalCos(const direction& w) {
    return w.z/pi;
}

inline dirSample sampleHemisphericalCos(const tuple2& ruv) {
    real z = sqrt(ruv.y);
    real r = sqrt(1-z*z);
    real phi = 2 * pi * ruv.x;
    direction w = direction(r*cos(phi), r*sin(phi), z);
    return dirSample(w, pdfHemisphericalCos(w));
}

inline real pdfHemisphericalCosPower(const direction& w, real n) {
    return pow(w.z,n) * (n+1) / (2*pi);
}

inline dirSample sampleHemisphericalCosPower(const tuple2& ruv, real n) {
    real z = pow(ruv.y,1.0/(n+1.0));
    real r = sqrt(1-z*z);
    real phi = 2 * pi * ruv.x;
    direction w = direction(r*cos(phi), r*sin(phi), z);
    return dirSample(w, pdfHemisphericalCosPower(w,n));
}

inline real pdfSpherical(const direction& w) {
    return 1.0 / sphericalAngle;
}

inline dirSample sampleSpherical(const tuple2& ruv) {
    real z = 2*ruv.y-1;
    real r = sqrt(1-z*z);
    real phi = 2 * pi * ruv.x;
    direction w = direction(r*cos(phi), r*sin(phi), z);
    return dirSample(w, pdfSpherical(w));
}

inline real pdfHemispherical(const direction& w) {
    return 1.0 / hemisphericalAngle;
}

inline dirSample sampleHemispherical(const tuple2& ruv) {
    real z = ruv.y;
    real r = sqrt(1-z*z);
    real phi = 2 * pi * ruv.x;
    direction w = direction(r*cos(phi), r*sin(phi), z);
    return dirSample(w, pdfHemispherical(w));
}

#endif
