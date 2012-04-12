# AUX_SOURCE_DIRECTORY(. SOURCES)

SET(SOURCES
main.cpp
shader_src.h
shader_src.cpp
gl_renderer.h
gl_renderer.cpp
)

ADD_EXECUTABLE(tgl ${SOURCES})
INCLUDE_DIRECTORIES(../../libs/t)


TARGET_LINK_LIBRARIES(tgl sparser tsafegi gi_aux ${LIBS_glew} ${LIBS_glut})
