#ifndef _SCENE_H_
#define _SCENE_H_

#include "brdf.h"
#include "shape.h"
#include "source.h"
#include "lens.h"
#include "xform.h"

struct Camera {
	shared_ptr<Xform<lens_s,world_s>> xform;
    shared_ptr<Lens> lens;

    lensSample<world_s> sample(const tuple2& puv, const tuple2& luv, const mreal<time_d>& t) {
        auto s = lens->sample(puv, luv);
        auto m = xform->sample(t);
        return lensSample<world_s>(transform(m, s.o), transform(m, s.w));
    }
};

struct Material {
    shared_ptr<Brdf> brdf;
    shared_ptr<AreaSource> source;

    Material(shared_ptr<Brdf> brdf) : brdf(brdf), source() { }
    Material(shared_ptr<Brdf> brdf, shared_ptr<AreaSource> source) : brdf(brdf), source(source) { }

    spectrum<radiance_d> emission(const direction<world_s>& wo, const frame<world_s,local_s>& dp) {
        if(cos(dp.z, wo) < 0 || !source) return spectrum<radiance_d>();
        else return source->le;
    }

    spectrum<rho_d> rho(const direction<world_s>& wo, const frame<world_s,local_s>& dp, bool smooth, bool delta) {
        return brdf->rho(project(dp, wo),smooth,delta);
    }

    spectrum<brdf_d> f(const direction<world_s>& wo, const direction<world_s>& wi, const frame<world_s,local_s>& dp) {
        return brdf->f(project(dp, wo), project(dp, wi));
    }

    brdfSample<world_s> sample(const direction<world_s>& wo, const frame<world_s,local_s>& dp, const tuple2& ra, const real& rl, bool smooth, bool delta) {
        auto ls = brdf->sample(project(dp,wo), ra, rl, smooth, delta);
        return brdfSample<world_s>(ls.f, unproject(dp,ls.wi), ls.pdf, ls.delta);
    }

    mreal<invsolidangle_d> pdf(const direction<world_s>& wo, const direction<world_s>& wi, const frame<world_s,local_s>& dp, bool smooth, bool delta) {
        return brdf->pdf(project(dp,wo), project(dp,wi), smooth, delta);
    }
};

struct Light {
    shared_ptr<Xform<source_s,world_s>> xform;
    shared_ptr<Source> source;

    shadowSample<world_s> sampleShadow(const point<world_s>& p, const tuple2& uv, const mreal<time_d>& t) {
        auto m = xform->sample(t);
        auto pl = transform(invert(m), p);
        auto ssl = source->sampleShadow(pl,uv);
        return shadowSample<world_s>(ssl.le, ssl.dist, transform(m, ssl.wi), ssl.pdf);
    }

    mreal<invsolidangle_d> pdfShadow(const point<world_s>& p, const direction<world_s>& wi, const mreal<time_d>& t) {
        auto m = xform->sample(t);
        return source->pdfShadow(transform(invert(m),p),transform(invert(m),wi));
    }
};

struct Surface {
    shared_ptr<Xform<shape_s,world_s>> xform;
	shared_ptr<Material> material;
    shared_ptr<Shape> shape;

    isect<world_s> intersect(const ray<world_s>& r, const mreal<time_d>& t) {
        auto m = xform->sample(t);
        auto rt = transform(invert(m),r);
        auto ist = shape->intersect(rt);
        ist.m = material;
        return transform(m, ist);
    }

    bool hit(const ray<world_s>& r, const mreal<time_d>& t) {
        auto m = xform->sample(t);
        auto rt = transform(invert(m),r);
        return shape->hit(rt);
    }
};

struct Scene {
    std::vector<shared_ptr<Surface>> surfaces;
    std::vector<shared_ptr<Light>> lights;
    shared_ptr<Camera> camera;

    isect<world_s> intersect(const ray<world_s>& r, const mreal<time_d>& t) {
        isect<world_s> is; mreal<length_d> mint;
        for(size_t i = 0; i < surfaces.size(); i ++) {
            auto sis = surfaces[i]->intersect(r,t);
            if(sis.hit && (!is.hit || sis.t < mint)) {
                is = sis;
                mint = sis.t;
            }
        }
        return is;
    }

    bool hit(const ray<world_s>& r, const mreal<time_d>& t) {
        for(size_t i = 0; i < surfaces.size(); i ++) {
            if(surfaces[i]->hit(r,t)) return true;
        }
        return false;
    }
};

#endif
