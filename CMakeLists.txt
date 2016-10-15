cmake_minimum_required(VERSION 3.2)
project (tk-graphics)

option(TK_BUILD_SHARED "TK_BUILD_SHARED" ON)

file(GLOB SOURCES src/*.cpp src/*.c)
file(GLOB HEADERS include/*.hpp include/*.h)

set(BUILD_MODE STATIC)
if (TK_BUILD_SHARED)
    set(BUILD_MODE SHARED)
endif()

add_library(tk-graphics ${BUILD_MODE} ${SOURCES} ${HEADERS})
add_dependencies(tk-graphics tk-core)
