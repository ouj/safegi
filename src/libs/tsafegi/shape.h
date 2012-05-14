#ifndef _SHAPE_H_
#define _SHAPE_H_
#define NOMINMAX

#ifdef USE_SAFE_GL
#ifdef WIN32
#include <gl/glew.h>
#include <gl/glut.h>
#else
#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>
#endif
#include "safe_gl.h"
#endif


#include "common.h"

// TODO: shape with sampling
struct Shape {
    virtual isect<shape_s> intersect(const ray<shape_s>& r) = 0;
    virtual bool hit(const ray<shape_s>& r) = 0;
    virtual shapeSample<shape_s> sample(const tuple2& ruv) = 0;
    virtual mreal<area_d> area() = 0;
    virtual boundingbox<shape_s> bound() = 0;
#ifdef USE_SAFE_GL
    virtual void gl_draw(Aid<point<shape_s>> pa, Aid<normal<shape_s>> na) = 0;
protected:
    virtual void gl_init() {};
    virtual void gl_cleanup() {};
#endif
};

struct Sphere : public Shape {
    mreal<length_d> radius;

    Sphere(const mreal<length_d>& radius) : radius(radius) {
#ifdef USE_SAFE_GL 
        gl_init();
#endif
    }

    virtual ~Sphere() { 
#ifdef USE_SAFE_GL
        gl_cleanup();
#endif
    }

    virtual isect<shape_s> intersect(const ray<shape_s>& r) {
        mreal<length_d> t;
        if(!_hit(r,t)) return isect<shape_s>();

        auto p = eval(r,t);
        auto d = normalize(asvector(p));
        real phi = atan2(d.y, d.x); if(phi < 0) phi += pi;
        real theta = acos(d.z);

        isect<shape_s> is;
        is.t = t;
        is.hit = true;
        is.uv = tuple2( phi / (2*pi), theta / pi);
        is.dp = frame<shape_s,local_s>(p,asnormal(d));

        return is;
    }


    virtual bool hit(const ray<shape_s>& r) {
        mreal<length_d> t;
        return _hit(r,t);
    }

    virtual shapeSample<shape_s> sample(const tuple2& ruv) {
        auto phi = ruv.x*circleAngle;
        auto theta = _acos(1-2*ruv.y);
        auto n = normal<shape_s>(_sin(theta)*_cos(phi),_sin(theta)*_sin(phi),_cos(theta));
        auto p = point<shape_s>(n.x*radius,n.y*radius,n.z*radius);
        auto area = radius*radius*4.0*pi;
        return shapeSample<shape_s>(p,n,area);
    }

    virtual mreal<area_d> area() {
        return radius*radius*4.0*pi;
    }

    virtual boundingbox<shape_s> bound() {
        return boundingbox<shape_s>(point<shape_s>(-radius,-radius,-radius),point<shape_s>(radius,radius,radius));
    }
#ifdef USE_SAFE_GL
public:
    virtual void gl_draw(Aid<point<shape_s>> pa, Aid<normal<shape_s>> na)
    {
        safeglEnableClientState(GL_VERTEX_ARRAY);
        safeglEnableVertexAttribArray(pa);
        safeglEnableVertexAttribArray(na);
        safeglVertexAttribPointer(pa, 0, 0, vert_va);
        safeglVertexAttribPointer(na, 0, 0, norm_va);
        safeglDrawArrays(GL_TRIANGLES, 0, tesselated_vertex_num);
        safeglDisableVertexAttribArray(pa);
        safeglDisableVertexAttribArray(na);
        safeglDisableClientState(GL_VERTEX_ARRAY);
    }
private:
    int tesselated_vertex_num;
    VaBuf<point<shape_s>>           vert_va;
    VaBuf<normal<shape_s>>          norm_va;
    void gl_init()
    {
        const int level = 4;
        int nPhi = 1 << (level+2);
        int nTheta = 1 << (level+1);
        int nVertex = (nPhi+1)*(nTheta+1);
        int nTriangles = nPhi*nTheta*2;

        tesselated_vertex_num = nTriangles * 3;

        std::vector<point<shape_s>> pos(nVertex);
        std::vector<normal<shape_s>> norm(nVertex);

        for(int t = 0; t <= nTheta; t ++) {
            for(int p = 0; p <= nPhi; p ++) {
                int vIdx = p+t*(nPhi+1);
                auto u = float(p) / float(nPhi);
                auto v = float(t) / float(nTheta);
                auto phi = u * circleAngle;
                auto theta = v * halfCircleAngle;
                auto d = direction<shape_s>(_sin(phi)*_sin(theta), _cos(phi)*_sin(theta), _cos(theta));
                pos[vIdx] = point<shape_s>() + d * radius;
                norm[vIdx] = asnormal(d);
            }
        }

        if(!vert_va.ptr)
        {
            safeglCreateVertexAttribArray(vert_va, tesselated_vertex_num);
            safeglCreateVertexAttribArray(norm_va, tesselated_vertex_num);

            int count = 0;
            for(int t = 0; t < nTheta; t ++)
            {
                for(int p = 0; p < nPhi; p ++)
                {
                    safeglSetVertexAttribArray(vert_va, count, pos[(p+0)+(t+0)*(nPhi+1)]); 
                    safeglSetVertexAttribArray(norm_va, count, norm[(p+0)+(t+0)*(nPhi+1)]);
                    count++;
                    safeglSetVertexAttribArray(vert_va, count, pos[(p+1)+(t+0)*(nPhi+1)]); 
                    safeglSetVertexAttribArray(norm_va, count, norm[(p+1)+(t+0)*(nPhi+1)]);
                    count++;
                    safeglSetVertexAttribArray(vert_va, count, pos[(p+1)+(t+1)*(nPhi+1)]); 
                    safeglSetVertexAttribArray(norm_va, count, norm[(p+1)+(t+1)*(nPhi+1)]);
                    count++;
                    safeglSetVertexAttribArray(vert_va, count, pos[(p+0)+(t+0)*(nPhi+1)]); 
                    safeglSetVertexAttribArray(norm_va, count, norm[(p+0)+(t+0)*(nPhi+1)]);
                    count++;
                    safeglSetVertexAttribArray(vert_va, count, pos[(p+1)+(t+1)*(nPhi+1)]); 
                    safeglSetVertexAttribArray(norm_va, count, norm[(p+1)+(t+1)*(nPhi+1)]);
                    count++;
                    safeglSetVertexAttribArray(vert_va, count, pos[(p+0)+(t+1)*(nPhi+1)]); 
                    safeglSetVertexAttribArray(norm_va, count, norm[(p+0)+(t+1)*(nPhi+1)]);
                    count++;
                }
            }
        }
    }
    void gl_cleanup()
    {
        if(vert_va.ptr)
        {
            safeglDeleteVertexAttribArray(vert_va);
        }
        if(norm_va.ptr)
        {
            safeglDeleteVertexAttribArray(norm_va);
        }
    }
#endif
private:
    bool _hit(const ray<shape_s>& r, mreal<length_d>& t) {
        auto a = 1.0; // lenghtSqr of direction
        auto b = 2.0 * dot(r.d, asvector(r.e));
        auto c = lengthSqr(asvector(r.e)) - radius*radius;

        auto d = b*b - 4.0*a*c;
        if(__asreal(d) < 0) return false;

        mreal<length_d> tm = (-b - sqrt(d)) / (2*a);
        mreal<length_d> tM = (-b + sqrt(d)) / (2*a);

        if (tm > r.tmin && tm < r.tmax) {
            t = tm; return true;
        } else if (tM > r.tmin && tM < r.tmax) {
            t = tM; return true;
        } else {
            return false;
        }
    }
};

// quad aligned in the z axis
struct Quad : public Shape {
    mreal<length_d> radius;

    Quad(const mreal<length_d>& radius) : radius(radius) 
    {
#ifdef USE_SAFE_GL 
        gl_init();
#endif
    }
    virtual ~Quad() {
#ifdef USE_SAFE_GL
        gl_cleanup();
#endif
    }

    virtual isect<shape_s> intersect(const ray<shape_s>& r) {
        mreal<length_d> t; point<shape_s> p; tuple2 uv;
        if(!_hit(r,t,p,uv)) return isect<shape_s>();

        isect<shape_s> is;
        is.t = t;
        is.hit = true;
        is.uv = uv;
        is.dp.o = p;
        is.dp.z = normal<shape_s>(0,0,1);
        is.dp.y = direction<shape_s>(0,1,0);
        is.dp.x = direction<shape_s>(1,0,0);

        return is;
    }

    virtual bool hit(const ray<shape_s>& r) {
        mreal<length_d> t; point<shape_s> p; tuple2 uv;
        return _hit(r,t,p,uv);
    }

    virtual shapeSample<shape_s> sample(const tuple2& ruv) {
        auto p = point<shape_s>(radius*(2*ruv.x-1),radius*(2*ruv.y-1),mreal<length_d>());
        auto n = normal<shape_s>(0,0,1);
        auto area = 4.0*radius*radius;
        return shapeSample<shape_s>(p,n,area);
    }

    virtual mreal<area_d> area() {
        return radius*radius*4.0;
    }

    virtual boundingbox<shape_s> bound() {
        return boundingbox<shape_s>(point<shape_s>(-radius,-radius,mreal<length_d>()),point<shape_s>(radius,radius,mreal<length_d>()));
    }
#ifdef USE_SAFE_GL
    void gl_init()
    {
        if(!vert_va.ptr)
        {
            safeglCreateVertexAttribArray(vert_va, 4);
            mreal<length_d> r = radius;
            safeglSetVertexAttribArray(vert_va, 0, point<shape_s>(-r, -r, 0.0*meters));
            safeglSetVertexAttribArray(vert_va, 1, point<shape_s>(r, -r, 0.0*meters));
            safeglSetVertexAttribArray(vert_va, 2, point<shape_s>(r, r, 0.0*meters));
            safeglSetVertexAttribArray(vert_va, 3, point<shape_s>(-r, r, 0.0*meters));
        }
        if(!norm_va.ptr)
        {
            safeglCreateVertexAttribArray(norm_va, 4);
            safeglSetVertexAttribArray(norm_va, 0, normal<shape_s>(0.0, 0.0, 1.0));
            safeglSetVertexAttribArray(norm_va, 1, normal<shape_s>(0.0, 0.0, 1.0));
            safeglSetVertexAttribArray(norm_va, 2, normal<shape_s>(0.0, 0.0, 1.0));
            safeglSetVertexAttribArray(norm_va, 3, normal<shape_s>(0.0, 0.0, 1.0));
        }
    }
    void gl_cleanup()
    {
        if(vert_va.ptr)
        {
            safeglDeleteVertexAttribArray(vert_va);
        }
        if(norm_va.ptr)
        {
            safeglDeleteVertexAttribArray(norm_va);
        }
    }
    VaBuf<point<shape_s>> vert_va;
    VaBuf<normal<shape_s>> norm_va;
    virtual void gl_draw(Aid<point<shape_s>> pa, Aid<normal<shape_s>> na)
    {
        safeglEnableClientState(GL_VERTEX_ARRAY);
        safeglEnableVertexAttribArray(pa);
        safeglEnableVertexAttribArray(na);
        safeglVertexAttribPointer(pa, 0, 0, vert_va);
        safeglVertexAttribPointer(na, 0, 0, norm_va);
        safeglDrawArrays(GL_QUADS, 0, 4);
        safeglDisableVertexAttribArray(pa);
        safeglDisableVertexAttribArray(na);
        safeglDisableClientState(GL_VERTEX_ARRAY);
    }
#endif
private:
    bool _hit(const ray<shape_s>& r, mreal<length_d>& t, point<shape_s>& p, tuple2& uv) {
        if(r.d.z == 0) return false;

        t = -r.e.z/r.d.z;
        if(t < r.tmin || t > r.tmax) return false;

        p = eval(r,t);
        uv = tuple2( 0.5*(p.x/radius)+0.5, 0.5*(p.y/radius)+0.5 );

        if(uv.x < 0 || uv.x > 1 || uv.y < 0 || uv.y > 1) return false;

        return true;
    }
};

struct Triangle : public Shape {
    point<shape_s> v0, v1, v2;
    normal<shape_s> n0, n1, n2;

    Triangle(const point<shape_s>& v0, const point<shape_s>& v1, const point<shape_s>& v2) 
        : v0(v0), v1(v1), v2(v2) 
    {
        // default normal if normal is not provided
        n0 = n1 = n2 = asnormal(orthogonal(normalize(v0-v1), normalize(v0-v2)));
#ifdef USE_SAFE_GL
        gl_init();
#endif
    }

    Triangle(const point<shape_s>& v0, const point<shape_s>& v1, const point<shape_s>& v2, 
        const normal<shape_s>& n0, const normal<shape_s>& n1, const normal<shape_s>& n2) 
        : v0(v0), v1(v1), v2(v2), n0(n0), n1(n1), n2(n2) {
#ifdef USE_SAFE_GL 
            gl_init();
#endif
    }

    virtual ~Triangle() {
#ifdef USE_SAFE_GL 
        gl_cleanup();
#endif
    }

    virtual isect<shape_s> intersect(const ray<shape_s>& r) {
        mreal<length_d> t; point<shape_s> p; tuple2 uv;
        if(!_hit(r,t,p,uv)) return isect<shape_s>();

        normal<shape_s> norm;
        vector<shape_s> nv0 = n0 * meters;
        vector<shape_s> nv1 = n1 * meters;
        vector<shape_s> nv2 = n2 * meters;
        norm = asnormal(normalize(nv0 * (1.0-uv.x-uv.y) + nv1 * uv.x + nv2 * uv.y));

        isect<shape_s> is;
        is.t = t;
        is.hit = true;
        is.uv = uv;
        is.dp = frame<shape_s,local_s>(p, norm);
        return is;
    }

    virtual bool hit(const ray<shape_s>& r) {
        mreal<length_d> t; point<shape_s> p; tuple2 uv;
        return _hit(r,t,p,uv);
    }

    virtual shapeSample<shape_s> sample(const tuple2& ruv) { // not supported
        return shapeSample<shape_s>();
    }

    virtual mreal<area_d> area() { // not supported
        return mreal<area_d>();
    }

    virtual boundingbox<shape_s> bound() {
        return grow(grow(boundingbox<shape_s>(v0,v0), v1), v2);
    }
#ifdef USE_SAFE_GL
    VaBuf<point<shape_s>>     vert_va;
    VaBuf<normal<shape_s>>    norm_va;
    virtual void gl_draw(Aid<point<shape_s>> pa, Aid<normal<shape_s>> na)
    {
        safeglEnableClientState(GL_VERTEX_ARRAY);
        safeglEnableVertexAttribArray(pa);
        safeglEnableVertexAttribArray(na);
        safeglVertexAttribPointer(pa, 0, 0, vert_va);
        safeglVertexAttribPointer(na, 0, 0, norm_va);
        safeglDrawArrays(GL_TRIANGLES, 0, 3);
        safeglDisableVertexAttribArray(pa);
        safeglDisableVertexAttribArray(na);
        safeglDisableClientState(GL_VERTEX_ARRAY);
    }
private:
    void gl_init()
    {
        if(!vert_va.ptr)
        {
            safeglCreateVertexAttribArray(vert_va, 3);
            safeglSetVertexAttribArray(vert_va, 0, v0);
            safeglSetVertexAttribArray(vert_va, 1, v1);
            safeglSetVertexAttribArray(vert_va, 2, v2);
        }
        if(!norm_va.ptr)
        {
            safeglCreateVertexAttribArray(norm_va, 3);
            safeglSetVertexAttribArray(norm_va, 0, n0);
            safeglSetVertexAttribArray(norm_va, 1, n1);
            safeglSetVertexAttribArray(norm_va, 2, n2);
        }
    }

    void gl_cleanup()
    {
        if(vert_va.ptr)
        {
            safeglDeleteVertexAttribArray(vert_va);
        }
        if(norm_va.ptr)
        {
            safeglDeleteVertexAttribArray(norm_va);
        }
    }
#endif
private:
    bool _hit(const ray<shape_s>& r, mreal<length_d>& t, point<shape_s>& p, tuple2& uv) {
        // setup
        auto ab = v0-v1;
        auto ac = v0-v2;
        auto ae = v0-r.e;

        // rename values
        auto a = ab.x, b = ab.y, c = ab.z;
        auto d = ac.x, e = ac.y, f = ac.z;
        auto g = r.d.x, h = r.d.y, i = r.d.z;
        auto j = ae.x, k = ae.y, l = ae.z;

        // TODO: remove repetitions

        // denominator
        auto M = a*e*i-a*h*f+b*g*f-b*d*i+c*d*h-c*e*g;
        if(iszero(M)) return false;

        // t
        t = - (f*a*k-f*j*b+e*j*c-e*a*l+d*b*l-d*k*c) / M;
        if(t < r.tmin || t > r.tmax) return false;

        // a, b
        uv.x = (j*e*i-j*h*f+k*g*f-k*d*i+l*d*h-l*e*g) / M;
        uv.y = (i*a*k-i*j*b+h*j*c-h*a*l+g*b*l-g*k*c) / M;

        if(uv.x < 0 || uv.x > 1) return false;
        if(uv.y < 0 || uv.y > 1 - uv.x) return false;

        p = eval(r,t);

        return true;
    }
};

#endif
