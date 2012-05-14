# setting up cmake
cmake_minimum_required(VERSION 2.8)

# set renderer sources
set(sources
    bbox.h
    brdf.h
    common.h
    dimensions.h
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
    spaces.h
    std.h
    tracer.h
    tracerutils.h
    xform.h
    m_real.h
    m_geom.h
    m_sampling.h
    m_spectrum.h
    m_units.h
    safe_gl.h
    type_trait.h
    stub.cpp
    )

# create renderer executable
ADD_LIBRARY(tsafegi ${sources})
TARGET_LINK_LIBRARIES(tsafegi)