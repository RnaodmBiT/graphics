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


        class IDrawableNode : public core::Node<IDrawable> {
        public:
            IDrawableNode(const std::string& name) : core::Node<IDrawable>(name) { }
            virtual void draw(const core::Mat4f& transform = core::Mat4f()) {
                for (auto& child : children) {
                    child->draw(transform);
                }
            }
        };


        class ShapeNode : public IDrawableNode {
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
                IDrawableNode(name), shape(shape), tint(tint), texture(texture), shader(shader), transform(transform), drawChildrenFirst(false) { }

            void setDrawOrder(bool childrenFirst) {
                drawChildrenFirst = childrenFirst;
            }

            void draw(const core::Mat4f& t = core::Mat4f()) {
                core::Mat4f matrix = t * transform;

                if (drawChildrenFirst) {
                    IDrawableNode::draw(matrix);
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
                    IDrawableNode::draw(matrix);
                }
            }
        };


    }
}
