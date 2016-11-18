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

        Shape Shape::circle(const core::Vec2f& p, float r, int res) {
            std::vector<core::Vec2f> points;
            std::vector<core::Vec4f> colors;
            std::vector<core::Vec2f> uvs;

            for (int i = 0; i < res; ++i) {
                float theta;
                core::Vec2f pos;
                
                theta = 2 * core::pi * float(i) / float(res);
                pos = p + core::Vec2f{ std::cos(theta), std::sin(theta) } * r;
                points.push_back(pos);
                colors.push_back({ 1, 1, 1, 1 });
                uvs.push_back(pos / (2.0f * r) + 0.5f);

                theta = 2 * core::pi * float(i + 1) / float(res);
                pos = p + core::Vec2f{ std::cos(theta), std::sin(theta) } *r;
                points.push_back(pos);
                colors.push_back({ 1, 1, 1, 1 });
                uvs.push_back(pos / (2.0f * r) + 0.5f);

                points.push_back(p);
                colors.push_back({ 1, 1, 1, 1 });
                uvs.push_back({ 0.5f, 0.5f });
            }

            Shape shape;
            shape.vertexBuffer = Buffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW);
            shape.colorBuffer = Buffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW);
            shape.uvBuffer = Buffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW);

            shape.vertexBuffer.setData(points.data(), (int)points.size());
            shape.colorBuffer.setData(colors.data(), (int)colors.size());
            shape.uvBuffer.setData(uvs.data(), (int)uvs.size());

            shape.array = Array(GL_TRIANGLES);
            shape.array.addBuffer(shape.vertexBuffer, GL_FLOAT, 2);
            shape.array.addBuffer(shape.colorBuffer, GL_FLOAT, 4);
            shape.array.addBuffer(shape.uvBuffer, GL_FLOAT, 2);

            shape.vertexCount = res * 3;
            return shape;
        }


        void Shape::draw() {
            array.draw(0, vertexCount);
        }

    }
}