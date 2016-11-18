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
        protected:
            core::Mat4f transform;
        public:
            DrawableNode(const std::string& name) : core::Node<IDrawable>(name) { }
            virtual void draw(const core::Mat4f& matrix = core::Mat4f()) {
                core::Mat4f result = matrix * transform;
                for (auto& child : children) {
                    child->draw(result);
                }
            }

            const core::Mat4f& getTransform() const { return transform; }
            void setTransform(const core::Mat4f& matrix) { transform = matrix; }
        };


        class ShapeNode : public DrawableNode {
            Shape& shape;
            core::Vec4f tint;
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
                DrawableNode(name), shape(shape), tint(tint), texture(texture), shader(shader), drawChildrenFirst(false) {
                setTransform(transform);
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
            Texture texture;
            Shader* shader;
            const Font* font;
            bool drawChildrenFirst;
            core::Vec2i textSize;
        public:
            TextNode(const std::string& name,
                     const Font* font,
                     const std::string& text,
                     int size,
                     const core::Mat4f transform,
                     Shader* shader,
                     const core::Vec4f& tint = { 1, 1, 1, 1 }) :
                DrawableNode(name), font(font), tint(tint), shader(shader), drawChildrenFirst(false), texture(GL_TEXTURE_2D) {
                setTransform(transform);
                setText(text, size);
            }

            void setText(const std::string& text, int size) {
                Bitmap<uint8_t> textData = font->renderText(text, size);
                textSize = { textData.getWidth(), textData.getHeight() };

                std::swap(shape, Shape::rectangle({ 0, 0 }, { (float)textSize.x, (float)textSize.y }));
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

            const core::Vec2i& getSize() const {
                return textSize;
            }
        };


    }
}
