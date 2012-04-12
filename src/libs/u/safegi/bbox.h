#ifndef _BBOX_H_
#define _BBOX_H_

#include "shape.h"

struct BBox : public Shape {
    boundingbox bbox;
    std::vector<shared_ptr<Shape>> children;

    BBox(const std::vector<shared_ptr<Shape>>& s) : bbox(_bound(s)) { _split(s); }

    virtual isect intersect(const ray& r) {
        if(!_hitbbox(r)) return isect();

        isect is; real mint;
        for(size_t i = 0; i < children.size(); i ++) {
            auto sis = children[i]->intersect(r);
            if(sis.hit && (!is.hit || sis.t < mint)) {
                is = sis;
                mint = sis.t;
            }
        }
        return is;
    }

    virtual bool hit(const ray& r) {
        if(!_hitbbox(r)) return false;

        for(size_t i = 0; i < children.size(); i ++) {
            if(children[i]->hit(r)) return true;
        }
        return false;
    }

    virtual shapeSample sample(const tuple2& ruv) { // not supported
        return shapeSample();
    }

    virtual real area() { // not supported
        return real();
    }

    virtual boundingbox bound() { return bbox; }

private:
    bool _hitbbox(const ray& r) {
        real tmin = r.tmin, tmax = r.tmax;

        auto tnear = scale(bbox.m - r.e, 1/r.d.x, 1/r.d.y, 1/r.d.z);
        auto tfar = scale(bbox.M - r.e,  1/r.d.x, 1/r.d.y, 1/r.d.z);
        if(tnear.x > tfar.x) { auto aux = tnear.x; tnear.x = tfar.x; tfar.x = aux; }
        if(tnear.y > tfar.y) { auto aux = tnear.y; tnear.y = tfar.y; tfar.y = aux; }
        if(tnear.z > tfar.z) { auto aux = tnear.z; tnear.z = tfar.z; tfar.z = aux; }

        tmin = (tnear.x > tmin) ? tnear.x : tmin;
        tmax = (tfar.x < tmax) ? tfar.x : tmax;
        if(tmin > tmax) return false;

        tmin = (tnear.y > tmin) ? tnear.y : tmin;
        tmax = (tfar.y < tmax) ? tfar.y : tmax;
        if(tmin > tmax) return false;

        tmin = (tnear.z > tmin) ? tnear.z : tmin;
        tmax = (tfar.z < tmax) ? tfar.z : tmax;
        if(tmin > tmax) return false;

        return true;
    }

    void _split(const std::vector<shared_ptr<Shape>>& s) {
        // store a flat list if <= 4 shapes
        if(s.size() <= 8) { children = s; return; }

        // slipt the bound in half along the largest axis
        auto bs = size(bbox); auto bo = center(bbox);
        auto halfbox = bbox;
        if(bs.x > bs.y && bs.x > bs.z) { halfbox.m.x = bo.x; }
        else if(bs.y > bs.z) { halfbox.m.y = bo.y; }
        else { halfbox.m.z = bo.z; }

        // biuld lists
        std::vector<shared_ptr<Shape>> minlist, maxlist;
        for(size_t i = 0; i < s.size(); i ++) {
            if(contain(halfbox, center(s[i]->bound()))) minlist.push_back(s[i]);
            else maxlist.push_back(s[i]);
        }

        // add children
        children.push_back(shared_ptr<Shape>(new BBox(minlist)));
        children.push_back(shared_ptr<Shape>(new BBox(maxlist)));
    }

    boundingbox _bound(const std::vector<shared_ptr<Shape>>& s) {
        boundingbox bbox = s[0]->bound();
        for(size_t i = 1; i < s.size(); i ++) bbox = grow(bbox, s[i]->bound());
        return bbox;
    }
#ifdef USE_SAFE_GL
    virtual void gl_draw(Aid pa, Aid na)
    {
        for(size_t i = 0; i < children.size(); i ++) 
        {
            children[i]->gl_draw(pa, na);
        }
    }
#endif
};

#endif
