#pragma once
#include <array.hpp>
#include <buffer.hpp>
#include <vector.hpp>

namespace tk {
    namespace graphics {

        class TK_GRAPHICS Shape {
            Buffer vertexBuffer, colorBuffer, uvBuffer;
            Array array;
            int vertexCount;
        public:

            Shape() { }

            Shape(Shape&& move) :
                vertexBuffer(std::move(move.vertexBuffer)),
                colorBuffer(std::move(move.colorBuffer)),
                uvBuffer(std::move(move.uvBuffer)),
                array(std::move(move.array)) {
                std::swap(vertexCount, move.vertexCount);
            }

            static Shape rectangle(const core::Vec2f& position, const core::Vec2f& size);

            void draw();

        };

    }
}