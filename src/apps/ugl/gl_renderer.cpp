#define USE_SAFE_GL
#include <usafegi/scene.h>
#include <usafegi/mesh.h>
#include "gl_renderer.h"

#include "shader_src.h"
#define _USE_MATH_DEFINES
#include "math.h"

#define SHADOW_MAP_WIDTH    2048
#define SHADOW_MAP_HEIGHT   2048

#define IMAGE_WIDTH         512
#define IMAGE_HEIGHT        512

#define SHADOW_MAP_DOV      45

gl_renderer::gl_renderer()
{
}

bool gl_renderer::init()
{
#ifndef __APPLE__
    glewInit();
#endif
    glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);

    sm_rot_rigidmap[0] = rotate(direction(1.0, 0.0, 0.0), toRadians(0));
    sm_rot_rigidmap[1] = rotate(direction(1.0, 0.0, 0.0), toRadians(180));
    sm_rot_rigidmap[2] = rotate(direction(1.0, 0.0, 0.0), toRadians(-90));
    sm_rot_rigidmap[3] = rotate(direction(1.0, 0.0, 0.0), toRadians(90));
    sm_rot_rigidmap[4] = rotate(direction(0.0, 1.0, 0.0), toRadians(90));
    sm_rot_rigidmap[5] = rotate(direction(0.0, 1.0, 0.0), toRadians(-90));

    _setup_shadow_map();
    _setup_shaders();

    return true;
}

void gl_renderer::_cleanup()
{
    // cleanup shaders
    safeglDetachShader(shadowmap_program, shadowmap_vs);
    safeglDetachShader(shadowmap_program, shadowmap_fs);
    safeglDetachShader(shadowmap_program, image_vs);
    safeglDetachShader(shadowmap_program, pointlight_fs);

    safeglDeleteShader(shadowmap_vs);
    safeglDeleteShader(image_vs);

    safeglDeleteShader(shadowmap_fs);
    safeglDeleteShader(pointlight_fs);

    safeglDeleteProgram(shadowmap_program);
    safeglDeleteProgram(arealight_program);
    safeglDeleteProgram(pointlight_program);

    for(unsigned i = 0; i < 6; i++)
    {
        glDeleteRenderbuffersEXT(1, &shadowMapId[i].id);
    }
    safeglDeleteFramebuffer(&fboId);
}

mat4 compute_project_matrix(real xfov, real yfov, real n, real f)
{
    mat4 m;

    real l = -n * tan(xfov);
    real r = n * tan(xfov);
    real t = n * tan(yfov);
    real b = -n * tan(yfov);

    m.d[0][0] = 2 * n / (r - l);
    m.d[0][2] = (r + l) / (l - r);
    m.d[1][1] = 2 * n / (t - b);
    m.d[1][2] = (t + b) / (t - b);
    m.d[2][2] = (n + f) / (n - f);
    m.d[2][3] = 2.0 * f * n / (n - f);
    m.d[3][2] = -1.0;
    m.d[3][3] = 0.0;

    return m;
}


projmap get_projection(real xfov, real yfov, real n, real f)
{
    projmap rm;
    rm.m = compute_project_matrix(xfov, yfov, n, f);
    return rm;
}


void gl_renderer::_setup_shadow_map()
{
    GLenum FBOstatus;
    safeglGenFramebuffer(&fboId);
    safeglBindFramebuffer(&fboId);

    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);

    for(unsigned int i = 0; i < 6; i++)
    {
        safeglCreateTexture2D(shadowMapId[i], GL_TEXTURE_2D, GL_DEPTH_COMPONENT32, 0, SHADOW_MAP_WIDTH, SHADOW_MAP_HEIGHT, 0, NULL);
        safeglFramebufferDepthTexture2D(&fboId, shadowMapId[i]);

        FBOstatus = glCheckFramebufferStatus(GL_FRAMEBUFFER_EXT);
        if(FBOstatus != GL_FRAMEBUFFER_COMPLETE_EXT)
            printf("GL_FRAMEBUFFER_COMPLETE_EXT failed, CANNOT use FBO\n");
    }

    safeglUnbindFramebuffer();

    safeglGenFramebuffer(&targetFboId);
    safeglBindFramebuffer(&targetFboId);

    safeglCreateTexture2D(targetTexId, GL_TEXTURE_2D, GL_RGB32F, 0, IMAGE_WIDTH, IMAGE_HEIGHT, 0, NULL);
    safeglFramebufferColorTexture2D(&targetFboId, targetTexId);

    safeglCreateTexture2D(targetDepthTexId, GL_TEXTURE_2D, GL_DEPTH_COMPONENT32, 0, IMAGE_WIDTH, IMAGE_HEIGHT, 0, NULL);
    safeglFramebufferDepthTexture2D(&targetFboId, targetDepthTexId);

    FBOstatus = glCheckFramebufferStatus(GL_FRAMEBUFFER_EXT);
    if(FBOstatus != GL_FRAMEBUFFER_COMPLETE_EXT)
        printf("GL_FRAMEBUFFER_COMPLETE_EXT failed, CANNOT use FBO\n");

    safeglGenFramebuffer(&blendFboId);
    safeglBindFramebuffer(&blendFboId);

    safeglCreateTexture2D(blendTexId, GL_TEXTURE_2D, GL_RGB32F, 0, IMAGE_WIDTH, IMAGE_HEIGHT, 0, NULL);
    safeglFramebufferColorTexture2D(&blendFboId, blendTexId);

    FBOstatus = glCheckFramebufferStatus(GL_FRAMEBUFFER_EXT);
    if(FBOstatus != GL_FRAMEBUFFER_COMPLETE_EXT)
        printf("GL_FRAMEBUFFER_COMPLETE_EXT failed, CANNOT use FBO\n");

    safeglUnbindFramebuffer();
}

void gl_renderer::_render_shadow_buffer(unsigned int sm_dir, rigidmap &lXf, const real &t)
{
    safeglFramebufferDepthTexture2D(&fboId, shadowMapId[sm_dir]);

    GLenum FBOstatus = glCheckFramebufferStatus(GL_FRAMEBUFFER_EXT);
    if(FBOstatus != GL_FRAMEBUFFER_COMPLETE_EXT)
        printf("GL_FRAMEBUFFER_COMPLETE_EXT failed, CANNOT use FBO\n");
    glClear(GL_DEPTH_BUFFER_BIT);

    safeglUseProgram(shadowmap_program);
    auto lpXf = get_projection(toRadians(SHADOW_MAP_DOV), toRadians(SHADOW_MAP_DOV), 1.0, 100);
    safeglUniform(sm_lXf_lid, lXf);
    safeglUniform(sm_lpXf_lid, lpXf);

    for(unsigned int idx = 0; idx <  _scene->surfaces.size(); idx++)
    {
        shared_ptr<Surface> &surface = _scene->surfaces[idx];
        auto mXf = surface->xform->sample(t);
        safeglUniform(sm_mXf_lid, mXf);
        surface->shape->gl_draw(sm_lp_aid, sm_n_aid);
    }
    safeglUseProgram(0);
}

void gl_renderer::_setup_shaders()
{
    shadowmap_vs = safeglCreateShader(GL_VERTEX_SHADER_ARB);
    shadowmap_fs = safeglCreateShader(GL_FRAGMENT_SHADER_ARB);

    const GLcharARB* shadowmap_vs_src = get_shader(SHADOW_MAP_VS_SOURCE);
    const GLcharARB* shadowmap_fs_src = get_shader(SHADOW_MAP_FS_SOURCE);

    safeglShaderSource(shadowmap_vs, 1, &shadowmap_vs_src, 0);
    safeglShaderSource(shadowmap_fs, 1, &shadowmap_fs_src, 0);
    safeglCompileShader(shadowmap_vs);
    safeglCompileShader(shadowmap_fs);

    shadowmap_program = safeglCreateProgram();
    safeglAttachShader(shadowmap_program, shadowmap_vs);
    safeglAttachShader(shadowmap_program, shadowmap_fs);
    safeglLinkProgram(shadowmap_program);

    image_vs = safeglCreateShader(GL_VERTEX_SHADER_ARB);
    pointlight_fs = safeglCreateShader(GL_FRAGMENT_SHADER_ARB);

    const GLcharARB* image_vs_src = get_shader(IMAGE_VS_SOURCE);
    const GLcharARB* pointlight_fs_src = get_shader(POINTLIGHT_FS_SOURCE);

    safeglShaderSource(image_vs, 1, &image_vs_src, 0);
    safeglShaderSource(pointlight_fs, 1, &pointlight_fs_src, 0);
    safeglCompileShader(image_vs);
    safeglCompileShader(pointlight_fs);

    pointlight_program = safeglCreateProgram();
    safeglAttachShader(pointlight_program, image_vs);
    safeglAttachShader(pointlight_program, pointlight_fs);
    safeglLinkProgram(pointlight_program);

    arealight_fs = safeglCreateShader(GL_FRAGMENT_SHADER_ARB);
    const GLcharARB* arealigh_fs_src = get_shader(AREALIGHT_FS_SOURCE);

    safeglShaderSource(arealight_fs, 1, &arealigh_fs_src, 0);
    safeglCompileShader(arealight_fs);

    arealight_program = safeglCreateProgram();
    safeglAttachShader(arealight_program, image_vs);
    safeglAttachShader(arealight_program, arealight_fs);
    safeglLinkProgram(arealight_program);

    sm_lXf_lid = safeglGetUniformLocation(shadowmap_program, "lXf"); 
    sm_lpXf_lid = safeglGetUniformLocation(shadowmap_program, "lpXf"); 
    sm_mXf_lid = safeglGetUniformLocation(shadowmap_program, "mXf"); 
    sm_lp_aid = safeglGetAttribLocation(shadowmap_program, "local_point");
    sm_n_aid = safeglGetAttribLocation(shadowmap_program, "local_normal");

    pl_ep_lid = safeglGetUniformLocation(pointlight_program, "eye_pos");
    pl_vXf_lid = safeglGetUniformLocation(pointlight_program, "vXf");
    pl_pXf_lid = safeglGetUniformLocation(pointlight_program, "pXf");
    pl_lp_lid = safeglGetUniformLocation(pointlight_program, "light_pos");
    pl_inten_lid = safeglGetUniformLocation(pointlight_program, "intensity");
    pl_lpXf_lid = safeglGetUniformLocation(pointlight_program, "lpXf");
    pl_mXf_lid = safeglGetUniformLocation(pointlight_program, "mXf"); 
    for(unsigned int i = 0;i < 6; i++)
    {
        string lXf_name = "lXf";
        string sampler_name = "shadow_map";
        lXf_name += ('0'+i);
        sampler_name += ('0'+i);
        pl_lXf_lid[i] = safeglGetUniformLocation(pointlight_program, lXf_name.c_str());
        pl_sm_lid[i] = safeglGetUniformLocation(pointlight_program, sampler_name.c_str());
    }
    pl_rhod_lid = safeglGetUniformLocation(pointlight_program, "rhod");
	pl_rhos_lid = safeglGetUniformLocation(pointlight_program, "rhos");
    pl_n_lid = safeglGetUniformLocation(pointlight_program, "n");
    pl_invsamples_lid = safeglGetUniformLocation(pointlight_program, "invsamples");
	pl_lp_aid = safeglGetAttribLocation(pointlight_program, "local_point");
    pl_n_aid = safeglGetAttribLocation(pointlight_program, "local_normal");

    ar_ep_lid = safeglGetUniformLocation(arealight_program, "eye_pos");
    ar_vXf_lid = safeglGetUniformLocation(arealight_program, "vXf");
    ar_pXf_lid = safeglGetUniformLocation(arealight_program, "pXf");
    ar_lp_lid = safeglGetUniformLocation(arealight_program, "light_pos");
    ar_inten_lid = safeglGetUniformLocation(arealight_program, "intensity");
    ar_lpXf_lid = safeglGetUniformLocation(arealight_program, "lpXf");
    ar_mXf_lid = safeglGetUniformLocation(arealight_program, "mXf"); 
    for(unsigned int i = 0;i < 6; i++)
    {
        string lXf_name = "lXf";
        string sampler_name = "shadow_map";
        lXf_name += ('0'+i);
        sampler_name += ('0'+i);
        ar_lXf_lid[i] = safeglGetUniformLocation(arealight_program, lXf_name.c_str());
        ar_sm_lid[i] = safeglGetUniformLocation(arealight_program, sampler_name.c_str());
    }
    
    ar_le_lid = safeglGetUniformLocation(arealight_program, "le");
    ar_sa_lid = safeglGetUniformLocation(arealight_program, "sa");
    ar_ln_lid = safeglGetUniformLocation(arealight_program, "ln");
    ar_invsamples_lid = safeglGetUniformLocation(arealight_program, "invsamples");

    ar_rhod_lid = safeglGetUniformLocation(arealight_program, "rhod");
	ar_rhos_lid = safeglGetUniformLocation(arealight_program, "rhos");
    ar_n_lid = safeglGetUniformLocation(arealight_program, "n");

	ar_lp_aid = safeglGetAttribLocation(arealight_program, "local_point");
    ar_n_aid = safeglGetAttribLocation(arealight_program, "local_normal");
}

void gl_renderer::_render_scene_point(point &light_pos, const spectrum &intensity, const int samples, const real &t)
{
    glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE); 
    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, SHADOW_MAP_WIDTH, SHADOW_MAP_HEIGHT);

    rigidmap lXf[6];
    rigidmap trans = translate(light_pos - point());
    safeglBindFramebuffer(&fboId);	//Rendering offscreen
    for(unsigned int i = 0; i < 6; i++)
    {
        lXf[i] =  invert(trans % sm_rot_rigidmap[i]);
        _render_shadow_buffer(i, lXf[i], t);
    }
    safeglUnbindFramebuffer();
    glViewport(0, 0, IMAGE_WIDTH, IMAGE_HEIGHT);
    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE); 
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    safeglUseProgram(pointlight_program);
    for(unsigned int i = 0;i < 6; i++)
    {
        safeglUniform(pl_sm_lid[i], shadowMapId[i], i);
        safeglUniform(pl_lXf_lid[i], lXf[i]);
    }
    rigidmap cXf = _scene->camera->xform->sample(t);
    rigidmap vXf = invert(cXf);
    projmap pXf = _scene->camera->lens->get_projection(1, 500);
    projmap lpXf = get_projection(toRadians(SHADOW_MAP_DOV), toRadians(SHADOW_MAP_DOV), 1.0, 1000);
    point eye_pos = transform(cXf, point());
    safeglUniform(pl_ep_lid, eye_pos); 
    safeglUniform(pl_vXf_lid, vXf);
    safeglUniform(pl_pXf_lid, pXf);
    safeglUniform(pl_lp_lid, light_pos); 
    safeglUniform(pl_inten_lid, intensity);
    safeglUniform(pl_lpXf_lid, lpXf);
    safeglUniform(pl_invsamples_lid, (1.0 / samples));
    safeglBindFramebuffer(&targetFboId);	//Rendering offscreen
    glDrawBuffer(GL_COLOR_ATTACHMENT0_EXT);
    glReadBuffer(GL_NONE);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    for(unsigned int idx = 0; idx <  _scene->surfaces.size(); idx++)
    {
        shared_ptr<Surface> &surface = _scene->surfaces[idx];
        rigidmap mXf = surface->xform->sample(t);
        safeglUniform(pl_mXf_lid, mXf);

		shared_ptr<Lambert> lambert = dynamic_pointer_cast<Lambert>(surface->material->brdf);
		if(lambert.get())
		{
			safeglUniform(pl_rhod_lid, lambert->rhod);
			safeglUniform(pl_rhos_lid, spectrum());
			safeglUniform(pl_n_lid, real(0));
		}
		shared_ptr<Phong> phong = dynamic_pointer_cast<Phong>(surface->material->brdf);
		if(phong.get())
		{
			safeglUniform(pl_rhod_lid, phong->rhod);
			safeglUniform(pl_rhos_lid, phong->rhos);
			safeglUniform(pl_n_lid, phong->n);
		}
		surface->shape->gl_draw(pl_lp_aid, pl_n_aid);
    }
    safeglUnbindFramebuffer();
    safeglUseProgram(0);
    return;
}

void gl_renderer::_render_scene_area(const point &light_pos, const normal light_norm, 
    const spectrum &le, const real area, const int samples, const real &t)
{
    glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE); 
    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, SHADOW_MAP_WIDTH, SHADOW_MAP_HEIGHT);

    rigidmap lXf[6];
    rigidmap trans = translate(light_pos - point());
    safeglBindFramebuffer(&fboId);	//Rendering offscreen
    for(unsigned int i = 0; i < 6; i++)
    {
        lXf[i] =  invert(trans % sm_rot_rigidmap[i]);
        _render_shadow_buffer(i, lXf[i], t);
    }
    safeglUnbindFramebuffer();

    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE); 
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    safeglUseProgram(arealight_program);
    for(int i = 0;i < 6; i++)
    {
        safeglUniform(ar_sm_lid[i], shadowMapId[i], i);
        safeglUniform(ar_lXf_lid[i], lXf[i]);
    }
    rigidmap cXf = _scene->camera->xform->sample(t);
    rigidmap vXf = invert(cXf);
    projmap pXf = _scene->camera->lens->get_projection(1, 100);
    projmap lpXf = get_projection(toRadians(SHADOW_MAP_DOV), toRadians(SHADOW_MAP_DOV), 1.0, 1000);
    point eye_pos = transform(cXf, point());
    safeglUniform(ar_ep_lid, eye_pos);
    safeglUniform(ar_vXf_lid, vXf);
    safeglUniform(ar_pXf_lid, pXf);
    safeglUniform(ar_lp_lid, light_pos);
    safeglUniform(ar_lpXf_lid, lpXf);
    safeglUniform(ar_le_lid, le);
    safeglUniform(ar_sa_lid, area);
    safeglUniform(ar_ln_lid, light_norm);
    safeglUniform(ar_invsamples_lid, (1.0 / samples));

    glViewport(0, 0, IMAGE_WIDTH, IMAGE_WIDTH);

    safeglBindFramebuffer(&targetFboId);	//Rendering offscreen
    glDrawBuffer(GL_COLOR_ATTACHMENT0_EXT);
    glReadBuffer(GL_NONE);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    for(unsigned int idx = 0; idx <  _scene->surfaces.size(); idx++)
    {
        shared_ptr<Surface> &surface = _scene->surfaces[idx];
        rigidmap mXf = surface->xform->sample(t);
        safeglUniform(ar_mXf_lid, mXf);

		auto em_lid = safeglGetUniformLocation(arealight_program, "em");
		safeglUniform(em_lid, ((surface->material->source.get()) ? le : spectrum()));

		shared_ptr<Lambert> lambert = dynamic_pointer_cast<Lambert>(surface->material->brdf);
		if(lambert.get())
		{
			safeglUniform(ar_rhod_lid, lambert->rhod);
			safeglUniform(ar_rhos_lid, spectrum());
			safeglUniform(ar_n_lid, real(0));
		}
		shared_ptr<Phong> phong = dynamic_pointer_cast<Phong>(surface->material->brdf);
		if(phong.get())
		{
			safeglUniform(ar_rhod_lid, phong->rhod);
			safeglUniform(ar_rhos_lid, phong->rhos);
			safeglUniform(ar_n_lid, phong->n);
		}
		surface->shape->gl_draw(ar_lp_aid, ar_n_aid);
    }
    safeglUnbindFramebuffer();
    safeglUseProgram(0);
    return;
}

image<spectrum> gl_renderer::render_scene(shared_ptr<Scene> scene, const real& t0, 
                                          const real& t1, unsigned int samples)
{
    _scene = scene; 
    safeglBindFramebuffer(&targetFboId);	//Rendering offscreen
    glDrawBuffer(GL_COLOR_ATTACHMENT0_EXT);
    glReadBuffer(GL_COLOR_ATTACHMENT0_EXT);
    glClearColor(0,0,0,0);
    glClearDepth(1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    for(unsigned int idx = 0; idx < _scene->lights.size(); idx++)
    {
        shared_ptr<Light> &light = _scene->lights[idx];
        shared_ptr<PointSource> ps = dynamic_pointer_cast<PointSource>(light->source);
        if(ps.get())
        {
            for(unsigned int i = 0; i < samples; i++)
            {
                auto t = t0 + (t1-t0)*urandom();
                auto ilXf = light->xform->sample(t);
                point light_pos = transform(ilXf, point());
                _render_scene_point(light_pos, ps->intensity, samples, t);
                _blendImage();
            }
        }
        shared_ptr<AreaSource> as = dynamic_pointer_cast<AreaSource>(light->source);
        if(as.get())
        {
            for(unsigned int i = 0; i < samples; i++)
            {
                auto t = t0 + (t1-t0)*urandom();
                auto s = as->shape->sample(tuple2(urandom(), urandom()));
                auto ss = shapeSample(point(s.p.x,s.p.y,s.p.z),normal(s.n.x,s.n.y,s.n.z),s.area);
                auto lmap = light->xform->sample(t);

                point point = transform(lmap, ss.p);
                normal norm = transform(lmap, ss.n);
                _render_scene_area(point, norm, as->le, ss.area, samples, t);
                _blendImage();
            }
        }
    }
    // IO
    safeglBindFramebuffer(&blendFboId);	//Rendering offscreen
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_COLOR_ATTACHMENT0_EXT);
    std::vector<float> pixels(3 * IMAGE_WIDTH * IMAGE_HEIGHT);
    glReadPixels(0, 0, IMAGE_WIDTH, IMAGE_HEIGHT, GL_RGB, GL_FLOAT, &(pixels[0]));
    safeglUnbindFramebuffer();
    image<spectrum> img(IMAGE_WIDTH, IMAGE_HEIGHT);
    for(int i = 0; i < img.height(); i++)
    {
        for(int j = 0; j < img.width(); j++)
        {
            int idx = i * img.width() + j;
            img.at(j, i).r = real(pixels[idx * 3 + 0]);
            img.at(j, i).g = real(pixels[idx * 3 + 1]);
            img.at(j, i).b = real(pixels[idx * 3 + 2]);
        }
    }
    return img;
}

gl_renderer::~gl_renderer(void)
{
    _cleanup();
}

void gl_renderer::_blendImage()
{
    glEnable(GL_BLEND); 
    glBlendFunc(GL_ONE, GL_ONE);
    safeglBindFramebuffer(&blendFboId);
    glClear(GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glColor4f(1,1,1,1);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, targetTexId.id);
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
    glTexCoord2d(0.0,0.0); glVertex2d(-1.0,-1.0);
    glTexCoord2d(1.0,0.0); glVertex2d(1.0,-1.0);
    glTexCoord2d(1.0,1.0); glVertex2d(1.0,1.0);
    glTexCoord2d(0.0,1.0); glVertex2d(-1.0,1.0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    safeglUnbindFramebuffer();
    glDisable(GL_BLEND);
}