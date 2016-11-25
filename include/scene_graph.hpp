#pragma once
#include <shape.hpp>
#include <texture.hpp>
#include <shader.hpp>
#include <font.hpp>
#include <core.hpp>

namespace tk {
    namespace graphics {

        struct RenderState {
            core::Mat4f transform;
            Shader* shader;

            RenderState() : shader(nullptr) { }
            RenderState(const core::Mat4f& transform) : transform(transform), shader(nullptr) { }

            void setShader(Shader* s) {
                if (s) {
                    shader = s;
                }
            }
        };

        class IDrawable {
        public:
            virtual ~IDrawable() { };
            virtual void draw(RenderState state) { };
        };


        class DrawableNode : public core::Node<IDrawable> {
        protected:
            core::Mat4f transform;
            core::Vec4f tint;
            Shader* shader;

        public:
            DrawableNode(const std::string& name) : Node<IDrawable>(name), tint{ 1.0f, 1.0f, 1.0f, 1.0f }, shader(nullptr) { }

            virtual void draw(RenderState state) {
                state.transform = state.transform * transform;
                state.setShader(shader);
                for (auto& child : children) {
                    child->draw(state);
                }
            }

            void setShader(Shader* s) {
                shader = s;
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
        public:
            ShapeNode(const std::string& name, const Shape& shape, const Texture* texture = nullptr) :
                DrawableNode(name),
                shape(shape),
                texture(texture) { }

            void draw(RenderState state) {
                state.setShader(shader);

                state.shader->apply();
                state.shader->setUniform("transform", state.transform * transform);
                state.shader->setUniform("tint", tint);
                if (texture) {
                    state.shader->setUniform("image", *texture);
                } else {
                    state.shader->clearTexture("image");
                }

                shape.draw();

                DrawableNode::draw(state);
            }
        };


        class TextNode : public DrawableNode {
            Shape shape;
            Texture texture;
            const Font* font;
            core::Vec2i textSize;
        public:
            TextNode(const std::string& name, const Font* font, const std::string& text, int size) :
                DrawableNode(name),
                font(font),
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

            void draw(RenderState state) {
                state.setShader(shader);

                state.shader->apply();
                state.shader->setUniform("transform", state.transform * transform);
                state.shader->setUniform("tint", tint);
                state.shader->setUniform("image", texture);

                shape.draw();

                DrawableNode::draw(state);
            }

            const core::Vec2i& getSize() const {
                return textSize;
            }
        };


    }
}
