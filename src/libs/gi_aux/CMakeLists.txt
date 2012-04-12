# set renderer sources
set(sources
    test_scene_t.h
	bunny.cpp
    fileio_t.h
    )
    INCLUDE_DIRECTORIES(../../LIBS/)
# create renderer executable
ADD_LIBRARY(gi_aux ${sources})
TARGET_LINK_LIBRARIES(gi_aux)
