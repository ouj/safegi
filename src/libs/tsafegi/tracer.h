#ifndef _TRACER_H_
#define _TRACER_H_

#include "scene.h"
#include "image.h"
#include "tracerutils.h"

struct Integrator {
    virtual spectrum<radiance_d> l(const point<world_s>& o, const direction<world_s>& w, const mreal<time_d>& t, shared_ptr<Scene> scene) = 0;
};

struct Tracer {
    shared_ptr<Integrator> it;

    Tracer(shared_ptr<Integrator> it) : it(it) { }

    image<spectrum<radiance_d>> render(shared_ptr<Scene> scene, const mreal<time_d>& t0, const mreal<time_d>& t1, int w, int h, int ns) {
        image<spectrum<radiance_d>> img(w,h);
        for(int i = 0; i < w; i ++) {
            for(int j = 0; j < h; j ++) {
                img.at(i,j) = spectrum<radiance_d>();
                for(int s = 0; s < ns; s ++) {
                    tuple2 puv = tuple2( (i + urandom()) / w, (j + urandom()) / h );
                    tuple2 luv = tuple2( urandom(), urandom() );
                    auto t = t0 + (t1-t0)*urandom();
                    auto ls = scene->camera->sample(puv,luv,t);
                    spectrum<radiance_d> c = it->l(ls.o,ls.w,t,scene);
                    img.at(i,j) = img.at(i,j) + c;
                }
                img.at(i,j) = img.at(i,j) / (ns);
            }
        }
        return img;
    }
};

#endif
