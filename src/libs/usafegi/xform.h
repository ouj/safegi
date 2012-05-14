#ifndef _XFORM_H_
#define _XFORM_H_

#include "common.h"

struct Xform {
    virtual rigidmap sample(const real& t) = 0;
};

struct StaticXform : public Xform {
    rigidmap m;

    StaticXform(const rigidmap& m) : m(m) { }
    StaticXform(const vector& translation) : m(translate(translation)) { }
    StaticXform(const vector& translation, const direction& axis, const real& angle) :
        m(translate(translation) % rotate(axis,angle)) { }

    virtual rigidmap sample(const real& t) { return m; }
};

struct AnimatedTranslationXform : public Xform {
    vector pos0, pos1;
    real t0, t1;

    AnimatedTranslationXform(const vector& pos0, const real& t0, 
                             const vector& pos1, const real& t1) : 
                             pos0(pos0), pos1(pos1), t0(t0), t1(t1) { }

    virtual rigidmap sample(const real& t) { 
        vector pos;
        if(t < t0) pos = pos0;
        else if(t > t1) pos = pos1;
        else {
            real s = (t - t0) / (t1 - t0);
            pos = pos0 * (1-s) + pos1 * s;
        }
        return translate(pos);
    }
};

#endif
