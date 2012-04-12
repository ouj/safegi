#ifndef _SOURCE_H_
#define _SOURCE_H_

#include "common.h"

struct Source {
    virtual shadowSample<source_s> sampleShadow(const point<source_s>& p, const tuple2& ruv) = 0;
    virtual mreal<invsolidangle_d> pdfShadow(const point<source_s>& p, const direction<source_s>& wi) = 0;

    virtual bool isdelta() = 0;
};

struct PointSource : public Source {
    spectrum<intensity_d> intensity;

    //PointSource(const spectrum<intensity_d>& intensity) : intensity(intensity) { }
    PointSource(const spectrum<power_d>& power) : intensity(power / sphericalAngle) { }

    shadowSample<source_s> sampleShadow(const point<source_s>& p, const tuple2& ruv) {
        auto d = - asvector(p);
        return shadowSample<source_s>(intensity / (lengthSqr(d) * mreal<proj_d>(1)), length(d), normalize(d), mreal<invsolidangle_d>(1));
    }

    virtual mreal<invsolidangle_d> pdfShadow(const point<source_s>& p, const direction<source_s>& wi) {
        return mreal<invsolidangle_d>();
    }

    virtual bool isdelta() { return true; }
};

struct AreaSource : public Source {
    shared_ptr<Shape> shape;
    spectrum<radiance_d> le;

    AreaSource(shared_ptr<Shape> shape, const spectrum<power_d>& power) : shape(shape), le(power / (shape->area() * hemisphericalProjectedAngle)) { }

    shadowSample<source_s> sampleShadow(const point<source_s>& p, const tuple2& ruv) {
        auto s = shape->sample(ruv);
        auto ss = shapeSample<source_s>(point<source_s>(s.p.x,s.p.y,s.p.z),normal<source_s>(s.n.x,s.n.y,s.n.z),s.area); // typecast since this object assume the spaces of are equivalent
        auto d = ss.p-p;
        auto w = -normalize(d);
        if(cos(ss.n, w) <= 0) return shadowSample<source_s>();
        return shadowSample<source_s>(le, length(d), normalize(d), mreal<invsolidangle_d>(lengthSqr(d) / (s.area * cos(ss.n,w))) );
    }

    virtual mreal<invsolidangle_d> pdfShadow(const point<source_s>& p, const direction<source_s>& wi) {
        ray<shape_s> r(point<shape_s>(p.x,p.y,p.z),direction<shape_s>(wi.x,wi.y,wi.z));
        isect<shape_s> is = shape->intersect(r);
        if(!is.hit) return mreal<invsolidangle_d>();

        auto pp = point<source_s>(is.dp.o.x,is.dp.o.y,is.dp.o.z);
        auto nn = direction<source_s>(is.dp.z.x,is.dp.z.y,is.dp.z.z);
        auto d = pp-p;
        if(cos(nn, wi) <= 0) return mreal<invsolidangle_d>();
        else return mreal<invsolidangle_d>(lengthSqr(d) / (shape->area() * cos(nn,wi)));
    }

    virtual bool isdelta() { return false; }
};

#endif
