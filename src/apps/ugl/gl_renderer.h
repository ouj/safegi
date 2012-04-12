#ifndef _OPENGL_SCENE_H_
#define _OPENGL_SCENE_H_
#ifdef WIN32_
#include <GL/glew.h>
#include <GL/wglew.h>
#else
#include <GL/glew.h>
#endif
#define USE_SAFE_GL
#include <usafegi/safe_gl.h>
#include <usafegi/tracer.h>
using std::tr1::shared_ptr;

struct Surface;
struct Scene;

class gl_renderer
{
public:
    gl_renderer();
    ~gl_renderer(void);

    bool init();
    image<spectrum> render_scene(shared_ptr<Scene> scene, const real& t0, 
        const real& t1, unsigned int samples = 512);
protected:
    void _setup_shaders();
    void _setup_shadow_map();

    void _cleanup();
    void _blendImage();
    void _render_shadow_buffer(unsigned int sm_dir, rigidmap &lXf, const real &t);
    void _render_scene_point(point &light_pos, const spectrum &intensity, 
        const int samples, const real &t);
    void _render_scene_area(const point &light_pos, const normal light_norm, 
    const spectrum &le, const real area, const int sample, const real &t);
protected:
    shared_ptr<Scene>   _scene;

    GLuint              shadowmap_vs;
    GLuint              shadowmap_fs;

    GLuint              image_vs;
    GLuint              pointlight_fs;
    GLuint              arealight_fs;

    GLuint              shadowmap_program;
    GLuint              pointlight_program;
    GLuint              arealight_program;

    rigidmap                                sm_rot_rigidmap[6];
    FboId                                   fboId;
    TexId                                   shadowMapId[6];
    FboId                                   targetFboId;
    TexId                                   targetTexId;
    TexId                                   targetDepthTexId;
    FboId                                   blendFboId;
    TexId                                   blendTexId;

    Lid                                     sm_lXf_lid;
    Lid                                     sm_lpXf_lid;
    Lid                                     sm_mXf_lid;
	Aid										sm_lp_aid;
	Aid										sm_n_aid;

    Lid                                     pl_ep_lid;
    Lid                                     pl_vXf_lid;
    Lid                                     pl_pXf_lid;
    Lid                                     pl_lp_lid;
    Lid                                     pl_inten_lid;
    Lid                                     pl_lpXf_lid;
    Lid                                     pl_mXf_lid;
    Lid                                     pl_lXf_lid[6];
    Lid                                     pl_sm_lid[6];
	Lid										pl_rhod_lid;
	Lid  				                    pl_rhos_lid;
	Lid     								pl_n_lid;
    Lid                                     pl_invsamples_lid;
	Aid                     				pl_lp_aid;
	Aid                     				pl_n_aid;

    Lid                                     ar_ep_lid;
    Lid                                     ar_vXf_lid;
    Lid                                     ar_pXf_lid;
    Lid                                     ar_lp_lid;
    Lid                                     ar_inten_lid;
    Lid                                     ar_lpXf_lid;
    Lid                                     ar_mXf_lid;
    Lid                                     ar_lXf_lid[6];
    Lid                                     ar_sm_lid[6];
    Lid                                     ar_le_lid;
    Lid                                     ar_sa_lid;
    Lid                                     ar_ln_lid;
	Lid                     				ar_rhod_lid;
	Lid                 					ar_rhos_lid;
	Lid         							ar_n_lid;
    Lid                                     ar_invsamples_lid;
	Aid                     				ar_lp_aid;
	Aid                     				ar_n_aid;
};
#endif // _OPENGL_SCENE_H_
