#ifndef _UNSAFE_GL_H_
#define _UNSAFE_GL_H_

#include "common.h"

#include <string>
using std::string;

#ifdef WIN32_
#include <GL/glew.h>
#include <GL/wglew.h>
#else
#include <GL/glew.h>
#endif

#include <assert.h>

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

#define safeglCreateShader  glCreateShader
#define safeglCreateProgram glCreateProgram
#define safeglUseProgram    glUseProgram
#define safeglShaderSource  glShaderSource
#define safeglCompileShader glCompileShader
#define safeglAttachShader  glAttachShader
#define safeglLinkProgram   glLinkProgram
#define safeglDetachShader  glDetachShader
#define safeglDeleteShader  glDeleteShader
#define safeglDeleteProgram glDeleteProgram

struct TexId
{
    GLuint id;
};

inline void safeglCreateTexture2D(TexId &s, GLenum target,  GLint internalFormat, GLint level, 
    GLsizei width, GLsizei height, GLint border, const void* data)
{
    glGenTextures(1, &s.id);
    glBindTexture(GL_TEXTURE_2D, s.id);
    if (internalFormat == GL_DEPTH_COMPONENT32)
        glTexImage2D( GL_TEXTURE_2D, level, GL_DEPTH_COMPONENT32, width, height, border, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, data);
    else
        glTexImage2D( GL_TEXTURE_2D, level, GL_RGB32F, width, height, border, GL_RGBA, GL_FLOAT, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );
    glBindTexture(GL_TEXTURE_2D, 0);
}


inline void safeglDeleteTexture(TexId &s)
{
    glDeleteRenderbuffers(1, &s.id);
}


struct FboId
{
    GLuint id;
};

inline void safeglGenFramebuffer(FboId *framebuffers)
{
    glGenFramebuffers(1, &(framebuffers->id));
}

inline void safeglDeleteFramebuffer(FboId *framebuffers)
{
    glDeleteFramebuffers(1, &(framebuffers->id));
}

inline void safeglBindFramebuffer(FboId *framebuffers)
{
    glBindFramebuffer(GL_FRAMEBUFFER_EXT, framebuffers->id);
}

inline void safeglUnbindFramebuffer()
{
    glBindFramebuffer(GL_FRAMEBUFFER_EXT, 0);
}

inline void safeglFramebufferDepthTexture2D(FboId *framebuffers, TexId texture)
{
    glFramebufferTexture2D(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT,GL_TEXTURE_2D, texture.id, 0);
}


inline void safeglFramebufferColorTexture2D(FboId *framebuffers, TexId texture1)
{
    glFramebufferTexture2D(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT,GL_TEXTURE_2D, texture1.id, 0);
}

inline void safeglFramebufferColorTexture2D(FboId *framebuffers, TexId texture1, TexId texture2)
{
    safeglFramebufferColorTexture2D(framebuffers, texture1);
    glFramebufferTexture2D(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT1_EXT,GL_TEXTURE_2D, texture2.id, 0);
}

inline void safeglFramebufferColorAndDepthTexture2D(FboId *framebuffers, TexId texture1, TexId texture2, TexId texture3)
{
    safeglFramebufferColorTexture2D(framebuffers, texture1, texture2);
    glFramebufferTexture2D(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT,GL_TEXTURE_2D, texture3.id, 0);
}

struct Lid {  Lid() : v(-1) {} GLint v; };

inline Lid safeglGetUniformLocation(GLuint program, const GLchar *name)
{
    Lid l;
    l.v = glGetUniformLocation(program, name);;
    return l;
};

template<typename T>
inline void safeglUniform(Lid lid, const T &o);

template<>
inline void safeglUniform(Lid lid, const real &o)
{
    glUniform1f(lid.v, GLfloat(o));
}

template<>
inline void safeglUniform(Lid lid, const point &o)
{
    glUniform3f(lid.v, GLfloat(o.x), GLfloat(o.y), GLfloat(o.z));
}

template<>
inline void safeglUniform(Lid lid, const direction &o)
{
    glUniform3f(lid.v, GLfloat(o.x), GLfloat(o.y), GLfloat(o.z));
}

template<>
inline void safeglUniform(Lid lid, const normal &o)
{
    glUniform3f(lid.v, GLfloat(o.x), GLfloat(o.y), GLfloat(o.z));
}

template<>
inline void safeglUniform(Lid lid, const spectrum &o)
{
    glUniform3f(lid.v, GLfloat(o.r), GLfloat(o.g), GLfloat(o.b));
}

void _lineup_mat(const mat4& mat, float *f);

template<>
inline void safeglUniform(Lid lid, const rigidmap &o)
{
    static float lm[32];
    __lineup_mat(o.m, lm);
    __lineup_mat(o.mi, lm+16);
    glUniformMatrix4fv(lid.v, 2, true, lm);
}

template<>
inline void safeglUniform(Lid lid, const projmap &o)
{
    static float lm[32];
    __lineup_mat(o.m, lm);
    __lineup_mat(o.mi, lm+16);
    glUniformMatrix4fv(lid.v, 2, true, lm);
}

inline void safeglUniform(Lid lid, const TexId &o, GLuint i)
{
    glActiveTexture(GL_TEXTURE0 + i);
    glBindTexture(GL_TEXTURE_2D, o.id);
    glUniform1i(lid.v, i);
}

struct Aid {  GLint v; };

inline Aid safeglGetAttribLocation(GLuint program, const GLchar *name)
{
    Aid a;
    a.v = glGetAttribLocation(program, name);
    return a;
};

inline void safeglVertexAttrib(Aid aid, const real &o)
{
    glVertexAttrib1f(aid.v, GLfloat(o));
}

inline void safeglVertexAttrib(Aid aid, const point &o)
{
    glVertexAttrib3f(aid.v, GLfloat(o.x), GLfloat(o.y), GLfloat(o.z));
}

inline void safeglVertexAttrib(Aid aid, const direction &o)
{
    glVertexAttrib3f(aid.v, GLfloat(o.x), GLfloat(o.y), GLfloat(o.z));
}

inline void safeglVertexAttrib(Aid aid, const normal &o)
{
    glVertexAttrib3f(aid.v, GLfloat(o.x), GLfloat(o.y), GLfloat(o.z));
}

inline void safeglVertexAttrib(Aid aid, const spectrum &o)
{
    glVertexAttrib3f(aid.v, GLfloat(o.r), GLfloat(o.g), GLfloat(o.b));
}

inline void safeglEnableVertexAttribArray(Aid aid)
{
    glEnableVertexAttribArray(aid.v);
}

inline void safeglDisableVertexAttribArray(Aid aid)
{
    glDisableVertexAttribArray(aid.v);
}

inline void safeglVertex(const point& p)
{
    glVertex3f(GLfloat(__asreal(p.x)), GLfloat(__asreal(p.y)), GLfloat(__asreal(p.z)));
}

inline void safeglNormal(const direction& n)
{
    glNormal3f(GLfloat(n.x), GLfloat(n.y), GLfloat(n.z));
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
template<>
inline void safeglCreateVertexAttribArray(VaBuf<point> &id, GLuint size)
{
    id.ptr = new float[size * 3];
}
template<>
inline void safeglCreateVertexAttribArray(VaBuf<direction> &id, GLuint size)
{
    id.ptr = new float[size * 3];  
}
template<>
inline void safeglCreateVertexAttribArray(VaBuf<normal> &id, GLuint size)
{
    id.ptr = new float[size * 3];  
}
template<>
inline void safeglCreateVertexAttribArray(VaBuf<spectrum> &id, GLuint size)
{
    id.ptr = new float[size * 3]; 
}

template<>
inline void safeglCreateVertexAttribArray(VaBuf<real> &id, GLuint size)
{
    id.ptr = new float[size]; 
}

template<typename T>
inline void safeglDeleteVertexAttribArray(VaBuf<T> &id)
{
    if(id.ptr)
        delete [] id.ptr;
    id.ptr = 0;
}


inline void safeglSetVertexAttribArray(VaBuf<point> &id, GLuint idx, const point &v)
{
    float *f = static_cast<float*>(id.ptr);
    f[idx * 3 + 0] = GLfloat(__asreal(v.x));
    f[idx * 3 + 1] = GLfloat(__asreal(v.y));
    f[idx * 3 + 2] = GLfloat(__asreal(v.z));
}

inline void safeglSetVertexAttribArray(VaBuf<direction> &id, GLuint idx, const direction &v)
{
    float *f = static_cast<float*>(id.ptr);
    f[idx * 3 + 0] = GLfloat(v.x);
    f[idx * 3 + 1] = GLfloat(v.y);
    f[idx * 3 + 2] = GLfloat(v.z);
}

inline void safeglSetVertexAttribArray(VaBuf<normal> &id, GLuint idx, const normal &v)
{
    float *f = static_cast<float*>(id.ptr);
    f[idx * 3 + 0] = GLfloat(v.x);
    f[idx * 3 + 1] = GLfloat(v.y);
    f[idx * 3 + 2] = GLfloat(v.z);
}

inline void safeglSetVertexAttribArray(VaBuf<spectrum> &id, GLuint idx, const spectrum &v)
{
    float *f = static_cast<float*>(id.ptr);
    f[idx * 3 + 0] = GLfloat(__asreal(v.r));
    f[idx * 3 + 1] = GLfloat(__asreal(v.g));
    f[idx * 3 + 2] = GLfloat(__asreal(v.b));
}

inline void safeglSetVertexAttribArray(VaBuf<real> &id, GLuint idx, const real v)
{
    float *f = static_cast<float*>(id.ptr);
    f[idx] = GLfloat(v);
}


inline point safeglGetVertexAttribArray(VaBuf<point> &id, GLuint idx)
{
    float *f = static_cast<float*>(id.ptr);
    point v(f[idx * 3 + 0], f[idx * 3 + 1], f[idx * 3 + 2]);
    return v;
}

inline direction safeglGetVertexAttribArray(VaBuf<direction> &id, GLuint idx)
{
    float *f = static_cast<float*>(id.ptr);
    direction v(f[idx * 3 + 0], f[idx * 3 + 1], f[idx * 3 + 2]);
    return v;
}

inline normal safeglGetVertexAttribArray(VaBuf<normal> &id, GLuint idx)
{
    float *f = static_cast<float*>(id.ptr);
    normal v(f[idx * 3 + 0], f[idx * 3 + 1], f[idx * 3 + 2]);
    return v;
}

inline spectrum safeglGetVertexAttribArray(VaBuf<spectrum> &id, GLuint idx)
{
    float *f = static_cast<float*>(id.ptr);
    spectrum v(f[idx * 3 + 0], f[idx * 3 + 1], f[idx * 3 + 2]);
    return v;
}

inline real safeglGetVertexAttribArray(VaBuf<real> &id, GLuint idx)
{
    float *f = static_cast<float*>(id.ptr);
    return f[idx];
}

template<typename T>
inline void safeglVertexAttribPointer(Aid aid, GLboolean normalized, GLsizei stride , const VaBuf<T> &VaBuf);

template<>
inline void safeglVertexAttribPointer(Aid aid, GLboolean normalized, GLsizei stride , const VaBuf<point> &VaBuf)
{
    glVertexAttribPointer(aid.v, 3, GL_FLOAT, normalized, stride, VaBuf.ptr);
}

template<>
inline void safeglVertexAttribPointer(Aid aid, GLboolean normalized, GLsizei stride , const VaBuf<direction> &VaBuf)
{
    glVertexAttribPointer(aid.v, 3, GL_FLOAT, normalized, stride, VaBuf.ptr);
}

template<>
inline void safeglVertexAttribPointer(Aid aid, GLboolean normalized, GLsizei stride , const VaBuf<normal> &VaBuf)
{
    glVertexAttribPointer(aid.v, 3, GL_FLOAT, normalized, stride, VaBuf.ptr);
}

template<>
inline void safeglVertexAttribPointer(Aid aid, GLboolean normalized, GLsizei stride , const VaBuf<spectrum> &VaBuf)
{
    glVertexAttribPointer(aid.v, 3, GL_FLOAT, normalized, stride, VaBuf.ptr);
}

template<>
inline void safeglVertexAttribPointer(Aid aid, GLboolean normalized, GLsizei stride , const VaBuf<real> &VaBuf)
{
    glVertexAttribPointer(aid.v, 1, GL_FLOAT, normalized, stride, VaBuf.ptr);
}

#define safeglEnableClientState glEnableClientState
#define safeglDisableClientState glDisableClientState
#define safeglDrawArrays glDrawArrays

#endif //_UNSAFE_GL_H_
