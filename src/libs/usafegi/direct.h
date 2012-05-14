#ifndef _DIRECT_H_
#define _DIRECT_H_

#include "tracer.h"
#include "tracerutils.h"

struct DirectIntegrator : public Integrator {
    int maxLength;

    DirectIntegrator() : maxLength(2) { }

    virtual spectrum l(const point& o, const direction& w, const real& t, shared_ptr<Scene> scene) {
        return l(o,w,t,scene,0);
    }

    virtual spectrum l(const point& o, const direction& w, const real& t, shared_ptr<Scene> scene, int depth) {
        // intersect the scene
        auto is = scene->intersect(ray(o,w),t);

        // if missed, return 0
        if(!is.hit) return spectrum();

        // rename variables for readability
        auto wo = -w;
        auto n = is.dp.z;
        auto dp = is.dp;
        auto m = is.m;

        // radiance: emitted + direct + indirect
        return le(wo,t,dp,m,scene,depth) + ld(wo,t,dp,m,scene,depth) + li(wo,t,dp,m,scene,depth);
    }

    virtual spectrum le(const direction& wo, const real& t, const frame& dp, shared_ptr<Material> m, shared_ptr<Scene> scene, int depth) {
        return m->emission(wo, dp);
    }

    virtual spectrum ld(const direction& wo, const real& t, const frame& dp, shared_ptr<Material> m, shared_ptr<Scene> scene, int depth) {
        // select a random light
        auto ls = uniformsample(scene->lights);
        if(!isvalid(ls)) return spectrum();

        // pick a sample on the light
        auto ss = ls.light->sampleShadow(dp.o, tuple2(urandom(), urandom()), t);
        if(!isvalid(ss)) return spectrum();

        // shade
        spectrum mbrdf = m->f(wo, ss.wi, dp);
        real abscos_proj = abscos(dp.z,ss.wi);
        auto lit = ss.le * mbrdf * abscos_proj / (ss.pdf * ls.pdf);
        if(iszero(lit)) return spectrum();

        // shadow check
        if(scene->hit(ray(dp.o, ss.wi, ss.dist), t)) return spectrum();

        // done
        return lit;
    }

    virtual spectrum li(const direction& wo, const real& t, const frame& dp, shared_ptr<Material> m, shared_ptr<Scene> scene, int depth) {
        // check for max length
        if(depth > maxLength) return spectrum();

        // delta paths
        auto bs = m->sample(wo,dp,tuple2(urandom(),urandom()),urandom(),false,true);
        if(!isvalid(bs)) return spectrum();

        // shoot delta path
        return bs.f * abscos(dp.z,bs.wi) * l(dp.o, bs.wi, t, scene, depth+1) / bs.pdf;
    }
};

struct DirectMISIntegrator : public Integrator {
    int maxLength;

    DirectMISIntegrator() : maxLength(2) { }

    virtual spectrum l(const point& o, const direction& w, const real& t, shared_ptr<Scene> scene) {
        return l(o,w,t,scene,0);
    }

    virtual spectrum l(const point& o, const direction& w, const real& t, shared_ptr<Scene> scene, int depth) {
        // intersect the scene
        auto is = scene->intersect(ray(o,w),t);

        // if missed, return 0
        if(!is.hit) return spectrum();

        // rename variables for readability
        auto wo = -w;
        auto n = is.dp.z;
        auto dp = is.dp;
        auto m = is.m;

        // radiance: emitted + direct + indirect
        return le(wo,t,dp,m,scene,depth) + ld(wo,t,dp,m,scene,depth) + li(wo,t,dp,m,scene,depth);
    }

    virtual spectrum le(const direction& wo, const real& t, const frame& dp, shared_ptr<Material> m, shared_ptr<Scene> scene, int depth) {
        return m->emission(wo, dp);
    }

    virtual spectrum ld(const direction& wo, const real& t, const frame& dp, shared_ptr<Material> m, shared_ptr<Scene> scene, int depth) {
        // select a random light
        auto ls = uniformsample(scene->lights);
        if(!isvalid(ls)) return spectrum();

        // if delta, sample simply
        if(ls.light->source->isdelta()) return ld_delta(ls, wo, t, dp, m, scene, depth);

        // sample accrding to light and brdf
        return (ld_light(ls.light, wo, t, dp, m, scene, depth) +
                ld_brdf(ls.light, wo, t, dp, m, scene, depth)) / ls.pdf;
    }

    virtual spectrum ld_delta(lightSample ls, const direction& wo, const real& t, const frame& dp, shared_ptr<Material> m, shared_ptr<Scene> scene, int depth) {
        // pick a sample on the light
        auto ss = ls.light->sampleShadow(dp.o, tuple2(urandom(), urandom()), t);
        if(!isvalid(ss)) return spectrum();

        // shade
        auto lit = ss.le * m->f(wo, ss.wi, dp) * abscos(dp.z,ss.wi) / (ss.pdf * ls.pdf);
        if(iszero(lit)) return spectrum();

        // shadow check
        if(scene->hit(ray(dp.o, ss.wi, ss.dist), t)) return spectrum();

        // done
        return lit;
    }

    virtual spectrum ld_light(shared_ptr<Light> light, const direction& wo, const real& t, const frame& dp, shared_ptr<Material> m, shared_ptr<Scene> scene, int depth) {
        // pick a sample on the light
        auto ss = light->sampleShadow(dp.o, tuple2(urandom(), urandom()), t);
        if(!isvalid(ss)) return spectrum();

        // shade
        auto lit = ss.le * m->f(wo, ss.wi, dp) * abscos(dp.z,ss.wi) / ss.pdf;
        if(iszero(lit)) return spectrum();

        // grab brdf pdf
        real brdfPdf = m->pdf(wo, ss.wi, dp, true, true);
        if(iszero(brdfPdf)) return spectrum();

        // compute weight
        real weight = powerHeuristic(ss.pdf, brdfPdf);
        if(iszero(weight)) return spectrum();

        // shadow check
        if(scene->hit(ray(dp.o, ss.wi, ss.dist), t)) return spectrum();

        // done
        return lit * weight;
    }

    virtual spectrum ld_brdf(shared_ptr<Light> light, const direction& wo, const real& t, const frame& dp, shared_ptr<Material> m, shared_ptr<Scene> scene, int depth) {
        // pick direction based on brdf
        auto bs = m->sample(wo,dp,tuple2(urandom(),urandom()),urandom(),true,true);
        if(!isvalid(bs)) return spectrum();

        // grab light pdf
        real shadowPdf = light->pdfShadow(dp.o, bs.wi, t);
        if(iszero(shadowPdf)) return spectrum();

        // compute weight
        real weight = powerHeuristic(bs.pdf, shadowPdf);
        if(iszero(weight)) return spectrum();

        // check if it hits the light
        auto is = scene->intersect(ray(dp.o,bs.wi),t);
        if(!is.hit) return spectrum();
        if(is.m->source != light->source) return spectrum();

        // shade
        auto lit = is.m->source->le * bs.f * abscos(dp.z,bs.wi) / bs.pdf;
        if(iszero(lit)) return spectrum();

        // done
        return lit * weight;
    }

    virtual spectrum li(const direction& wo, const real& t, const frame& dp, shared_ptr<Material> m, shared_ptr<Scene> scene, int depth) {
        // check for max length
        if(depth > maxLength) return spectrum();

        // delta paths
        auto bs = m->sample(wo,dp,tuple2(urandom(),urandom()),urandom(),false,true);
        if(!isvalid(bs)) return spectrum();

        // shoot delta path
        return bs.f * abscos(dp.z,bs.wi) * l(dp.o, bs.wi, t, scene, depth+1) / bs.pdf;
    }
};

#endif
