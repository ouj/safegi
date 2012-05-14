#ifndef _TRACER_H_
#define _TRACER_H_

#include "scene.h"
#include "image.h"
#include "tracerutils.h"

struct Integrator {
    virtual spectrum l(const point& o, const direction& w, const real& t, shared_ptr<Scene> scene) = 0;
};

struct Tracer {
    shared_ptr<Integrator> it;

    Tracer(shared_ptr<Integrator> it) : it(it) { }

    image<spectrum> render(shared_ptr<Scene> scene, const real& t0, const real& t1, int w, int h, int ns) {
        image<spectrum> img(w,h);
        for(int i = 0; i < w; i ++) {
            for(int j = 0; j < h; j ++) {
                img.at(i,j) = spectrum();
                for(int s = 0; s < ns; s ++) {
                    tuple2 puv = tuple2( (i + urandom()) / w, (j + urandom()) / h );
                    tuple2 luv = tuple2( urandom(), urandom() );
                    auto t = t0 + (t1-t0)*urandom();
                    auto ls = scene->camera->sample(puv,luv,t);
                    spectrum c = it->l(ls.o,ls.w,t,scene);
                    img.at(i,j) = img.at(i,j) + c;
                }
                img.at(i,j) = img.at(i,j) / (ns);
            }
        }
        return img;
    }
};

#endif
