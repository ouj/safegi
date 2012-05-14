#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "common.h"

struct Lens {
    virtual lensSample sample(const tuple2& puv, const tuple2& luv) = 0;
    virtual projmap get_projection(real n, real f) = 0;
};

struct PinholeLens : public Lens {
    real fovx, fovy;    
    real imagedist;

    PinholeLens(const real& fovx, const real& fovy) : fovx(fovx), fovy(fovy), imagedist(1) { }

    virtual lensSample sample(const tuple2& puv, const tuple2& luv) {
        auto q = _imagePlanePoint(puv);
        auto o = point();
        return lensSample(o, normalize(q-o));
    }

    virtual projmap get_projection(real n, real f)
    {
        projmap rm;
        mat4 m;

        real l = -n * tan(fovx);
        real r = n * tan(fovx);
        real t = n * tan(fovy);
        real b = -n * tan(fovy);

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

    point _imagePlanePoint(const tuple2& puv) {
        return point( (2*puv.x-1)*tan(fovx)*imagedist, (2*puv.y-1)*tan(fovy)*imagedist, -imagedist);
    }
};

struct Thinlens : public Lens {
    real fovx, fovy;
    real focaldist;
    real aperture;

    Thinlens(const real& fovx, const real& fovy, const real& focaldist, const real& aperture) : fovx(fovx), fovy(fovy), focaldist(focaldist), aperture(aperture) { }

    virtual lensSample sample(const tuple2& puv, const tuple2& luv) { 
        auto q = _focalPlanePoint(puv);
        auto o = _lensPlanePoint(luv);
        return lensSample(o, normalize(q-o));
    }

    point _focalPlanePoint(const tuple2& puv) {
        return point( (2*puv.x-1)*tan(fovx)*focaldist, (2*puv.y-1)*tan(fovy)*focaldist, -focaldist);
    }

    virtual projmap get_projection(real n, real f)
    {
        projmap rm;
        mat4 m;

        real l = -n * tan(fovx);
        real r = n * tan(fovx);
        real t = n * tan(fovy);
        real b = -n * tan(fovy);

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

    point _lensPlanePoint(const tuple2& luv) {
        return point( (2*luv.x-1)*aperture, (2*luv.y-1)*aperture, real());
    }
};

#endif
