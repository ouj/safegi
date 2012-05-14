#ifndef _SCENE_H_
#define _SCENE_H_

#include "brdf.h"
#include "shape.h"
#include "source.h"
#include "lens.h"
#include "xform.h"

struct Camera {
	shared_ptr<Xform> xform;
    shared_ptr<Lens> lens;

    lensSample sample(const tuple2& puv, const tuple2& luv, const real& t) {
        auto s = lens->sample(puv, luv);
        auto m = xform->sample(t);
        return lensSample(transform(m, s.o), transform(m, s.w));
    }
};

struct Material {
    shared_ptr<Brdf> brdf;
    shared_ptr<AreaSource> source;

    Material(shared_ptr<Brdf> brdf) : brdf(brdf), source() { }
    Material(shared_ptr<Brdf> brdf, shared_ptr<AreaSource> source) : brdf(brdf), source(source) { }

    spectrum emission(const direction& wo, const frame& dp) {
        if(cos(dp.z, wo) < 0 || !source) return spectrum();
        else return source->le;
    }

    spectrum rho(const direction& wo, const frame& dp, bool smooth, bool delta) {
        return brdf->rho(project(dp, wo),smooth,delta);
    }

    spectrum f(const direction& wo, const direction& wi, const frame& dp) {
        return brdf->f(project(dp, wo), project(dp, wi));
    }

    brdfSample sample(const direction& wo, const frame& dp, const tuple2& ra, const real& rl, bool smooth, bool delta) {
        auto ls = brdf->sample(project(dp,wo), ra, rl, smooth, delta);
        return brdfSample(ls.f, unproject(dp,ls.wi), ls.pdf, ls.delta);
    }

    real pdf(const direction& wo, const direction& wi, const frame& dp, bool smooth, bool delta) {
        return brdf->pdf(project(dp,wo), project(dp,wi), smooth, delta);
    }
};

struct Light {
    shared_ptr<Xform> xform;
    shared_ptr<Source> source;

    shadowSample sampleShadow(const point& p, const tuple2& uv, const real& t) {
        auto m = xform->sample(t);
        auto pl = transform(invert(m), p);
        auto ssl = source->sampleShadow(pl,uv);
        return shadowSample(ssl.le, ssl.dist, transform(m, ssl.wi), ssl.pdf);
    }

    real pdfShadow(const point& p, const direction& wi, const real& t) {
        auto m = xform->sample(t);
        return source->pdfShadow(transform(invert(m),p),transform(invert(m),wi));
    }
};

struct Surface {
    shared_ptr<Xform> xform;
	shared_ptr<Material> material;
    shared_ptr<Shape> shape;

    isect intersect(const ray& r, const real& t) {
        auto m = xform->sample(t);
        auto rt = transform(invert(m),r);
        auto ist = shape->intersect(rt);
        ist.m = material;
        return transform(m, ist);
    }

    bool hit(const ray& r, const real& t) {
        auto m = xform->sample(t);
        auto rt = transform(invert(m),r);
        return shape->hit(rt);
    }
};

struct Scene {
    std::vector<shared_ptr<Surface>> surfaces;
    std::vector<shared_ptr<Light>> lights;
    shared_ptr<Camera> camera;

    isect intersect(const ray& r, const real& t) {
        isect is; real mint;
        for(size_t i = 0; i < surfaces.size(); i ++) {
            auto sis = surfaces[i]->intersect(r,t);
            if(sis.hit && (!is.hit || sis.t < mint)) {
                is = sis;
                mint = sis.t;
            }
        }
        return is;
    }

    bool hit(const ray& r, const real& t) {
        for(size_t i = 0; i < surfaces.size(); i ++) {
            if(surfaces[i]->hit(r,t)) return true;
        }
        return false;
    }
};

#endif
