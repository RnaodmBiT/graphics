
project(freetype C)
cmake_minimum_required(VERSION 3.2)

# Specify library include directories
include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories("${PROJECT_SOURCE_DIR}/include/freetype")
include_directories("${PROJECT_SOURCE_DIR}/include/freetype/config")

# For the auto-generated ftmodule.h file
include_directories("${PROJECT_BINARY_DIR}/include")
include_directories("${PROJECT_SOURCE_DIR}/objs")

include_directories(include)
include_directories("src/truetype")
include_directories("src/sfnt")
include_directories("src/autofit")
include_directories("src/smooth")
include_directories("src/raster")
include_directories("src/psaux")
include_directories("src/psnames")

# First, compiler definitions for building the library
add_definitions(-DFT2_BUILD_LIBRARY)
add_definitions("-DFT_CONFIG_MODULES_H=<ftmodule.h>")

set(BASE_SRCS
    src/autofit/autofit.c
    src/bdf/bdf.c
    src/cff/cff.c
    src/base/ftbase.c
    src/base/ftbbox.c
    src/base/ftbitmap.c
    src/cache/ftcache.c
    src/base/ftdebug.c
    src/base/ftfstype.c
    src/base/ftgasp.c
    src/base/ftglyph.c
    src/base/ftgxval.c
    src/gzip/ftgzip.c
    src/base/ftinit.c
    src/base/ftlcdfil.c
    src/lzw/ftlzw.c
    src/base/ftmm.c
    src/base/ftotval.c
    src/base/ftpatent.c
    src/base/ftpfr.c
    src/base/ftstroke.c
    src/base/ftsynth.c
    src/base/ftsystem.c
    src/base/fttype1.c
    src/base/ftxf86.c
    src/gxvalid/gxvalid.c
    src/otvalid/otvalid.c
    src/pcf/pcf.c
    src/pfr/pfr.c
    src/psaux/psaux.c
    src/pshinter/pshinter.c
    src/psnames/psnames.c
    src/raster/raster.c
    src/sfnt/sfnt.c
    src/smooth/smooth.c
    src/truetype/truetype.c
    src/type1/type1.c
    src/cid/type1cid.c
    src/type42/type42.c
    src/winfonts/winfnt.c
    )

add_library(freetype STATIC ${BASE_SRCS} )
