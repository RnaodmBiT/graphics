#pragma once
#include <node.hpp>
#include <log.hpp>
#include <shape.hpp>
#include <texture.hpp>

namespace tk {
    namespace graphics {

        class IDrawable {
        public:
            virtual ~IDrawable() { }
            virtual void draw(const core::Mat4f& transform = core::Mat4f()) { }
        };


        class DrawableNode : public core::Node<IDrawable> {
        public:
            DrawableNode(const std::string& name) : core::Node<IDrawable>(name) { }
            virtual void draw(const core::Mat4f& transform = core::Mat4f()) {
                for (auto& child : children) {
                    child->draw(transform);
                }
            }
        };


        class ShapeNode : public DrawableNode {
            Shape& shape;
            core::Vec4f tint;
            core::Mat4f transform;
            const Texture* texture;
            Shader* shader;
            bool drawChildrenFirst;
        public:
            ShapeNode(const std::string& name,
                      Shape& shape,
                      const core::Mat4f transform,
                      Shader* shader,
                      const Texture* texture = nullptr,
                      const core::Vec4f& tint = { 1, 1, 1, 1 }) : 
                DrawableNode(name), shape(shape), tint(tint), texture(texture), shader(shader), transform(transform), drawChildrenFirst(false) { }

            void setDrawOrder(bool childrenFirst) {
                drawChildrenFirst = childrenFirst;
            }

            void draw(const core::Mat4f& t = core::Mat4f()) {
                core::Mat4f matrix = t * transform;

                if (drawChildrenFirst) {
                    DrawableNode::draw(matrix);
                }

                shader->apply();
                shader->setUniform("transform", matrix);
                shader->setUniform("tint", tint);
                if (texture) {
                    shader->setUniform("image", *texture);
                } else {
                    shader->clearTexture("image");
                }

                shape.draw();

                if (!drawChildrenFirst) {
                    DrawableNode::draw(matrix);
                }
            }

            const core::Vec4f& getTint() const {
                return tint;
            }

            void setTint(const core::Vec4f& newTint) {
                tint = newTint;
            }
        };


        class TextNode : public DrawableNode {
            Shape shape;
            core::Vec4f tint;
            core::Mat4f transform;
            Texture texture;
            Shader* shader;
            const Font* font;
            bool drawChildrenFirst;
        public:
            TextNode(const std::string& name,
                     const Font* font,
                     const std::string& text,
                     int size,
                     const core::Mat4f transform,
                     Shader* shader,
                     const core::Vec4f& tint = { 1, 1, 1, 1 }) :
                DrawableNode(name), font(font), tint(tint), shader(shader), transform(transform), drawChildrenFirst(false), texture(GL_TEXTURE_2D) {
                setText(text, size);
            }

            void setText(const std::string& text, int size) {
                Bitmap<uint8_t> textData = font->renderText(text, size);

                std::swap(shape, Shape::rectangle({ 0, 0 }, { (float)textData.getWidth(), (float)textData.getHeight() }));
                texture.setData(textData.getData(), textData.getWidth(), textData.getHeight(), GL_R8, GL_RED, GL_UNSIGNED_BYTE);
                texture.useRedAsAlpha();
            }

            void setDrawOrder(bool childrenFirst) {
                drawChildrenFirst = childrenFirst;
            }

            void draw(const core::Mat4f& t = core::Mat4f()) {
                core::Mat4f matrix = t * transform;

                if (drawChildrenFirst) {
                    DrawableNode::draw(matrix);
                }

                shader->apply();
                shader->setUniform("transform", matrix);
                shader->setUniform("tint", tint);
                shader->setUniform("image", texture);

                shape.draw();

                if (!drawChildrenFirst) {
                    DrawableNode::draw(matrix);
                }
            }
        };


    }
}
