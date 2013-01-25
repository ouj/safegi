overview
========
This package contains the source code implementation of our [safegi paper](http://www.cs.dartmouth.edu/~ouj/site/Research/Entries/2010/6/28_SafeGI__Type_Checking_to_Improve_Correctness_in_Rendering_System_Implementation.html).


build
-----------------------------------------------------------
__MacOSX__

    cd src
    ./cmake-xcode.sh

__Linux__

    cd src
    ./cmake-mk.sh

execution
-----------------------------------------------------------
run the executable directly, the images will be generated in the same folder. Image files are ppm format, it can be convert to other formats using ImageMagick.



folder structure
-----------------------------------------------------------
#### README.md ####
This file

###[libs]###
Library source code folder.

####[libs\tsafegi]####
typed SafeGI library

* __dimensions.h__    --  contains the dimension definition and dimension analysis implementation mentioned in section 3.1.1 Dimensional Analysis.
* __real.h__          --  basic real number and tuple type without dimension.
* __m_real.h__        --  real number type and tuple types with dimensional constraint.
* __m_units.h__       --  units definition, such as meters, seconds, degrees..
* __m_spectrum.h__    --  spectrum type with dimensional analysis
* __spaces.h__        --  basic space definition, such as shape_s, world_s, local_s, mentioned in section 3.1.1 Space Analysis
* __m_geom.h__        --  geometry type with space analysis implementation mentioned in section 3.2 Geometric Space Analysis.
    + _point._     contains x,y,z components stores Cartesian coordinates in length dimension.
    + _vector._    contains x,y,z components in length dimension.
    + _direction._ directional vector, which is normalized to length 1. Contains x,y,z components in unit dimension.
    + _normal._    specific direction type represent surface normal
    + _rigidmap._  rigid mapping type used to transform point, vector, direction and normal from one space to another.
    
* __xform.h__         --  transform class definition
* __linalg.h__        --  basic linear algebra operation definitions.
* __lens.h__          --  lens class used to generate ray samples.
* __m_sampling.h__    --  different sample types, such as shadow sample, lens sample direction sample and brdf sample. 
* __direct.h__        --  direct lighting integrator. 
    * _spectrum<radiance_d>_ l(..) compute radiance spectrum for lens sample point p and direction w.
    * _spectrum<radiance_d>_ le(..) compute emission radiance spectrum of the surface.
    * _spectrum<radiance_d>_ ld(..) compute direct illumination radiance spectrum of the surface.
* __path.h__  --  path tracer integrator.
    * _spectrum<radiance_d>_ li(..) compute indirect illumination radiance spectrum of the surface
* __brdf.h__  --  brdf for materials, including Lambert, Phong and mirror. The brdf class is defined similar to BxDF class in PBRT. 
    + _spectrum<brdf_d>_ f(..) return the brdf spectrum according of the brdf.
    + _spectrum<rho_d>_ rho(..) return the rho spectrum of the brdf
    + _brdfSample<local_s>_ sample(..) return the brdf sample of the brdf.     
    + _mreal<invsolidangle_d>_ pdf(..) return the pdf.
* __scene.h__         --  definitions for scene objects, such camera, light and materials.
* __source.h__        --  point light source and area light source.
* __shape.h__         --  base shapes, including sphere, quad and triangle.
* __mesh.h__          --  triangle mesh shape.
* __bbox.h__          --  bounding box class.
* __tracer.h__        --  ray tracer class
* __tracerutils.h__   --  utility class for ray tracing.
* __type_trait.h__    --  type trait deduction facilities used to impose type constraint between CPU-end and GPU-end of the SafeGI GPU renderer.
* __safe_gl.h__       --  typed OpenGL wrapper functions used by SafeGI GPU renderer.
* __common.h__        --  common header
* __image.h__         --  image class for rendering outputs.    
* __std.h__           --  standard C++ STL header
* __stub.cpp__        --  an empty cpp file

    
####[ libs/gi_aux ]####
SafeGI auxiliary classes.

* __bunny.cpp__       --  bunny data
* __fileio_t.h__      --  image I/O functions
* __test_scene_t.h__  --  test scene generation utilities
* __timer.h__         --  timer class.
    
####[ libs/sparser ]####
SafeGI GLSL parser for type checking.

* __aux_data.cpp__        --  parser auxiliary data structures.
* __aux_data.h__          --  parser auxiliary data structures.
* __context.cpp__         --  parsing context
* __context.h__           --  parsing context
* __parser.y__            --  bison file for parser.
* __predef_symbols.h__    --  pre-define file for dimensions, spaces and built-in functions mentioned in section 3.1.2 in the paper.
* __scanner.l__           --  flex file for scanner.
* __type_checker.cpp__    --  SafeGI GLSL type check interface
* __type_checker.h__      --  type check interface
* __unistd.h__            --  unix header

###[ apps ]###
Application source code folder.

####[ apps/tsafegi_gl ]####
Source code folder for typed SafeGI GPU renderer.
    
* __gl_renderer.cpp__     --  Source file for GPU renderer class. This class demonstrate how our SafeGI interface is used to create type safe GPU rendering program. 
* __gl_renderer.h__       --  GPU renderer class header
* __shader_src.cpp__      --  Typed GLSL source code for point light, area light and shadow mapping.
* __shader_src.h__        --  Typed GLSL source code header
* __main.cpp__            --  Main entry point of the typed SafeGI GPU renderer the program.
        
####[ apps/tsafegi_ray ]####
Source code folder for SafeGI CPU renderer.

* __main.cpp__            --  Main entry point of the typed SafeGI CPU ray tracer program.
