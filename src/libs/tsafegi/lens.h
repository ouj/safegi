#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "common.h"

struct Lens {
    virtual lensSample<lens_s> sample(const tuple2& puv, const tuple2& luv) = 0;
    virtual projmap<lens_s, clip_s> get_projection(mreal<length_d> n, mreal<length_d> f) = 0;
};

struct PinholeLens : public Lens {
    mreal<angle_d> fovx, fovy;    
    mreal<length_d> imagedist;

    PinholeLens(const mreal<angle_d>& fovx, const mreal<angle_d>& fovy) : fovx(fovx), fovy(fovy), imagedist(1) { }

    virtual lensSample<lens_s> sample(const tuple2& puv, const tuple2& luv) {
        auto q = _imagePlanePoint(puv);
        auto o = point<lens_s>();
        return lensSample<lens_s>(o, normalize(q-o));
    }

    virtual projmap<lens_s, clip_s> get_projection(mreal<length_d> n, mreal<length_d> f)
    {
        projmap<lens_s, clip_s> rm;
        mat4 m;

        mreal<length_d> l = -n * tan(fovx);
        mreal<length_d> r = n * tan(fovx);
        mreal<length_d> t = n * tan(fovy);
        mreal<length_d> b = -n * tan(fovy);

        m.d[0][0] = 2 * n / (r - l);
        m.d[0][2] = (r + l) / (l - r);
        m.d[1][1] = 2 * n / (t - b);
        m.d[1][2] = (t + b) / (t - b);
        m.d[2][2] = (n + f) / (n - f);
        m.d[2][3] = __asreal(2.0 * f * n / (n - f));
        m.d[3][2] = -1.0;
        m.d[3][3] = 0.0;
        rm.m = m;
        return rm;
    }

    point<lens_s> _imagePlanePoint(const tuple2& puv) {
        return point<lens_s>( (2*puv.x-1)*tan(fovx)*imagedist, (2*puv.y-1)*tan(fovy)*imagedist, -imagedist);
    }
};

struct Thinlens : public Lens {
    mreal<angle_d> fovx, fovy;
    mreal<length_d> focaldist;
    mreal<length_d> aperture;

    Thinlens(const mreal<angle_d>& fovx, const mreal<angle_d>& fovy, const mreal<length_d>& focaldist, const mreal<length_d>& aperture) 
        : fovx(fovx), fovy(fovy), focaldist(focaldist), aperture(aperture) { }

    virtual lensSample<lens_s> sample(const tuple2& puv, const tuple2& luv) { 
        auto q = _focalPlanePoint(puv);
        auto o = _lensPlanePoint(luv);
        return lensSample<lens_s>(o, normalize(q-o));
    }

    point<lens_s> _focalPlanePoint(const tuple2& puv) {
        return point<lens_s>( (2*puv.x-1)*tan(fovx)*focaldist, (2*puv.y-1)*tan(fovy)*focaldist, -focaldist);
    }

    virtual projmap<lens_s, clip_s> get_projection(mreal<length_d> n, mreal<length_d> f)
    {
        projmap<lens_s, clip_s> rm;
        mat4 m;

        mreal<length_d> l = -n * tan(fovx);
        mreal<length_d> r = n * tan(fovx);
        mreal<length_d> t = n * tan(fovy);
        mreal<length_d> b = -n * tan(fovy);

        m.d[0][0] = 2 * n / (r - l);
        m.d[0][2] = (r + l) / (l - r);
        m.d[1][1] = 2 * n / (t - b);
        m.d[1][2] = (t + b) / (t - b);
        m.d[2][2] = (n + f) / (n - f);
        m.d[2][3] = __asreal(2.0 * f * n / (n - f));
        m.d[3][2] = -1.0;
        m.d[3][3] = 0.0;
        rm.m = m;
        return rm;
    }

    point<lens_s> _lensPlanePoint(const tuple2& luv) {
        return point<lens_s>( (2*luv.x-1)*aperture, (2*luv.y-1)*aperture, mreal<length_d>());
    }
};

#endif
