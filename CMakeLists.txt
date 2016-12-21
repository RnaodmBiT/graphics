cmake_minimum_required(VERSION 3.2)
project (tk-graphics)

find_package(OpenGL)

option(TK_BUILD_SHARED "TK_BUILD_SHARED" ON)

file(GLOB_RECURSE SOURCES src/*.cpp src/*.c)
file(GLOB_RECURSE HEADERS include/*.hpp)

add_definitions(-DTK_BUILD_GRAPHICS)

set(BUILD_MODE STATIC)
if (TK_BUILD_SHARED)
    set(BUILD_MODE SHARED)
    add_definitions(-DTK_SHARED)
endif()

add_definitions(-DGLEW_BUILD)

add_subdirectory(thirdparty/freetype-2.4.0)
include_directories(thirdparty/freetype-2.4.0/include)

include_directories(thirdparty/stb)

add_library(tk-graphics ${BUILD_MODE} ${SOURCES} ${HEADERS})
target_link_libraries(tk-graphics tk-core freetype ${OPENGL_gl_LIBRARY})
