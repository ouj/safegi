#include <tsafegi/tracer.h>
#include "stdio.h"
#include <iomanip>
using std::setw;
#include <tsafegi/mesh.h>

#include <tsafegi/direct.h>
#include <tsafegi/path.h>

#include <gi_aux/test_scene_t.h>
#include <gi_aux/fileio_t.h>
#include <gi_aux/timer.h>

int main(int argc, char *argv[]) {

    const int w = 512;
    const int h = 512;

    // scenes
    Timer tm;
    std::vector<SceneDesc> scenes;
/*
    scenes.push_back(sphereScene(false,false,0));
    scenes.push_back(sphereScene(true,false,0));  
    scenes.push_back(sphereScene(false,false,1)); 
    scenes.push_back(sphereScene(true,false,1));  
    scenes.push_back(sphereScene(false,false,2));
    scenes.push_back(sphereScene(true,false,2));
    scenes.push_back(sphereScene(false,true,0));
    scenes.push_back(sphereScene(true,true,0));
    scenes.push_back(sphereScene(false,true,1)); 
    scenes.push_back(sphereScene(true,true,1));  
    scenes.push_back(sphereScene(false,true,2));
    scenes.push_back(sphereScene(true,true,2));
*/
    scenes.push_back(manyBunnyScene(false, false, 1));
    scenes.push_back(manyBunnyScene(false, true, 1));
    scenes.push_back(manyBunnyScene(false, true, 0));

    scenes.push_back(bunnyScene(false,false,0));
    scenes.push_back(bunnyScene(true,false,0));
    scenes.push_back(bunnyScene(false,false,1));
    scenes.push_back(bunnyScene(true,false,1));
    scenes.push_back(bunnyScene(false,false,2));
    scenes.push_back(bunnyScene(true,false,2));
    scenes.push_back(bunnyScene(false,true,0));
    scenes.push_back(bunnyScene(true,true,0));
    scenes.push_back(bunnyScene(false,true,1));
    scenes.push_back(bunnyScene(true,true,1));
    scenes.push_back(bunnyScene(false,true,2));
    scenes.push_back(bunnyScene(true,true,2));

    //scenes.push_back(furnaceScene());

    // tracers
    std::vector<shared_ptr<Tracer>> tracers;
    tracers.push_back(shared_ptr<Tracer>(new Tracer(shared_ptr<Integrator>(new DirectIntegrator()))));
    tracers.push_back(shared_ptr<Tracer>(new Tracer(shared_ptr<Integrator>(new DirectMISIntegrator()))));
    tracers.push_back(shared_ptr<Tracer>(new Tracer(shared_ptr<Integrator>(new PathIntegrator()))));

    cout << setw(25) << "image filename"  << "\t" << setw(25) << "rendering time" << endl;;
    // render all
    for(size_t t = 0; t < tracers.size(); t ++) {
        string tname;
        switch(t)
        {
        case 0: tname = "direct"; break;
        case 1: tname = "direct_mis"; break;
        case 2: tname = "path"; break;
        }

        cout << "integrator:" << tname << "\t" << "width:" << w << "\t" << "height:" << h << "\t" << endl;
        cout << "object"  << "\t" << "material" << "\t" << "light" << "\t" << "feature" << "\t" << "time" << endl;
        for(size_t s = 0; s < scenes.size(); s ++) {
            SceneDesc &desc = scenes[s];
            //int ns = 4;
            int ns = 64;
            if(tname == "path" || desc.feat != "std")
                ns = 256;

            // render scene
            tm.Reset();
            tm.Start();
            image<spectrum<radiance_d>> img = tracers[t]->render(desc._scene,0*seconds,1*seconds,w,h,ns);
            tm.Stop();
            stringstream filename;
            filename << "tray." << tname << "." << desc.object << "." << desc.mat << "." << desc.light << "." << desc.feat << "." << ns << ".ppm";
            // save image
            save(img, filename.str());
            cout << desc.object  << "\t" << desc.mat << "\t" << desc.light << "\t" << desc.feat  << "\t" << tm.GetElapsedTime() << endl;
        }
    }

    // done
    return 0;
}
