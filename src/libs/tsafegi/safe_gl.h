#ifndef _SAFE_GL_H_
#define _SAFE_GL_H_

#include "common.h"

#include <string>
#include <map>
using std::map;
using std::string;

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

#include <assert.h>
#include <sparser/type_checker.h>
#include "type_trait.h"

inline void __lineup_mat(const mat4& mat, float *f)
{
    for(int i = 0;i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            f[i * 4 + j] = static_cast<float>(mat.d[i][j]);
        }
    }
}

template<typename T>
void safeglCreateTexture2D(TexId<T> &s, GLenum target, GLint level, GLint internalFormat, 
    GLsizei width, GLsizei height, GLint border,  GLenum format, const GLvoid *data )
{
    assert(false);
};

template<typename D>
void safeglCreateTexture2D(TexId<mreal<D>> &s, GLenum target, GLint level, 
    GLsizei width, GLsizei height, GLint border, const GLvoid *data )
{
    glGenTextures(1, &s.id);
    glBindTexture(GL_TEXTURE_2D, s.id);
    glTexImage2D( GL_TEXTURE_2D, level, GL_DEPTH_COMPONENT32, width, height, border, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );
    glBindTexture(GL_TEXTURE_2D, 0);
}

template<typename D>
void safeglCreateTexture2D(TexId<spectrum<D>> &s, GLenum target, GLint level, 
    GLsizei width, GLsizei height, GLint border, const GLvoid *data )
{
    glGenTextures(1, &s.id);
    glBindTexture(GL_TEXTURE_2D, s.id);
    glTexImage2D( GL_TEXTURE_2D, level, GL_RGB32F, width, height, border, GL_RGBA, GL_FLOAT, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );
    glBindTexture(GL_TEXTURE_2D, 0);
}

template<typename T>
void safeglDeleteTexture(TexId<T> &s)
{
    glDeleteRenderbuffersEXT(1, &s.id);
}

struct no_buffer
{};

template<typename T>
struct color_buffer
{};

template<typename T>
struct depth_buffer
{};

template<typename D>
struct color_buffer<spectrum<D>>
{
    typedef spectrum<D> data_type;
};

template<typename D>
struct depth_buffer<mreal<D>>
{
    typedef spectrum<D> data_type;
};

template<typename C0, typename C1, typename D>
struct FboId
{
    GLuint id;
};

template<typename C0, typename C1, typename D>
void safeglGenFramebuffer(FboId<C0, C1, D> *framebuffers)
{
    glGenFramebuffersEXT(1, &(framebuffers->id));
}

template<typename C0, typename C1, typename D>
void safeglDeleteFramebuffer(FboId<C0, C1, D> *framebuffers)
{
    glDeleteFramebuffersEXT(1, &(framebuffers->id));
}

typedef FboId<no_buffer, no_buffer, depth_buffer<mreal<length_d>>> depth_only_fbo_id;
typedef FboId<color_buffer<spectrum<radiance_d>>, no_buffer, depth_buffer<mreal<length_d>>> color_depth_fbo_id;
typedef FboId<color_buffer<spectrum<radiance_d>>, color_buffer<spectrum<radiance_d>>, depth_buffer<mreal<length_d>>> color2_depth_fbo_id;

template<typename C0, typename C1, typename D>
void safeglBindFramebuffer(FboId<C0, C1, D> *framebuffers)
{
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, framebuffers->id);
}

inline void safeglUnbindFramebuffer()
{
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
}

template<typename D, typename T, typename T1>
void safeglFramebufferDepthTexture2D(FboId<T, T1, depth_buffer<mreal<D>>> *framebuffers, TexId<mreal<D>> texture)
{
    glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT,GL_TEXTURE_2D, texture.id, 0);
}

template<typename D0, typename T, typename T1>
void safeglFramebufferColorTexture2D(FboId<color_buffer<spectrum<D0>>, T, T1> *framebuffers, 
    TexId<spectrum<D0>> texture1)
{
    glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT,GL_TEXTURE_2D, texture1.id, 0);
}

template<typename D0, typename D1, typename T>
void safeglFramebufferColorTexture2D(FboId<color_buffer<spectrum<D0>>, color_buffer<spectrum<D1>>, T> *framebuffers, 
    TexId<spectrum<D0>> texture1, TexId<spectrum<D1>> texture2)
{
    safeglFramebufferColorTexture2D<D0>(framebuffers, texture1);
    glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT1_EXT,GL_TEXTURE_2D, texture2.id, 0);
}

template<typename D0, typename D1, typename D2>
void safeglFramebufferColorAndDepthTexture2D(FboId<color_buffer<spectrum<D0>>, color_buffer<spectrum<D1>>, depth_buffer<mreal<D2>>> *framebuffers, 
    TexId<color_buffer<spectrum<D0>>> texture1, TexId<color_buffer<spectrum<D1>>> texture2, TexId<mreal<D2>> texture3)
{
    safeglFramebufferColorTexture2D<D0, D1>(framebuffers, texture1, texture2);
    glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT,GL_TEXTURE_2D, texture3.id, 0);
}

void __lineup_mat(const mat4& mat, float *f);

#define safeglCreateShader  __safeglCreateShader
#define safeglCreateProgram __safeglCreateProgram
#define safeglUseProgram    __safeglUseProgram
#define safeglShaderSource  __safeglShaderSource
#define safeglCompileShader __safeglCompileShader
#define safeglAttachShader  __safeglAttachShader
#define safeglLinkProgram   __safeglLinkProgram
#define safeglDetachShader  __safeglDetachShader
#define safeglDeleteShader  __safeglDeleteShader
#define safeglDeleteProgram __safeglDeleteProgram


GLuint __safeglCreateShader(GLenum shaderType);
GLuint __safeglCreateProgram(void);
void __safeglUseProgram(GLuint program);
void __safeglShaderSource(GLuint shader, GLsizei count, const GLchar **string, const GLint *length);
void __safeglCompileShader(GLuint shader); 
void __safeglAttachShader(GLuint program, GLuint shader);
void __safeglLinkProgram(GLuint program);
void __safeglDetachShader(GLuint program, GLuint shader);
void __safeglDeleteShader(GLuint shader);
void __safeglDeleteProgram(GLuint program); 

using std::map;

struct safeglShader
{
    GLuint obj;
    string source;
    t_info info;
};

struct safeglProgram
{
    safeglProgram() : obj(0), shader1(0), shader2(0){}
    GLuint obj;
    safeglShader* shader1;
    safeglShader* shader2;
};

struct safegl
{
    ~safegl()
    {
        for(unsigned int i = 0; i < shaders.size(); i++)
        {
            delete shaders[i];
            shaders[i] = 0;
        }
        for(unsigned int i = 0; i < programs.size(); i++)
        {
            delete programs[i];
            programs[i] = 0;
        }
    }
    std::vector<safeglProgram*> programs;
    std::vector<safeglShader*> shaders;
};

static safegl g;

template<typename T>
inline GLuint get_free_slot(std::vector<T*> &collection)
{
    unsigned int idx = -1;
    for(unsigned int i = 0; i < collection.size(); i++)
    {
        if(collection[i] == NULL)
        {
            collection[i] = new T();
            idx = i;
        }
    }
    if(idx == -1)
    {
        collection.push_back(new T());
        idx = collection.size() - 1;
    }
    return idx + 1;
}

template<typename T>
inline T* _get_pointer(std::vector<T*> &collection, GLuint index)
{
    index--;
    if(index >= collection.size())
        return NULL;
    else
        return collection[index];
}

template<typename T>
inline void _reset(std::vector<T*> &collection, GLuint index)
{
    index--;
    if(index >= collection.size())
        return;
    else
    {
        if(collection[index])
        {
            delete collection[index];
            collection[index] = 0;
        }
    }
}

inline GLuint __safeglCreateShader(GLenum shaderType)
{
    safeglShader *shader = NULL;
    unsigned int idx = get_free_slot(g.shaders);
    shader = _get_pointer(g.shaders, idx);
    shader->obj = glCreateShader(shaderType);
    return idx;
}

inline void __safeglShaderSource(GLuint index, GLsizei count, const GLchar **string, const GLint *length)
{
    assert(count == 1 && length == 0); // do not support other options yet;
    if(count != 1 || length != 0)
        return;
    safeglShader *shader = _get_pointer(g.shaders, index);
    if(!shader)
        return;

    bool is_passed = type_check(*string, shader->source, &(shader->info));
    if(is_passed)
    {
        const GLchar *src = shader->source.c_str();
        glShaderSource(shader->obj, 1, &src, 0);
    }
    else
        fprintf(stderr, "Type check failed!\n");
}

inline void __safeglCompileShader(GLuint index)
{
    safeglShader *shader = _get_pointer(g.shaders, index);
    if(!shader)
        return;

    glCompileShader(shader->obj);
}

inline void __safeglAttachShader(GLuint program_idx, GLuint shader_idx)
{
    safeglProgram *prog = _get_pointer(g.programs, program_idx);
    if(!prog)
        return;
    safeglShader *shader = _get_pointer(g.shaders, shader_idx);
    assert(!prog->shader1 || !prog->shader2);
    if(prog->shader1 && prog->shader2)
        return;
    if(!prog->shader1)
    {
        prog->shader1 = shader;
        glAttachShader(prog->obj, shader->obj);
    }
    else if(!prog->shader2)
    {
        prog->shader2 = shader;
        glAttachShader(prog->obj, shader->obj);
    }
}

inline void __safeglLinkProgram(GLuint program_idx)
{
    // check varying type;
    safeglProgram *prog = _get_pointer(g.programs, program_idx);
    if(!prog)
        return;
    if(!prog->shader1 || !prog->shader2)
        return;

    map<string, t_varying> &vary_map1 = prog->shader1->info.varyings;
    map<string, t_varying> &vary_map2 = prog->shader2->info.varyings;

    map<string, t_varying>::iterator vit1 = vary_map1.begin();
    map<string, t_varying>::iterator vit2;
    while(vit1 != vary_map1.end())
    {
        vit2 = vary_map2.find(vit1->first);
        if(vit2 != vary_map2.end())
        {
            if(*(vit1->second.type) != *(vit2->second.type))
            {
                assert(false);
                fprintf(stderr, "Link error, varyings do not match\n");
            }
        }
        vit1++;
    }
    glLinkProgram(prog->obj);
}

inline GLuint __safeglCreateProgram()
{
    safeglProgram *prog = NULL;
    unsigned int idx = get_free_slot(g.programs);
    prog = _get_pointer(g.programs, idx);
    prog->obj = glCreateProgram();
    return idx;
}

inline void __safeglUseProgram(GLuint program_idx)
{
    if(program_idx != 0)
    {
        safeglProgram *prog = _get_pointer(g.programs, program_idx);
        if(!prog)
            return;
        glUseProgram(prog->obj);
    }
    else
        glUseProgram(0);
}

inline void __safeglDetachShader(GLuint program_idx, GLuint shader_idx)
{
    safeglProgram *prog = _get_pointer(g.programs, program_idx);
    if(!prog)
        return;
    safeglShader *shader = _get_pointer(g.shaders, shader_idx);
    if(!shader)
        return;

    if(prog->shader1 == shader)
        prog->shader1 = 0;
    if(prog->shader2 == shader)
        prog->shader2 = 0;
}

inline void __safeglDeleteShader(GLuint shader_idx)
{
    _reset(g.shaders, shader_idx);    
}

inline void __safeglDeleteProgram(GLuint program_idx)
{
    _reset(g.programs, program_idx);    
}

inline GLint __get_uniform_signature(GLuint program_idx, const string &signature, const GLchar *name)
{
    safeglProgram *prog = _get_pointer(g.programs, program_idx);
    if(!prog)
        return -1;
    if(!prog->shader1 || !prog->shader2)
        return -1;

    map<string, t_uniform> &uniform_map1 = prog->shader1->info.uniforms;
    map<string, t_uniform> &uniform_map2 = prog->shader2->info.uniforms;

    map<string, t_uniform>::iterator vit;
    vit = uniform_map1.find(name);
    if(vit != uniform_map1.end())
    {
        if(vit->second.type->get_signature() == signature)
        {
            return glGetUniformLocation(prog->obj, name);;
        }
    }
    vit = uniform_map2.find(name);
    if(vit != uniform_map2.end())
    {
        if(vit->second.type->get_signature() == signature)
        {
            return glGetUniformLocation(prog->obj, name);
        }
    }
    return -1;
}

inline GLint __get_attrib_signature(GLuint program_idx, const string &signature, const GLchar *name)
{
    safeglProgram *prog = _get_pointer(g.programs, program_idx);
    if(!prog)
        return -1;
    if(!prog->shader1 || !prog->shader2)
        return -1;

    map<string, t_attribute> &attrib_map1 = prog->shader1->info.attributes;
    map<string, t_attribute> &attrib_map2 = prog->shader2->info.attributes;

    map<string, t_attribute>::iterator vit;
    vit = attrib_map1.find(name);
    if(vit != attrib_map1.end())
    {
        if(vit->second.type->get_signature() == signature)
        {
            return glGetAttribLocation(prog->obj, name);;
        }
    }
    vit = attrib_map2.find(name);
    if(vit != attrib_map2.end())
    {
        if(vit->second.type->get_signature() == signature)
        {
            return glGetAttribLocation(prog->obj, name);
        }
    }
    return -1;
}

template<typename T>
struct Lid {  GLint v; };

inline GLint __get_uniform_signature(GLuint program, const string &signature, const GLchar *name);
inline GLint __get_attrib_signature(GLuint program_idx, const string &signature, const GLchar *name);

template<typename T>
inline Lid<T> safeglGetUniformLocation(GLuint program, const GLchar *name)
{
    Lid<T> l;
    l.v = __get_uniform_signature(program, type_signature<T>::get(), name);
    return l;
};

template<typename T>
inline void safeglUniform(Lid<T> lid, const T &o);

template<>
inline void safeglUniform(Lid<real> lid, const real &o)
{
    glUniform1f(lid.v, GLfloat(o));
}

template<typename D>
inline void safeglUniform(Lid<mreal<D>> lid, const mreal<D> &o)
{
    glUniform1f(lid.v, GLfloat(__asreal(o)));
}

template<typename S>
inline void safeglUniform(Lid<point<S>> lid, const point<S> &o)
{
    glUniform3f(lid.v, GLfloat(__asreal(o.x)), GLfloat(__asreal(o.y)), GLfloat(__asreal(o.z)));
}

template<typename S>
inline void safeglUniform(Lid<direction<S>> lid, const direction<S> &o)
{
    glUniform3f(lid.v, GLfloat(o.x), GLfloat(o.y), GLfloat(o.z));
}

template<typename S>
inline void safeglUniform(Lid<normal<S>> lid, const normal<S> &o)
{
    glUniform3f(lid.v, GLfloat(__asreal(o.x)), GLfloat(__asreal(o.y)), GLfloat(__asreal(o.z)));
}

template<typename D>
inline void safeglUniform(Lid<spectrum<D>> lid, const spectrum<D> &o)
{
    glUniform3f(lid.v, GLfloat(__asreal(o.r)), GLfloat(__asreal(o.g)), GLfloat(__asreal(o.b)));
}

template<typename S1, typename S2>
inline void safeglUniform(Lid<rigidmap<S1, S2>> lid, const rigidmap<S1, S2> &o)
{
    static float lm[32];
    __lineup_mat(o.m, lm);
    __lineup_mat(o.mi, lm+16);
    glUniformMatrix4fv(lid.v, 2, true, lm);
}

template<typename S1, typename S2>
inline void safeglUniform(Lid<projmap<S1, S2>> lid, const projmap<S1, S2> &o)
{
    static float lm[32];
    __lineup_mat(o.m, lm);
    __lineup_mat(o.mi, lm+16);
    glUniformMatrix4fv(lid.v, 2, true, lm);
}

template<typename T>
inline void safeglUniform(Lid<TexId<T>> lid, const TexId<T> &o, GLuint i)
{
    glActiveTexture(GL_TEXTURE0 + i);
    glBindTexture(GL_TEXTURE_2D, o.id);
    glUniform1i(lid.v, i);
}

// Attribute
template<typename T>
struct Aid {  GLint v; };


template<typename T>
inline Aid<T> safeglGetAttribLocation(GLuint program, const GLchar *name)
{
    Aid<T> a;
    a.v = __get_attrib_signature(program, type_signature<T>::get(), name);
    return a;
};

template<typename T>
inline void safeglVertexAttrib(Aid<T> aid, const T &o);

template<>
inline void safeglVertexAttrib(Aid<real> aid, const real &o)
{
    glVertexAttrib1f(aid.v, GLfloat(o));
}

template<typename D>
inline void safeglVertexAttrib(Aid<mreal<D>> aid, const mreal<D> &o)
{
    glVertexAttrib1f(aid.v, GLfloat(o));
}

template<typename S>
inline void safeglVertexAttrib(Aid<point<S>> aid, const point<S> &o)
{
    glVertexAttrib3f(aid.v, GLfloat(__asreal(o.x)), GLfloat(__asreal(o.y)), GLfloat(__asreal(o.z)));
}

template<typename S>
inline void safeglVertexAttrib(Aid<direction<S>> aid, const direction<S> &o)
{
    glVertexAttrib3f(aid.v, GLfloat(o.x), GLfloat(o.y), GLfloat(o.z));
}

template<typename S>
inline void safeglVertexAttrib(Aid<normal<S>> aid, const normal<S> &o)
{
    glVertexAttrib3f(aid.v, GLfloat(__asreal(o.x)), GLfloat(__asreal(o.y)), GLfloat(__asreal(o.z)));
}


template<typename D>
inline void safeglVertexAttrib(Aid<spectrum<D>> aid, const spectrum<D> &o)
{
    glVertexAttrib3f(aid.v, GLfloat(__asreal(o.x)), GLfloat(__asreal(o.y)), GLfloat(__asreal(o.z)));
}


template<typename T>
inline void safeglEnableVertexAttribArray(Aid<T> aid)
{
    glEnableVertexAttribArray(aid.v);
}

template<typename T>
void safeglDisableVertexAttribArray(Aid<T> aid)
{
    glDisableVertexAttribArray(aid.v);
}

//geometry
template<typename T>
inline void safeglVertex(const T& p);

template<>
inline void safeglVertex(const point<shape_s>& p)
{
    glVertex3f(GLfloat(__asreal(p.x)), GLfloat(__asreal(p.y)), GLfloat(__asreal(p.z)));
}

template<typename T>
inline void safeglNormal(const T& n);

template<>
inline void safeglNormal(const direction<shape_s>& n)
{
    glVertex3f(GLfloat(n.x), GLfloat(n.y), GLfloat(n.z));
}



//Vertext Array
template<typename T>
struct VaBuf
{
    VaBuf() : ptr(0) {}
    float *ptr;
};

template<typename T>
void safeglCreateVertexAttribArray(VaBuf<T> &id, GLuint size);
template<typename S>
void safeglCreateVertexAttribArray(VaBuf<point<S>> &id, GLuint size)
{
    id.ptr = new float[size * 3];
}
template<typename S>
void safeglCreateVertexAttribArray(VaBuf<direction<S>> &id, GLuint size)
{
    id.ptr = new float[size * 3];  
}
template<typename S>
void safeglCreateVertexAttribArray(VaBuf<normal<S>> &id, GLuint size)
{
    id.ptr = new float[size * 3];  
}
template<typename D>
void safeglCreateVertexAttribArray(VaBuf<spectrum<D>> &id, GLuint size)
{
    id.ptr = new float[size * 3]; 
}

template<typename D>
void safeglCreateVertexAttribArray(VaBuf<mreal<D>> &id, GLuint size)
{
    id.ptr = new float[size]; 
}

template<>
inline void safeglCreateVertexAttribArray(VaBuf<real> &id, GLuint size)
{
    id.ptr = new float[size]; 
}

template<typename T>
void safeglDeleteVertexAttribArray(VaBuf<T> &id)
{
    if(id.ptr)
        delete [] id.ptr;
    id.ptr = 0;
}

template<typename T>
void safeglSetVertexAttribArray(VaBuf<T> &id, GLuint idx, const T &v);
template<typename S>
void safeglSetVertexAttribArray(VaBuf<point<S>> &id, GLuint idx, const point<S> &v)
{
    float *f = static_cast<float*>(id.ptr);
    f[idx * 3 + 0] = GLfloat(__asreal(v.x));
    f[idx * 3 + 1] = GLfloat(__asreal(v.y));
    f[idx * 3 + 2] = GLfloat(__asreal(v.z));
}

template<typename S>
void safeglSetVertexAttribArray(VaBuf<direction<S>> &id, GLuint idx, const direction<S> &v)
{
    float *f = static_cast<float*>(id.ptr);
    f[idx * 3 + 0] = GLfloat(v.x);
    f[idx * 3 + 1] = GLfloat(v.y);
    f[idx * 3 + 2] = GLfloat(v.z);
}

template<typename S>
void safeglSetVertexAttribArray(VaBuf<normal<S>> &id, GLuint idx, const normal<S> &v)
{
    float *f = static_cast<float*>(id.ptr);
    f[idx * 3 + 0] = GLfloat(v.x);
    f[idx * 3 + 1] = GLfloat(v.y);
    f[idx * 3 + 2] = GLfloat(v.z);
}

template<typename D>
void safeglSetVertexAttribArray(VaBuf<spectrum<D>> &id, GLuint idx, const spectrum<D> &v)
{
    float *f = static_cast<float*>(id.ptr);
    f[idx * 3 + 0] = GLfloat(__asreal(v.r));
    f[idx * 3 + 1] = GLfloat(__asreal(v.g));
    f[idx * 3 + 2] = GLfloat(__asreal(v.b));
}
template<typename D>
void safeglSetVertexAttribArray(VaBuf<mreal<D>> &id, GLuint idx, const mreal<D> v)
{
    float *f = static_cast<float*>(id.ptr);
    f[idx] = GLfloat(__asreal(v));
}

template<typename T>
T safeglGetVertexAttribArray(VaBuf<T> &id, GLuint idx);
template<typename S>
point<S> safeglGetVertexAttribArray(VaBuf<point<S>> &id, GLuint idx)
{
    float *f = static_cast<float*>(id.ptr);
    point<S> v(f[idx * 3 + 0], f[idx * 3 + 1], f[idx * 3 + 2]);
    return v;
}
template<typename S>
direction<S> safeglGetVertexAttribArray(VaBuf<direction<S>> &id, GLuint idx)
{
    float *f = static_cast<float*>(id.ptr);
    direction<S> v(f[idx * 3 + 0], f[idx * 3 + 1], f[idx * 3 + 2]);
    return v;
}
template<typename S>
normal<S> safeglGetVertexAttribArray(VaBuf<normal<S>> &id, GLuint idx)
{
    float *f = static_cast<float*>(id.ptr);
    normal<S> v(f[idx * 3 + 0], f[idx * 3 + 1], f[idx * 3 + 2]);
    return v;
}
template<typename D>
spectrum<D> safeglGetVertexAttribArray(VaBuf<spectrum<D>> &id, GLuint idx)
{
    float *f = static_cast<float*>(id.ptr);
    spectrum<D> v(f[idx * 3 + 0], f[idx * 3 + 1], f[idx * 3 + 2]);
    return v;
}
template<typename D>
mreal<D> safeglGetVertexAttribArray(VaBuf<mreal<D>> &id, GLuint idx)
{
    float *f = static_cast<float*>(id.ptr);
    return mreal<D>(f[idx]);
}

template<typename T>
inline void safeglVertexAttribPointer(Aid<T> aid, GLboolean normalized, GLsizei stride , const VaBuf<T> &VaBuf);


template<typename S>
inline void safeglVertexAttribPointer(Aid<point<S>> aid, GLboolean normalized, GLsizei stride , const VaBuf<point<S>> &VaBuf)
{
    glVertexAttribPointer(aid.v, 3, GL_FLOAT, normalized, stride, VaBuf.ptr);
}

template<typename S>
inline void safeglVertexAttribPointer(Aid<direction<S>> aid, GLboolean normalized, GLsizei stride , const VaBuf<direction<S>> &VaBuf)
{
    glVertexAttribPointer(aid.v, 3, GL_FLOAT, normalized, stride, VaBuf.ptr);
}

template<typename S>
inline void safeglVertexAttribPointer(Aid<normal<S>> aid, GLboolean normalized, GLsizei stride , const VaBuf<normal<S>> &VaBuf)
{
    glVertexAttribPointer(aid.v, 3, GL_FLOAT, normalized, stride, VaBuf.ptr);
}

template<typename D>
inline void safeglVertexAttribPointer(Aid<spectrum<D>> aid, GLboolean normalized, GLsizei stride , const VaBuf<spectrum<D>> &VaBuf)
{
    glVertexAttribPointer(aid.v, 3, GL_FLOAT, normalized, stride, VaBuf.ptr);
}

template<>
inline void safeglVertexAttribPointer(Aid<real> aid, GLboolean normalized, GLsizei stride , const VaBuf<real> &VaBuf)
{
    glVertexAttribPointer(aid.v, 1, GL_FLOAT, normalized, stride, VaBuf.ptr);
}

template<typename D>
inline void safeglVertexAttribPointer(Aid<mreal<D>> aid, GLboolean normalized, GLsizei stride , const VaBuf<mreal<D>> &VaBuf)
{
    glVertexAttribPointer(aid.v, 1, GL_FLOAT, normalized, stride, VaBuf.ptr);
}

#define safeglEnableClientState glEnableClientState
#define safeglDisableClientState glDisableClientState
#define safeglDrawArrays glDrawArrays

#endif //_SAFE_GL_H_
