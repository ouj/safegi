# AUX_SOURCE_DIRECTORY(. SOURCES)

SET(SOURCES
main.cpp
shader_src.h
shader_src.cpp
gl_renderer.h
gl_renderer.cpp
)

ADD_EXECUTABLE(ugl ${SOURCES})
include_directories(../../libs/u/)


TARGET_LINK_LIBRARIES(ugl gi_aux ${LIBS_glew} ${LIBS_glut})
