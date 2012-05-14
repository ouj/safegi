#ifndef _BRDF_H_
#define _BRDF_H_

#include "common.h"

struct Brdf {
    virtual spectrum f(const direction& wo, const direction& wi) = 0;
    virtual spectrum rho(const direction& wo, bool smooth, bool delta) = 0;
    virtual brdfSample sample(const direction& wo, const tuple2& ra, const real& rl, bool smooth, bool delta) = 0;
    virtual real pdf(const direction& wo, const direction& wi, bool smooth, bool delta) = 0;
};

struct Lambert : public Brdf {
    spectrum rhod;

    Lambert(const spectrum& rhod) : rhod(rhod) { }

    virtual spectrum f(const direction& wo, const direction& wi) { 
        if(wo.z <= 0 || wi.z <= 0) return spectrum();

        return rhod / hemisphericalProjectedAngle;
    }

    virtual spectrum rho(const direction& wo, bool smooth, bool delta) {
        if(wo.z <= 0 || !smooth) return spectrum();

        return rhod;
    }

    virtual brdfSample sample(const direction& wo, const tuple2& ra, const real& rl, bool smooth, bool delta) {
        if(wo.z <= 0 || !smooth) return brdfSample();

        auto s = sampleHemisphericalCos(ra);
        return brdfSample(f(wo,s.w),s.w,s.pdf,false);
    }

    virtual real pdf(const direction& wo, const direction& wi, bool smooth, bool delta) {
        if(wo.z <= 0 || !smooth) return real();

        return pdfHemisphericalCos(wi);
    }
};

struct Phong : public Brdf {
    spectrum rhod; 
    spectrum rhos; 
    real n;

    Phong(const spectrum& rhod, const spectrum& rhos, real n) : rhod(rhod), rhos(rhos), n(n) { }

    virtual spectrum f(const direction& wo, const direction& wi) {
        if(wo.z <= 0 || wi.z <= 0) return spectrum();

        /*
        direction wh = bisector(wi,wo);
        return (rhod + rhos * ((n + 2) * pow(max(wh.z,0.0),n) / 2)) / hemisphericalProjectedAngle;
        */
        auto wr = reflect(wi);
        return (rhod + rhos * ((n + 2) * pow(poscos(wo,wr),n) / 2)) / hemisphericalProjectedAngle;
    }

    virtual spectrum rho(const direction& wo, bool smooth, bool delta) {
        if(wo.z <= 0 || !smooth) return spectrum();

        return rhod + rhos;
    }

    virtual brdfSample sample(const direction& wo, const tuple2& ra, const real& rl, bool smooth, bool delta) {
        if(wo.z <= 0 || !smooth) return brdfSample();

        real pd = averageCmp(rhod) / (averageCmp(rhod)+averageCmp(rhos));
       
        direction wi;
        if(pd < rl) {
            auto s = sampleHemisphericalCos(ra);
            wi = s.w;
        } else {
            auto s = sampleHemisphericalCosPower(ra,n);
            auto f = frame(reflect(wo));
            wi = unproject(f,direction(s.w.x,s.w.y,s.w.z));
        }
        return brdfSample(f(wo,wi),wi,pdf(wo,wi,smooth,delta),false);
    }

    virtual real pdf(const direction& wo, const direction& wi, bool smooth, bool delta) {
        if(wo.z <= 0 || !smooth) return real();

        real pd = averageCmp(rhod) / (averageCmp(rhod)+averageCmp(rhos));
        real ps = averageCmp(rhos) / (averageCmp(rhod)+averageCmp(rhos));

        auto f = frame(reflect(wo));
        auto w = project(f,wi);
        return pd*pdfHemisphericalCos(wi)+ps*pdfHemisphericalCosPower(direction(w.x,w.y,w.z),n);
    }
};

struct Mirror : public Brdf {
    spectrum rhor;

    Mirror(const spectrum& rhor) : rhor(rhor) { }

    virtual spectrum f(const direction& wo, const direction& wi) { return spectrum(); }

    virtual spectrum rho(const direction& wo, bool smooth, bool delta) {
        if(wo.z <= 0 || !delta) return spectrum();

        return rhor;
    }

    virtual brdfSample sample(const direction& wo, const tuple2& ra, const real& rl, bool smooth, bool delta) {
        if(wo.z <= 0 || !delta) return brdfSample();

        return brdfSample(rhor*real(1)/real(wo.z),reflect(wo),real(1),true);
    }

    virtual real pdf(const direction& wo, const direction& wi, bool smooth, bool delta) {
        return real();
    }
};

#endif /* BRDF_H_ */
