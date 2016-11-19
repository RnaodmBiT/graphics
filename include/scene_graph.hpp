#pragma once
#include <shape.hpp>
#include <texture.hpp>
#include <shader.hpp>
#include <font.hpp>
#include <core.hpp>

namespace tk {
    namespace graphics {

        class IDrawable {
        public:
            virtual ~IDrawable() { };
            virtual void draw(const core::Mat4f& transform = core::Mat4f()) { };
        };


        class DrawableNode : public core::Node<IDrawable> {
        protected:
            core::Mat4f transform;
            core::Vec4f tint;
        public:
            DrawableNode(const std::string& name) : Node<IDrawable>(name), tint{ 1.0f, 1.0f, 1.0f, 1.0f } { }

            virtual void draw(const core::Mat4f& matrix = core::Mat4f()) {
                core::Mat4f result = matrix * transform;
                for (auto& child : children) {
                    child->draw(result);
                }
            }

            const core::Mat4f& getTransform() const {
                return transform;
            }

            void setTransform(const core::Mat4f& matrix) {
                transform = matrix;
            }

            const core::Vec4f& getTint() const {
                return tint;
            }

            void setTint(const core::Vec4f& color) {
                tint = color;
            }
        };


        class ShapeNode : public DrawableNode {
            const Shape& shape;
            const Texture* texture;
            Shader* shader;
        public:
            ShapeNode(const std::string& name, const Shape& shape, Shader* shader, const Texture* texture = nullptr) :
                DrawableNode(name),
                shape(shape),
                shader(shader),
                texture(texture) { }

            void draw(const core::Mat4f& matrix = core::Mat4f()) {
                core::Mat4f t = matrix * transform;

                shader->apply();
                shader->setUniform("transform", t);
                shader->setUniform("tint", tint);
                if (texture) {
                    shader->setUniform("image", *texture);
                } else {
                    shader->clearTexture("image");
                }

                shape.draw();

                DrawableNode::draw(t);
            }
        };


        class TextNode : public DrawableNode {
            Shape shape;
            Texture texture;
            Shader* shader;
            const Font* font;
            core::Vec2i textSize;
        public:
            TextNode(const std::string& name, const Font* font, const std::string& text, int size, Shader* shader) :
                DrawableNode(name),
                font(font),
                shader(shader),
                texture(GL_TEXTURE_2D) {
                setText(text, size);
            }

            void setText(const std::string& text, int size) {
                Bitmap<uint8_t> textData = font->renderText(text, size);
                textSize = { textData.getWidth(), textData.getHeight() };

                std::swap(shape, Shape::rectangle({ 0, 0 }, { (float)textSize.x, (float)textSize.y }));
                texture.setData(textData.getData(), textData.getWidth(), textData.getHeight(), GL_R8, GL_RED, GL_UNSIGNED_BYTE);
                texture.useRedAsAlpha();
            }

            void draw(const core::Mat4f& matrix = core::Mat4f()) {
                core::Mat4f t = matrix * transform;

                shader->apply();
                shader->setUniform("transform", t);
                shader->setUniform("tint", tint);
                shader->setUniform("image", texture);

                shape.draw();

                DrawableNode::draw(t);
            }

            const core::Vec2i& getSize() const {
                return textSize;
            }
        };


    }
}
