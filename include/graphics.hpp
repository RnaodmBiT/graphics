#pragma once
#include <linkage.hpp>
#include <GL/glew.h>

#include <array.hpp>
#include <buffer.hpp>
#include <shader.hpp>
#include <texture.hpp>
#include <bitmap.hpp>
#include <font.hpp>
#include <shape.hpp>
#include <scene_graph.hpp>

namespace tk {
    namespace graphics {

        TK_GRAPHICS bool initialize();
        TK_GRAPHICS bool initializeExtensions();

    }
}
