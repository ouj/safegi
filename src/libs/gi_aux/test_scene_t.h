#ifndef _SCENE_CREATION_H_
#define _SCENE_CREATION_H_

struct SceneDesc
{
    shared_ptr<Scene> _scene;
    string object;
    string light;
    string mat;
    string feat;
};

void addLambertQuad(shared_ptr<Scene> scene, const mreal<length_d>& radius, 
    const vector<world_s>& center, const direction<world_s>& axis, 
    const real& angle, const spectrum<rho_d>& rhod) {
        shared_ptr<Surface> quad = shared_ptr<Surface>(new Surface());
        quad->shape = shared_ptr<Shape>(new Quad(radius));
        quad->xform = shared_ptr<Xform<shape_s,world_s>>(new StaticXform<shape_s, world_s>(center, axis, angle));
        quad->material = shared_ptr<Material>(new Material(shared_ptr<Brdf>(new Lambert(rhod))));
        scene->surfaces.push_back(quad);
}

void addLambertEmitterQuad(shared_ptr<Scene> scene, const mreal<length_d>& radius, 
    const vector<world_s>& center, const direction<world_s>& axis, 
    const real& angle, const spectrum<rho_d>& rhod,
    const spectrum<power_d>& power) {
        shared_ptr<Shape> lightShape = shared_ptr<Shape>(new Quad(radius));
        shared_ptr<AreaSource> source = shared_ptr<AreaSource>(new AreaSource(lightShape,power));

        shared_ptr<Light> light = shared_ptr<Light>(new Light());
        light->xform = shared_ptr<Xform<source_s,world_s>>(new StaticXform<source_s, world_s>(center, axis, angle));
        light->source = source;

        shared_ptr<Surface> surface = shared_ptr<Surface>(new Surface());
        surface->shape = lightShape;
        surface->xform = shared_ptr<Xform<shape_s,world_s>>(new StaticXform<shape_s, world_s>(center, axis, angle));
        surface->material = shared_ptr<Material>(new Material(shared_ptr<Brdf>(new Lambert(rhod)),
            dynamic_pointer_cast<AreaSource>(light->source)));

        scene->surfaces.push_back(surface);
        scene->lights.push_back(light);
}

SceneDesc sphereScene(bool arealight, bool animation, int sphereMatType) {
    SceneDesc desc;
    // scene
    shared_ptr<Scene> scene = shared_ptr<Scene>(new Scene());

    // camera
    scene->camera = shared_ptr<Camera>(new Camera());
    scene->camera->xform = shared_ptr<Xform<lens_s,world_s>>(new StaticXform<lens_s, world_s>(vector<world_s>(0*meters,0*meters,4*meters)));
    scene->camera->lens = shared_ptr<Lens>(new PinholeLens(40*degrees,40*degrees));

    // sphere
    shared_ptr<Surface> sphere = shared_ptr<Surface>(new Surface());
    switch(sphereMatType) {
    case 0: 
        sphere->material = shared_ptr<Material>(new Material(shared_ptr<Brdf>(new Lambert(spectrum<rho_d>(0.7,0.7,0.7))))); 
        desc.mat = "lambert";
        break;
    case 1: 
        sphere->material = shared_ptr<Material>(new Material(shared_ptr<Brdf>(new Phong(spectrum<rho_d>(0.4,0.4,0.4),spectrum<rho_d>(0.3,0.3,0.3),100)))); 
        desc.mat = "phong";
        break;
    case 2: sphere->material = shared_ptr<Material>(new Material(shared_ptr<Brdf>(new Mirror(spectrum<rho_d>(0.7,0.7,0.7))))); 
        desc.mat = "mirror";
        break;
    }
    sphere->shape = shared_ptr<Shape>(new Sphere(1*meters));
    if(animation) {
        sphere->xform = shared_ptr<Xform<shape_s,world_s>>(new AnimatedTranslationXform<shape_s, world_s>(
            vector<world_s>(0.2*meters,-1*meters,0*meters),0*seconds,
            vector<world_s>(-0.2*meters,-1*meters,0*meters),1*seconds));
        desc.feat = "motion";
    }
    else {
        sphere->xform = shared_ptr<Xform<shape_s,world_s>>(new StaticXform<shape_s, world_s>(vector<world_s>(0*meters,-1*meters,0*meters)));
        desc.feat = "std";
    }
    scene->surfaces.push_back(sphere);
    desc.object = "sphere";
    // bottom
    addLambertQuad(scene, 2*meters,
        vector<world_s>(0*meters,-2*meters,0*meters), 
        direction<world_s>(1,0,0), toRadians(-90),
        spectrum<rho_d>(0.7,0.7,0.7));

    // top
    addLambertQuad(scene, 2*meters,
        vector<world_s>(0*meters,2*meters,0*meters), 
        direction<world_s>(1,0,0), toRadians(90),
        spectrum<rho_d>(0.7,0.7,0.7));
    // left
    addLambertQuad(scene, 2*meters,
        vector<world_s>(-2*meters,0*meters,0*meters), 
        direction<world_s>(0,1,0), toRadians(90),
        spectrum<rho_d>(0.7,0.4,0.4));
    // right
    addLambertQuad(scene, 2*meters,
        vector<world_s>(2*meters,0*meters,0*meters), 
        direction<world_s>(0,1,0), toRadians(-90),
        spectrum<rho_d>(0.4,0.7,0.4));
    // back
    addLambertQuad(scene, 2*meters,
        vector<world_s>(0*meters,0*meters,-2*meters),
        direction<world_s>(1,0,0), toRadians(0),
        spectrum<rho_d>(0.7,0.7,0.7));

    // light
    if(!arealight) {
        shared_ptr<Light> light = shared_ptr<Light>(new Light());
        light->xform = shared_ptr<Xform<source_s,world_s>>(new StaticXform<source_s, world_s>(vector<world_s>(0*meters,1.995*meters,0*meters)));
        light->source = shared_ptr<Source>(new PointSource(spectrum<power_d>(10*watts,10*watts,10*watts)));
        scene->lights.push_back(light);
        desc.light = "point";
    } else {
        addLambertEmitterQuad(scene, 0.5*meters, 
            vector<world_s>(0*meters,1.995*meters,0*meters),
            direction<world_s>(1,0,0), toRadians(90),
            spectrum<rho_d>(), spectrum<power_d>(10*watts,10*watts,10*watts));
        desc.light = "area";
    }
    desc._scene = scene;
    return desc;
}

SceneDesc furnaceScene() {
    SceneDesc desc;
    // scene
    shared_ptr<Scene> scene = shared_ptr<Scene>(new Scene());

    // camera
    scene->camera = shared_ptr<Camera>(new Camera());
    scene->camera->xform = shared_ptr<Xform<lens_s,world_s>>(new StaticXform<lens_s, world_s>(vector<world_s>(0*meters,0*meters,1.995*meters)));
    scene->camera->lens = shared_ptr<Lens>(new PinholeLens(60*degrees,60*degrees));

    // spectrums
    spectrum<rho_d> rhod = spectrum<rho_d>(0.7,0.7,0.7);
    spectrum<power_d> power = spectrum<power_d>(100*watts,100*watts,100*watts);

    // bottom
    addLambertEmitterQuad(scene, 2*meters,
        vector<world_s>(0*meters,-2*meters,0*meters), 
        direction<world_s>(1,0,0), toRadians(-90),
        rhod, power);

    // top
    addLambertEmitterQuad(scene, 2*meters,
        vector<world_s>(0*meters,2*meters,0*meters), 
        direction<world_s>(1,0,0), toRadians(90),
        rhod, power);
    // left
    addLambertEmitterQuad(scene, 2*meters,
        vector<world_s>(-2*meters,0*meters,0*meters), 
        direction<world_s>(0,1,0), toRadians(90),
        rhod, power);
    // right
    addLambertEmitterQuad(scene, 2*meters,
        vector<world_s>(2*meters,0*meters,0*meters), 
        direction<world_s>(0,1,0), toRadians(-90),
        rhod, power);
    // back
    addLambertEmitterQuad(scene, 2*meters,
        vector<world_s>(0*meters,0*meters,-2*meters),
        direction<world_s>(1,0,0), toRadians(0),
        rhod, power);
    // front
    addLambertEmitterQuad(scene, 2*meters,
        vector<world_s>(0*meters,0*meters,2*meters),
        direction<world_s>(1,0,0), toRadians(180),
        rhod, power);
    desc.object = "furnace";
    desc.feat = "std";
    desc.light = "area";
    desc.mat = "lambert";
    desc._scene = scene;
    return desc;
}

extern double pos[];
extern int idx[];
extern double norm[];
shared_ptr<Shape> makeBunny() {
    std::vector<point<shape_s>> bunny_pos;
    std::vector<int> bunny_idx;
    std::vector<normal<shape_s>> bunny_norm;
    auto scale = 15.0 * meters;
    for(int i = 0; i < 107841; i += 3) {
        bunny_pos.push_back(point<shape_s>(pos[i]*scale, pos[i+1]*scale, pos[i+2]*scale));
        bunny_norm.push_back(normal<shape_s>(norm[i], norm[i+1], norm[i+2]));
    }
    for(int i = 0; i < 208353; i ++) {
        bunny_idx.push_back(idx[i]);
    }
    return shared_ptr<Shape>(new Mesh(bunny_pos, bunny_norm, bunny_idx));
}

SceneDesc manyBunnyScene(bool arealight, bool dof, int sphereMatType) {
    SceneDesc desc;
    // scene
    shared_ptr<Scene> scene = shared_ptr<Scene>(new Scene());

    // camera
    scene->camera = shared_ptr<Camera>(new Camera());
    scene->camera->xform = shared_ptr<Xform<lens_s,world_s>>(new StaticXform<lens_s, world_s>(vector<world_s>(0*meters,2*meters,8*meters), direction<world_s>(1,0,0), toRadians(-15)));
    if(dof)
    {
        scene->camera->lens = shared_ptr<Lens>(new Thinlens(40*degrees,40*degrees, 7.0f*meters, 0.3f*meters));
        desc.feat = "dof";
    }
    else
    {
        scene->camera->lens = shared_ptr<Lens>(new PinholeLens(40*degrees,40*degrees));
        desc.feat = "std";
    }

   
    shared_ptr<Material> mat;
    switch(sphereMatType) {
    case 0: 
        mat = shared_ptr<Material>(new Material(shared_ptr<Brdf>(new Lambert(spectrum<rho_d>(0.7,0.7,0.7))))); 
        desc.mat = "lambert";
        break;
    case 1: 
        mat = shared_ptr<Material>(new Material(shared_ptr<Brdf>(new Phong(spectrum<rho_d>(0.7,0.7,0.7),spectrum<rho_d>(0.3,0.3,0.3),50)))); 
        desc.mat = "phong";
        break;
    case 2: 
        mat = shared_ptr<Material>(new Material(shared_ptr<Brdf>(new Mirror(spectrum<rho_d>(0.7,0.7,0.7))))); 
        desc.mat = "mirror";
        break;
    }

    shared_ptr<Shape> bunnyShape = makeBunny();
    for(int z = -2; z <= 2 ;z++)
    {
        for(int x = -2; x <= 2; x++)
        {
            shared_ptr<Surface> obj = shared_ptr<Surface>(new Surface());
            obj->shape = bunnyShape; 
            obj->material = mat;
            obj->xform = 
                shared_ptr<Xform<shape_s,world_s>>(
                new StaticXform<shape_s, world_s>(vector<world_s>((3.0f*x+0.4f)*meters,-2.35*meters,(3.0f*z)*meters)));
            scene->surfaces.push_back(obj);
        }
    }
    desc.object = "many_bunny";

    // bottom
    addLambertQuad(scene, 20*meters,
        vector<world_s>(0*meters,-2*meters,0*meters), 
        direction<world_s>(1,0,0), toRadians(-90),
        spectrum<rho_d>(0.4,0.7,0.4));
        // back
    addLambertQuad(scene, 20*meters,
        vector<world_s>(0*meters,0*meters,-8*meters),
        direction<world_s>(1,0,0), toRadians(0),
        spectrum<rho_d>(0.7,0.4,0.4));

    // light
    if(!arealight) {
        shared_ptr<Light> light = shared_ptr<Light>(new Light());
        light->xform = shared_ptr<Xform<source_s,world_s>>(new StaticXform<source_s, world_s>(vector<world_s>(0*meters,4.0f*meters,10.0f*meters)));
        light->source = shared_ptr<Source>(new PointSource(spectrum<power_d>(10*watts,10*watts,10*watts)));
        scene->lights.push_back(light);
        desc.light = "point";
    } else {
        addLambertEmitterQuad(scene, 0.5*meters, 
            vector<world_s>(0*meters,4.0*meters,0*meters),
            direction<world_s>(1,0,0), toRadians(90),
            spectrum<rho_d>(), spectrum<power_d>(10*watts,10*watts,10*watts));
        desc.light = "area";
    }
    desc._scene = scene;
    return desc;
}

SceneDesc manyBunnyScene2(bool arealight, bool dof, int sphereMatType) {
    SceneDesc desc;
    // scene
    shared_ptr<Scene> scene = shared_ptr<Scene>(new Scene());

    // camera
    scene->camera = shared_ptr<Camera>(new Camera());
    scene->camera->xform = shared_ptr<Xform<lens_s,world_s>>(new StaticXform<lens_s, world_s>(vector<world_s>(0*meters,5*meters,9.5*meters), direction<world_s>(1,0,0), toRadians(-50)));
    if(dof)
    {
        scene->camera->lens = shared_ptr<Lens>(new Thinlens(40*degrees,40*degrees, 7.0f*meters, 0.3f*meters));
        desc.feat = "dof";
    }
    else
    {
        scene->camera->lens = shared_ptr<Lens>(new PinholeLens(40*degrees,40*degrees));
        desc.feat = "std";
    }


    shared_ptr<Material> mat;
    switch(sphereMatType) {
    case 0: 
        mat = shared_ptr<Material>(new Material(shared_ptr<Brdf>(new Lambert(spectrum<rho_d>(0.7,0.7,0.7))))); 
        desc.mat = "lambert";
        break;
    case 1: 
        mat = shared_ptr<Material>(new Material(shared_ptr<Brdf>(new Phong(spectrum<rho_d>(0.7,0.7,0.7),spectrum<rho_d>(0.3,0.3,0.3),50)))); 
        desc.mat = "phong";
        break;
    case 2: 
        mat = shared_ptr<Material>(new Material(shared_ptr<Brdf>(new Mirror(spectrum<rho_d>(0.7,0.7,0.7))))); 
        desc.mat = "mirror";
        break;
    }

    shared_ptr<Shape> bunnyShape = makeBunny();
    for(int z = -3; z <= 3 ;z++)
    {
        for(int x = -3; x <= 3; x++)
        {
            shared_ptr<Surface> obj = shared_ptr<Surface>(new Surface());
            obj->shape = bunnyShape; 
            obj->material = mat;
            obj->xform = 
                shared_ptr<Xform<shape_s,world_s>>(
                new StaticXform<shape_s, world_s>(vector<world_s>((3.0f*x+0.4f)*meters,-2.35*meters,(3.0f*z)*meters)));
            scene->surfaces.push_back(obj);
        }
    }
    desc.object = "many_bunny2";

    // bottom
    addLambertQuad(scene, 30*meters,
        vector<world_s>(0*meters,-2*meters,0*meters), 
        direction<world_s>(1,0,0), toRadians(-90),
        spectrum<rho_d>(0.4,0.7,0.4));

    // light
    if(!arealight) {
        shared_ptr<Light> light = shared_ptr<Light>(new Light());
        light->xform = shared_ptr<Xform<source_s,world_s>>(new StaticXform<source_s, world_s>(vector<world_s>(0*meters,5.0f*meters,10.0f*meters)));
        light->source = shared_ptr<Source>(new PointSource(spectrum<power_d>(10*watts,10*watts,10*watts)));
        scene->lights.push_back(light);
        desc.light = "point";
    } else {
        addLambertEmitterQuad(scene, 1.5*meters, 
            vector<world_s>(0*meters,5.0*meters,0*meters),
            direction<world_s>(1,0,0), toRadians(90),
            spectrum<rho_d>(), spectrum<power_d>(10*watts,10*watts,10*watts));
        desc.light = "area";
    }
    desc._scene = scene;
    return desc;
}

SceneDesc bunnyScene(bool arealight, bool animation, int sphereMatType) {
    SceneDesc desc;
    // scene
    shared_ptr<Scene> scene = shared_ptr<Scene>(new Scene());

    // camera
    scene->camera = shared_ptr<Camera>(new Camera());
    scene->camera->xform = shared_ptr<Xform<lens_s,world_s>>(new StaticXform<lens_s, world_s>(vector<world_s>(0*meters,0*meters,4*meters)));
    scene->camera->lens = shared_ptr<Lens>(new PinholeLens(40*degrees,40*degrees));

    // sphere
    shared_ptr<Surface> obj = shared_ptr<Surface>(new Surface());
    switch(sphereMatType) {
    case 0: 
        obj->material = shared_ptr<Material>(new Material(shared_ptr<Brdf>(new Lambert(spectrum<rho_d>(0.7,0.7,0.7))))); 
        desc.mat = "lambert";
        break;
    case 1: 
        obj->material = shared_ptr<Material>(new Material(shared_ptr<Brdf>(new Phong(spectrum<rho_d>(0.7,0.7,0.7),spectrum<rho_d>(0.3,0.3,0.3),50)))); 
        desc.mat = "phong";
        break;
    case 2: 
        obj->material = shared_ptr<Material>(new Material(shared_ptr<Brdf>(new Mirror(spectrum<rho_d>(0.7,0.7,0.7))))); 
        desc.mat = "mirror";
        break;
    }

    obj->shape = makeBunny(); 
    desc.object = "bunny";

    if(animation) {
        obj->xform = shared_ptr<Xform<shape_s,world_s>>(new AnimatedTranslationXform<shape_s, world_s>(
            vector<world_s>(0.6*meters,-2.35*meters,0*meters),0*seconds,
            vector<world_s>(0.2*meters,-2.35*meters,0*meters),1*seconds));
        desc.feat = "motion";
    }
    else {
        obj->xform = shared_ptr<Xform<shape_s,world_s>>(new StaticXform<shape_s, world_s>(vector<world_s>(0.4*meters,-2.35*meters,0*meters)));
        desc.feat = "std";
    }
    scene->surfaces.push_back(obj);

    // bottom
    addLambertQuad(scene, 2*meters,
        vector<world_s>(0*meters,-2*meters,0*meters), 
        direction<world_s>(1,0,0), toRadians(-90),
        spectrum<rho_d>(0.7,0.7,0.7));

    // top
    addLambertQuad(scene, 2*meters,
        vector<world_s>(0*meters,2*meters,0*meters), 
        direction<world_s>(1,0,0), toRadians(90),
        spectrum<rho_d>(0.7,0.7,0.7));
    // left
    addLambertQuad(scene, 2*meters,
        vector<world_s>(-2*meters,0*meters,0*meters), 
        direction<world_s>(0,1,0), toRadians(90),
        spectrum<rho_d>(0.7,0.4,0.4));
    // right
    addLambertQuad(scene, 2*meters,
        vector<world_s>(2*meters,0*meters,0*meters), 
        direction<world_s>(0,1,0), toRadians(-90),
        spectrum<rho_d>(0.4,0.7,0.4));
    // back
    addLambertQuad(scene, 2*meters,
        vector<world_s>(0*meters,0*meters,-2*meters),
        direction<world_s>(1,0,0), toRadians(0),
        spectrum<rho_d>(0.7,0.7,0.7));

    // light
    if(!arealight) {
        shared_ptr<Light> light = shared_ptr<Light>(new Light());
        light->xform = shared_ptr<Xform<source_s,world_s>>(new StaticXform<source_s, world_s>(vector<world_s>(0*meters,1.995*meters,0*meters), direction<world_s>(1,0,0), toRadians(-90)));
        light->source = shared_ptr<Source>(new PointSource(spectrum<power_d>(10*watts,10*watts,10*watts)));
        scene->lights.push_back(light);
        desc.light = "point";
    } else {
        addLambertEmitterQuad(scene, 0.5*meters, 
            vector<world_s>(0*meters,1.995*meters,0*meters),
            direction<world_s>(1,0,0), toRadians(90),
            spectrum<rho_d>(), spectrum<power_d>(10*watts,10*watts,10*watts));
        desc.light = "area";
    }
    desc._scene = scene;
    return desc;
}

#endif