#include <shape.hpp>

namespace tk {
    namespace graphics {

        Shape Shape::rectangle(const core::Vec2f& p, const core::Vec2f& s) {
            core::Vec2f vertices[] = {
                { p.x, p.y },
                { p.x + s.x, p.y },
                { p.x, p.y + s.y },

                { p.x + s.x, p.y },
                { p.x + s.x, p.y + s.y },
                { p.x, p.y + s.y },
            };

            core::Vec4f colors[] = {
                { 1, 1, 1, 1 },
                { 1, 1, 1, 1 },
                { 1, 1, 1, 1 },

                { 1, 1, 1, 1 },
                { 1, 1, 1, 1 },
                { 1, 1, 1, 1 },
            };

            core::Vec2f uvs[] = {
                { 0, 0 },
                { 1, 0 },
                { 0, 1 },

                { 1, 0 },
                { 1, 1 },
                { 0, 1 },
            };

            Shape shape;
            shape.vertexBuffer = Buffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW);
            shape.colorBuffer = Buffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW);
            shape.uvBuffer = Buffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW);

            shape.vertexBuffer.setData(vertices, 6);
            shape.colorBuffer.setData(colors, 6);
            shape.uvBuffer.setData(uvs, 6);

            shape.array = Array(GL_TRIANGLES);
            shape.array.addBuffer(shape.vertexBuffer, GL_FLOAT, 2);
            shape.array.addBuffer(shape.colorBuffer, GL_FLOAT, 4);
            shape.array.addBuffer(shape.uvBuffer, GL_FLOAT, 2);

            shape.vertexCount = 6;

            return shape;
        }


        void Shape::draw() {
            array.draw(0, vertexCount);
        }

    }
}