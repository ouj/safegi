# setting up cmake
cmake_minimum_required(VERSION 2.8)


# set renderer sources
set(sources
    bbox.h
    brdf.h
    common.h
    direct.h
    image.h
    lens.h
    linalg.h
    mesh.h
    path.h
    real.h
    scene.h
    shape.h
    source.h
    std.h
    tracer.h
    tracerutils.h
    xform.h
    u_geom.h
    u_sampling.h
    u_spectrum.h
    u_units.h
    safe_gl.h
    stub.cpp
    )

# create renderer executable
ADD_LIBRARY(usafegi ${sources})
TARGET_LINK_LIBRARIES(usafegi)