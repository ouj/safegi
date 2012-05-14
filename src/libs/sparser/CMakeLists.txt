# setting up macros

find_package(BISON)
find_package(FLEX)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

FLEX_TARGET(GlslScanner scanner.l ${CMAKE_CURRENT_SOURCE_DIR}/scanner.cpp)
BISON_TARGET(GlslParser parser.y ${CMAKE_CURRENT_SOURCE_DIR}/parser.cpp COMPILE_FLAGS "-t -d")

#ADD_FLEX_BISON_DEPENDENCY(GlslScanner GlslParser)

SET(SOURCES
	type_checker.cpp
    type_checker.h
    predef_symbols.h
    context.h
    context.cpp
    aux_data.h
    aux_data.cpp
	scanner.l
	parser.hpp
	parser.y
	${CMAKE_CURRENT_SOURCE_DIR}/scanner.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/parser.cpp
)

ADD_LIBRARY(sparser ${SOURCES})