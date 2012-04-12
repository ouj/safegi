#ifndef _OPENGL_SCENE_H_
#define _OPENGL_SCENE_H_

#ifdef WIN32
#include <GL/glew.h>
#include <GL/wglew.h>
#else
#include <GL/glew.h>
#endif

#define USE_SAFE_GL
#include <tsafegi/safe_gl.h>
#include <tsafegi/tracer.h>

#ifdef _WIN32
#include <memory>
#else
#include <tr1/memory>
#endif

using std::tr1::shared_ptr;

struct Surface;
struct Scene;

class gl_renderer
{
public:
    gl_renderer();
    ~gl_renderer(void);

    bool init();
    image<spectrum<radiance_d>> render_scene(shared_ptr<Scene> scene, const mreal<time_d>& t0, 
        const mreal<time_d>& t1, unsigned int samples = 512);
protected:
    void _setup_shaders();
    void _setup_shadow_map();

    void _cleanup();
    void _blendImage();
    void _render_shadow_buffer(unsigned int sm_dir, rigidmap<world_s, source_s> &lXf, const mreal<time_d>& t);
    void _render_scene_point(point<world_s> &light_pos, const spectrum<intensity_d> &intensity, 
        const int samples, const mreal<time_d>& t);
    void _render_scene_area(const point<world_s> &light_pos, const normal<world_s> light_norm, 
    const spectrum<radiance_d> &le, const mreal<area_d> area, const int samples, const mreal<time_d>& t);
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

    rigidmap<source_s, source_s>            sm_rot_rigidmap[6];
    depth_only_fbo_id                       fboId;
    TexId<mreal<length_d>>                  shadowMapId[6];
    color_depth_fbo_id                      targetFboId;
    TexId<spectrum<radiance_d>>             targetTexId;
    TexId<mreal<length_d>>                  targetDepthTexId;
    color_depth_fbo_id                      blendFboId;
    TexId<spectrum<radiance_d>>             blendTexId;

    Lid<rigidmap<world_s, source_s>>        sm_lXf_lid;
    Lid<projmap<source_s, clip_s>>          sm_lpXf_lid;
    Lid<rigidmap<shape_s, world_s>>         sm_mXf_lid;
	Aid<point<shape_s>>						sm_lp_aid;
	Aid<normal<shape_s>>					sm_n_aid;

    Lid<point<world_s>>                     pl_ep_lid;
    Lid<rigidmap<world_s, lens_s>>          pl_vXf_lid;
    Lid<projmap<lens_s, clip_s>>            pl_pXf_lid;
    Lid<point<world_s>>                     pl_lp_lid;
    Lid<spectrum<intensity_d>>              pl_inten_lid;
    Lid<projmap<source_s, clip_s>>          pl_lpXf_lid;
    Lid<rigidmap<shape_s, world_s>>         pl_mXf_lid;
    Lid<rigidmap<world_s, source_s>>        pl_lXf_lid[6];
    Lid<TexId<mreal<length_d>>>             pl_sm_lid[6];
	Lid<spectrum<rho_d>>					pl_rhod_lid;
	Lid<spectrum<rho_d>>					pl_rhos_lid;
	Lid<real> 								pl_n_lid;
    Lid<real>                               pl_invsamples_lid;
	Aid<point<shape_s>>						pl_lp_aid;
	Aid<normal<shape_s>>					pl_n_aid;

    Lid<point<world_s>>                     ar_ep_lid;
    Lid<rigidmap<world_s, lens_s>>          ar_vXf_lid;
    Lid<projmap<lens_s, clip_s>>            ar_pXf_lid;
    Lid<point<world_s>>                     ar_lp_lid;
    Lid<spectrum<intensity_d>>              ar_inten_lid;
    Lid<projmap<source_s, clip_s>>          ar_lpXf_lid;
    Lid<rigidmap<shape_s, world_s>>         ar_mXf_lid;
    Lid<rigidmap<world_s, source_s>>        ar_lXf_lid[6];
    Lid<TexId<mreal<length_d>>>             ar_sm_lid[6];
    Lid<spectrum<radiance_d>>               ar_le_lid;
    Lid<mreal<area_d>>                      ar_sa_lid;
    Lid<direction<world_s>>                 ar_ln_lid;
	Lid<spectrum<rho_d>>					ar_rhod_lid;
	Lid<spectrum<rho_d>>					ar_rhos_lid;
	Lid<real> 								ar_n_lid;
    Lid<real>                               ar_invsamples_lid;
	Aid<point<shape_s>>						ar_lp_aid;
	Aid<normal<shape_s>>					ar_n_aid;
};
#endif // _OPENGL_SCENE_H_
