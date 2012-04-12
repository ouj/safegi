#ifndef _BRDF_H_
#define _BRDF_H_

#include "common.h"

struct Brdf {
    virtual spectrum<brdf_d> f(const direction<local_s>& wo, const direction<local_s>& wi) = 0;
    virtual spectrum<rho_d> rho(const direction<local_s>& wo, bool smooth, bool delta) = 0;
    virtual brdfSample<local_s> sample(const direction<local_s>& wo, const tuple2& ra, const real& rl, bool smooth, bool delta) = 0;
    virtual mreal<invsolidangle_d> pdf(const direction<local_s>& wo, const direction<local_s>& wi, bool smooth, bool delta) = 0;
};

struct Lambert : public Brdf {
    spectrum<rho_d> rhod;

    Lambert(const spectrum<rho_d>& rhod) : rhod(rhod) { }

    virtual spectrum<brdf_d> f(const direction<local_s>& wo, const direction<local_s>& wi) { 
        if(wo.z <= 0 || wi.z <= 0) return spectrum<brdf_d>();

        return rhod / hemisphericalProjectedAngle;
    }

    virtual spectrum<rho_d> rho(const direction<local_s>& wo, bool smooth, bool delta) {
        if(wo.z <= 0 || !smooth) return spectrum<rho_d>();

        return rhod;
    }

    virtual brdfSample<local_s> sample(const direction<local_s>& wo, const tuple2& ra, const real& rl, bool smooth, bool delta) {
        if(wo.z <= 0 || !smooth) return brdfSample<local_s>();

        auto s = sampleHemisphericalCos(ra);
        return brdfSample<local_s>(f(wo,s.w),s.w,s.pdf,false);
    }

    virtual mreal<invsolidangle_d> pdf(const direction<local_s>& wo, const direction<local_s>& wi, bool smooth, bool delta) {
        if(wo.z <= 0 || !smooth) return mreal<invsolidangle_d>();

        return pdfHemisphericalCos(wi);
    }
};

struct Phong : public Brdf {
    spectrum<rho_d> rhod; 
    spectrum<rho_d> rhos; 
    real n;

    Phong(const spectrum<rho_d>& rhod, const spectrum<rho_d>& rhos, real n) : rhod(rhod), rhos(rhos), n(n) { }

    virtual spectrum<brdf_d> f(const direction<local_s>& wo, const direction<local_s>& wi) {
        if(wo.z <= 0 || wi.z <= 0) return spectrum<brdf_d>();

        /*
        direction<local_s> wh = bisector(wi,wo);
        return (rhod + rhos * ((n + 2) * pow(max(wh.z,0.0),n) / 2)) / hemisphericalProjectedAngle;
        */
        auto wr = reflect(wi);
        return (rhod + rhos * ((n + 2) * pow(poscos(wo,wr),n) / 2)) / hemisphericalProjectedAngle;
    }

    virtual spectrum<rho_d> rho(const direction<local_s>& wo, bool smooth, bool delta) {
        if(wo.z <= 0 || !smooth) return spectrum<rho_d>();

        return rhod + rhos;
    }

    virtual brdfSample<local_s> sample(const direction<local_s>& wo, const tuple2& ra, const real& rl, bool smooth, bool delta) {
        if(wo.z <= 0 || !smooth) return brdfSample<local_s>();

        real pd = averageCmp(rhod) / (averageCmp(rhod)+averageCmp(rhos));
        real ps = averageCmp(rhos) / (averageCmp(rhod)+averageCmp(rhos));

        direction<local_s> wi;
        if(pd < rl) {
            auto s = sampleHemisphericalCos(ra);
            wi = s.w;
        } else {
            auto s = sampleHemisphericalCosPower(ra,n);
            auto f = frame<local_s,mirror_s>(reflect(wo));
            wi = unproject(f,direction<mirror_s>(s.w.x,s.w.y,s.w.z));
        }
        return brdfSample<local_s>(f(wo,wi),wi,pdf(wo,wi,smooth,delta),false);
    }

    virtual mreal<invsolidangle_d> pdf(const direction<local_s>& wo, const direction<local_s>& wi, bool smooth, bool delta) {
        if(wo.z <= 0 || !smooth) return mreal<invsolidangle_d>();

        real pd = averageCmp(rhod) / (averageCmp(rhod)+averageCmp(rhos));
        real ps = averageCmp(rhos) / (averageCmp(rhod)+averageCmp(rhos));

        auto f = frame<local_s,mirror_s>(reflect(wo));
        auto w = project(f,wi);
        return pd*pdfHemisphericalCos(wi)+ps*pdfHemisphericalCosPower(direction<local_s>(w.x,w.y,w.z),n);
    }
};

struct Mirror : public Brdf {
    spectrum<rho_d> rhor;

    Mirror(const spectrum<rho_d>& rhor) : rhor(rhor) { }

    virtual spectrum<brdf_d> f(const direction<local_s>& wo, const direction<local_s>& wi) { return spectrum<brdf_d>(); }

    virtual spectrum<rho_d> rho(const direction<local_s>& wo, bool smooth, bool delta) {
        if(wo.z <= 0 || !delta) return spectrum<rho_d>();

        return rhor;
    }

    virtual brdfSample<local_s> sample(const direction<local_s>& wo, const tuple2& ra, const real& rl, bool smooth, bool delta) {
        if(wo.z <= 0 || !delta) return brdfSample<local_s>();

        return brdfSample<local_s>(rhor*mreal<invsolidangle_d>(1)/mreal<proj_d>(wo.z),reflect(wo),mreal<invsolidangle_d>(1),true);
    }

    virtual mreal<invsolidangle_d> pdf(const direction<local_s>& wo, const direction<local_s>& wi, bool smooth, bool delta) {
        return mreal<invsolidangle_d>();
    }
};

#endif /* BRDF_H_ */
