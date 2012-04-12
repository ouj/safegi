#define USE_SAFE_GL
#include <tsafegi/tracer.h>

#ifdef WIN32
#include <GL/glew.h>
#include <GL/wglew.h>
#include <GL/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <stdio.h>
#include <time.h>
#include <assert.h>

#include "gl_renderer.h"
#include <tsafegi/mesh.h>
#include <gi_aux/test_scene_t.h>
#include <gi_aux/fileio_t.h>
#include <gi_aux/timer.h>
#include <iomanip>
using std::setw;

int main(int argc, char** argv) 
{
    std::vector<SceneDesc> scenes;
/*
    scenes.push_back(sphereScene(false,false,0));
    scenes.push_back(sphereScene(true,false,0));
    scenes.push_back(sphereScene(false,false,1));
    scenes.push_back(sphereScene(true,false,1));
    scenes.push_back(sphereScene(false,true,0));
    scenes.push_back(sphereScene(true,true,0));
    scenes.push_back(sphereScene(false,true,1));
    scenes.push_back(sphereScene(true,true,1));
*/

    scenes.push_back(manyBunnyScene(false, true, 1));
    scenes.push_back(manyBunnyScene2(true, false, 1));

    scenes.push_back(bunnyScene(false,false,0));
    scenes.push_back(bunnyScene(true,false,0));
    scenes.push_back(bunnyScene(false,false,1));
    scenes.push_back(bunnyScene(true,false,1));
    scenes.push_back(bunnyScene(false,true,0));
    scenes.push_back(bunnyScene(true,true,0));
    scenes.push_back(bunnyScene(false,true,1));
    scenes.push_back(bunnyScene(true,true,1));

    glutInit(&argc, argv);

    GLint m_GlutWindow = 0;
    glutInitDisplayMode(GLUT_RGB | GLUT_ALPHA | GLUT_DEPTH | GLUT_DOUBLE);
    m_GlutWindow = glutCreateWindow("safegi | glrenderer");
    assert(m_GlutWindow);
   
    gl_renderer renderer;
    renderer.init();

    Timer tm;

    cout << "object"  << "\t" << "material" << "\t" << "light" << "\t" << "animation" << "\t" << "time" << endl;
    for(size_t s = 0; s < scenes.size(); s ++)
    {
        SceneDesc &desc = scenes[s];
        tm.Reset();
        tm.Start();
        image<spectrum<radiance_d>> img = renderer.render_scene(scenes[s]._scene, 0 * seconds, 1 * seconds, 512);
        tm.Stop();
        stringstream filename;
        filename << "tgl." << desc.object << "." << desc.mat << "." << desc.light << "." << desc.feat << ".ppm";
        save(img, filename.str());
        cout << desc.object  << "\t" << desc.mat << "\t" << desc.light << "\t" << desc.feat  << "\t" << tm.GetElapsedTime() << endl;
    }


    glutDestroyWindow(m_GlutWindow);
}
