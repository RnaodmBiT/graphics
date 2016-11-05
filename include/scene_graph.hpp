#pragma once
#include <node.hpp>
#include <log.hpp>
#include <render_state.hpp>
#include <shape.hpp>

namespace tk {
    namespace graphics {

        class IDrawable {
        public:
            virtual ~IDrawable() { }
            virtual void draw(RenderState& state) { }
        };


        class IDrawableNode : public core::Node<IDrawable> {
        public:
            IDrawableNode(const std::string& name) : core::Node<IDrawable>(name) { }
            virtual void draw(RenderState& state) {
                for (auto& child : children) {
                    child->draw(state);
                }
            }
        };


        class TransformNode : public IDrawableNode {
            core::Mat4f matrix;
        public:
            TransformNode(const std::string& name, const core::Mat4f& m = core::Mat4f()) : IDrawableNode(name), matrix(m) { }
            void draw(RenderState& state) {
                state.pushMatrix();
                state.transform(matrix);

                IDrawableNode::draw(state);
                state.popMatrix();
            }

            core::Mat4f& getMatrix() {
                return matrix;
            }
        };


        class ShapeNode : public IDrawableNode {
            Shape& shape;
            core::Vec4f tint;
        public:
            ShapeNode(const std::string& name, Shape& shape, const core::Vec4f& tint = { 1, 1, 1, 1 }) : IDrawableNode(name), shape(shape), tint(tint) { }
            void draw(RenderState& state) {
                state.getShader()->setUniform("transform", state.getTransform());
                state.getShader()->setUniform("tint", tint);
                shape.draw();

                IDrawableNode::draw(state);
            }
        };


    }
}
