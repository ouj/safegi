#ifndef _SHAPE_H_
#define _SHAPE_H_
#define NOMINMAX

#ifdef USE_SAFE_GL
#ifdef WIN32
#include <GL/glew.h>
#include <GL/wglew.h>
#else
#include <GL/glew.h>
#endif
#include"safe_gl.h"
#endif


#include "common.h"

// TODO: shape with sampling
struct Shape {
    virtual isect intersect(const ray& r) = 0;
    virtual bool hit(const ray& r) = 0;
    virtual shapeSample sample(const tuple2& ruv) = 0;
    virtual real area() = 0;
    virtual boundingbox bound() = 0;
#ifdef USE_SAFE_GL
    virtual void gl_draw(Aid pa, Aid na) = 0;
    virtual void gl_init() {};
    virtual void gl_cleanup() {};
#endif
};

struct Sphere : public Shape {
    real radius;
    Sphere(const real& radius) : radius(radius) {
#ifdef USE_SAFE_GL
        gl_init();
#endif
    }
    virtual ~Sphere() {
#ifdef USE_SAFE_GL 
        gl_cleanup();
#endif
    }
    virtual isect intersect(const ray& r) {
        real t;
        if(!_hit(r,t)) return isect();

        auto p = eval(r,t);
        auto d = normalize(asvector(p));
        real phi = atan2(d.y, d.x); if(phi < 0) phi += pi;
        real theta = acos(d.z);

        isect is;
        is.t = t;
        is.hit = true;
        is.uv = tuple2( phi / (2*pi), theta / pi);
        is.dp = frame(p,asnormal(d));

        return is;
    }

    virtual bool hit(const ray& r) {
        real t;
        return _hit(r,t);
    }

    virtual shapeSample sample(const tuple2& ruv) {
        auto phi = 2*pi*ruv.x;
        auto theta = acos(1-2*ruv.y);
        auto n = normal(sin(theta)*cos(phi),sin(theta)*sin(phi),cos(theta));
        auto p = point(n.x*radius,n.y*radius,n.z*radius);
        auto area = radius*radius*4.0*pi;
        return shapeSample(p,n,area);
    }

    virtual real area() {
        return radius*radius*4.0*pi;
    }

    virtual boundingbox bound() {
        return boundingbox(point(-radius,-radius,-radius),point(radius,radius,radius));
    }

#ifdef USE_SAFE_GL //OpenGL relative stuff
    virtual void gl_draw(Aid pa, Aid na) 
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
    VaBuf<point>             vert_va;
    VaBuf<direction>         norm_va;
    void gl_init()
    {
        const int level = 4;
        int phi = 1 << (level+2);
        int theta = 1 << (level+1);
        int nVertex = (phi+1)*(theta+1);
        int nTriangles = phi*theta*2;

        tesselated_vertex_num = nTriangles * 3;
        const double PI = 3.1415926;

        std::vector<point> pos(nVertex);
        std::vector<direction> norm(nVertex);

        for(int t = 0; t <= theta; t ++) {
            for(int p = 0; p <= phi; p ++) {
                int vIdx = p+t*(phi+1);
                auto u = float(p) / float(phi);
                auto v = float(t) / float(theta);
                auto phi = u * 2 * PI;
                auto theta = v * PI;
                direction r = direction(sin(phi)*sin(theta), cos(phi)*sin(theta), cos(theta));
                pos[vIdx] = point() + r * radius;
                norm[vIdx] = r;
            }
        }

        if(!vert_va.ptr)
        {
            safeglCreateVertexAttribArray(vert_va, tesselated_vertex_num);
            safeglCreateVertexAttribArray(norm_va, tesselated_vertex_num);

            int count = 0;
            for(int t = 0; t < theta; t ++)
            {
                for(int p = 0; p < phi; p ++)
                {
                    safeglSetVertexAttribArray(vert_va, count, pos[(p+0)+(t+0)*(phi+1)]); 
                    safeglSetVertexAttribArray(norm_va, count, norm[(p+0)+(t+0)*(phi+1)]);
                    count++;
                    safeglSetVertexAttribArray(vert_va, count, pos[(p+1)+(t+0)*(phi+1)]); 
                    safeglSetVertexAttribArray(norm_va, count, norm[(p+1)+(t+0)*(phi+1)]);
                    count++;
                    safeglSetVertexAttribArray(vert_va, count, pos[(p+1)+(t+1)*(phi+1)]); 
                    safeglSetVertexAttribArray(norm_va, count, norm[(p+1)+(t+1)*(phi+1)]);
                    count++;
                    safeglSetVertexAttribArray(vert_va, count, pos[(p+0)+(t+0)*(phi+1)]); 
                    safeglSetVertexAttribArray(norm_va, count, norm[(p+0)+(t+0)*(phi+1)]);
                    count++;
                    safeglSetVertexAttribArray(vert_va, count, pos[(p+1)+(t+1)*(phi+1)]); 
                    safeglSetVertexAttribArray(norm_va, count, norm[(p+1)+(t+1)*(phi+1)]);
                    count++;
                    safeglSetVertexAttribArray(vert_va, count, pos[(p+0)+(t+1)*(phi+1)]); 
                    safeglSetVertexAttribArray(norm_va, count, norm[(p+0)+(t+1)*(phi+1)]);
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
    bool _hit(const ray& r, real& t) {
        real a = 1.0; // lenghtSqr of direction
        real b = 2.0 * dot(r.d, asvector(r.e));
        real c = lengthSqr(asvector(r.e)) - radius*radius;

        real d = b*b - 4.0*a*c;
        if(__asreal(d) < 0) return false;

        real tm = (-b - sqrt(d)) / (2*a);
        real tM = (-b + sqrt(d)) / (2*a);

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
    real radius;

    Quad(const real& radius) : radius(radius) { 
#ifdef USE_SAFE_GL
        gl_init();
#endif
    }
    virtual ~Quad() { 
#ifdef USE_SAFE_GL
        gl_cleanup();
#endif
    }

    virtual isect intersect(const ray& r) {
        real t; point p; tuple2 uv;
        if(!_hit(r,t,p,uv)) return isect();

        isect is;
        is.t = t;
        is.hit = true;
        is.uv = uv;
        is.dp.o = p;
        is.dp.z = normal(0,0,1);
        is.dp.y = direction(0,1,0);
        is.dp.x = direction(1,0,0);

        return is;
    }

    virtual bool hit(const ray& r) {
        real t; point p; tuple2 uv;
        return _hit(r,t,p,uv);
    }

    virtual shapeSample sample(const tuple2& ruv) {
        auto p = point(radius*(2*ruv.x-1),radius*(2*ruv.y-1),real());
        auto n = normal(0,0,1);
        auto area = 4.0*radius*radius;
        return shapeSample(p,n,area);
    }

    virtual real area() {
        return radius*radius*4.0;
    }

    virtual boundingbox bound() {
        return boundingbox(point(-radius,-radius,real()),point(radius,radius,real()));
    }
#ifdef USE_SAFE_GL
    VaBuf<point> vert_va;
    VaBuf<direction> norm_va;
    virtual void gl_draw(Aid pa, Aid na) 
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
    void gl_init()
    {
        if(!vert_va.ptr)
        {
            safeglCreateVertexAttribArray(vert_va, 4);
            real r = radius;
            safeglSetVertexAttribArray(vert_va, 0, point(-r, -r, 0.0*meters));
            safeglSetVertexAttribArray(vert_va, 1, point(r, -r, 0.0*meters));
            safeglSetVertexAttribArray(vert_va, 2, point(r, r, 0.0*meters));
            safeglSetVertexAttribArray(vert_va, 3, point(-r, r, 0.0*meters));
        }

        if(!norm_va.ptr)
        {
            safeglCreateVertexAttribArray(norm_va, 4);
            safeglSetVertexAttribArray(norm_va, 0, direction(0.0, 0.0, 1.0));
            safeglSetVertexAttribArray(norm_va, 1, direction(0.0, 0.0, 1.0));
            safeglSetVertexAttribArray(norm_va, 2, direction(0.0, 0.0, 1.0));
            safeglSetVertexAttribArray(norm_va, 3, direction(0.0, 0.0, 1.0));
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
    bool _hit(const ray& r, real& t, point& p, tuple2& uv) {
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
    point v0, v1, v2;
    normal n0, n1, n2;

    Triangle(const point& v0, const point& v1, const point& v2) : v0(v0), v1(v1), v2(v2) 
    {
        // default normal if normal is not provided
        n0 = n1 = n2 = asnormal(orthogonal(normalize(v0-v1), normalize(v0-v2)));
#ifdef USE_SAFE_GL
        gl_init();
#endif
    }

    Triangle(const point& v0, const point& v1, const point& v2, 
        const normal& n0, const normal& n1, const normal& n2) 
        : v0(v0), v1(v1), v2(v2), n0(n0), n1(n1), n2(n2) 
    {
#ifdef USE_SAFE_GL
        gl_init();
#endif
    }

    virtual ~Triangle()
    { 
#ifdef USE_SAFE_GL
        gl_cleanup();
#endif
    }

    virtual isect intersect(const ray& r) {
        real t; point p; tuple2 uv;
        if(!_hit(r,t,p,uv)) return isect();

        normal norm;
        vector nv0 = n0 * meters;
        vector nv1 = n1 * meters;
        vector nv2 = n2 * meters;
        norm = asnormal(normalize(nv0 * (1.0-uv.x-uv.y) + nv1 * uv.x + nv2 * uv.y));

        isect is;
        is.t = t;
        is.hit = true;
        is.uv = uv;
        is.dp = frame(p, norm);

        return is;
    }

    virtual bool hit(const ray& r) {
        real t; point p; tuple2 uv;
        return _hit(r,t,p,uv);
    }

    virtual shapeSample sample(const tuple2& ruv) { // not supported
        return shapeSample();
    }

    virtual real area() { // not supported
        return real();
    }

    virtual boundingbox bound() {
        return grow(grow(boundingbox(v0,v0), v1), v2);
    }
#ifdef USE_SAFE_GL
    VaBuf<point>     vert_va;
    VaBuf<direction> norm_va;
    virtual void gl_draw(Aid pa, Aid na)
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
    void _create_gl_buffers()
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

    void _delete_gl_buffers()
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
    bool _hit(const ray& r, real& t, point& p, tuple2& uv) {
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
