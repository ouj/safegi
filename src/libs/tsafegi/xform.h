#ifndef _XFORM_H_
#define _XFORM_H_

#include "common.h"

// S1 -> S2
template<typename S1, typename S2>
struct Xform {
    virtual rigidmap<S1,S2> sample(const mreal<time_d>& t) = 0;
};

template<typename S1, typename S2>
struct StaticXform : public Xform<S1,S2> {
    rigidmap<S1,S2> m;

    StaticXform(const rigidmap<S1,S2>& m) : m(m) { }
    StaticXform(const vector<S2>& translation) : m(translate<S1,S2>(translation)) { }
    StaticXform(const vector<S2>& translation, const direction<S2>& axis, const real& angle) :
        m(translate<S2,S2>(translation) % rotate<S1,S2>(axis,angle)) { }

    virtual rigidmap<S1,S2> sample(const mreal<time_d>& t) { return m; }
};

template<typename S1, typename S2>
struct AnimatedTranslationXform : public Xform<S1,S2> {
    vector<S2> pos0, pos1;
    mreal<time_d> t0, t1;

    AnimatedTranslationXform(const vector<S2>& pos0, const mreal<time_d>& t0, 
                             const vector<S2>& pos1, const mreal<time_d>& t1) : 
                             pos0(pos0), pos1(pos1), t0(t0), t1(t1) { }

    virtual rigidmap<S1,S2> sample(const mreal<time_d>& t) { 
        vector<S2> pos;
        if(t < t0) pos = pos0;
        else if(t > t1) pos = pos1;
        else {
            real s = (t - t0) / (t1 - t0);
            pos = pos0 * (1-s) + pos1 * s;
        }
        return translate<S1,S2>(pos);
    }
};

#endif
