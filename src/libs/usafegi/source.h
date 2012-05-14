#ifndef _SOURCE_H_
#define _SOURCE_H_

#include "common.h"

struct Source {
    virtual shadowSample sampleShadow(const point& p, const tuple2& ruv) = 0;
    virtual real pdfShadow(const point& p, const direction& wi) = 0;

    virtual bool isdelta() = 0;
};

struct PointSource : public Source {
    spectrum intensity;

    PointSource(const spectrum& power) : intensity(power / sphericalAngle) { }

    shadowSample sampleShadow(const point& p, const tuple2& ruv) {
        auto d = - asvector(p);
        return shadowSample(intensity / (lengthSqr(d) * real(1)), length(d), normalize(d), real(1));
    }

    virtual real pdfShadow(const point& p, const direction& wi) {
        return real();
    }

    virtual bool isdelta() { return true; }
};

struct AreaSource : public Source {
    shared_ptr<Shape> shape;
    spectrum le;

    AreaSource(shared_ptr<Shape> shape, const spectrum& power) : shape(shape), le(power / (shape->area() * hemisphericalProjectedAngle)) { }

    shadowSample sampleShadow(const point& p, const tuple2& ruv) {
        auto s = shape->sample(ruv);
        auto ss = shapeSample(point(s.p.x,s.p.y,s.p.z),normal(s.n.x,s.n.y,s.n.z),s.area); // typecast since this object assume the spaces of are equivalent
        auto d = ss.p-p;
        auto w = -normalize(d);
        if(cos(ss.n, w) <= 0) return shadowSample();
        return shadowSample(le, length(d), normalize(d), real(lengthSqr(d) / (s.area * cos(ss.n,w))) );
    }

    virtual real pdfShadow(const point& p, const direction& wi) {
        ray r(point(p.x,p.y,p.z),direction(wi.x,wi.y,wi.z));
        isect is = shape->intersect(r);
        if(!is.hit) return real();

        auto pp = point(is.dp.o.x,is.dp.o.y,is.dp.o.z);
        auto nn = direction(is.dp.z.x,is.dp.z.y,is.dp.z.z);
        auto d = pp-p;
        if(cos(nn, wi) <= 0) return real();
        else return real(lengthSqr(d) / (shape->area() * cos(nn,wi)));
    }

    virtual bool isdelta() { return false; }
};

#endif
