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

            Shape();
            Shape(Shape&& move);
            void operator=(Shape&& move);

            static Shape rectangle(const core::Vec2f& position, const core::Vec2f& size);
            static Shape circle(const core::Vec2f& position, float radius, int resolution = 32);
            static Shape polygon(const core::Vec2f* points, const core::Vec4f* colors, const core::Vec2f* uvs, int count);

            void draw() const;

        };

    }
}