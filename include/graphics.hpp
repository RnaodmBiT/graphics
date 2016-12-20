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

        TK_GRAPHICS void clipRectangle(const core::Vec2f& position, const core::Vec2f& size);
        TK_GRAPHICS void clearClip();

    }
}
