#pragma once
#include <node.hpp>
#include <log.hpp>

namespace tk {
    namespace graphics {

        class IDrawable {
        public:
            virtual ~IDrawable() { }
            virtual void draw() { }
        };


        class IDrawableNode : public core::Node<IDrawable> {
        public:
            IDrawableNode(const std::string& name) : core::Node<IDrawable>(name) { }
            virtual void draw() {
                for (auto& child : children) {
                    child->draw();
                }
            }
        };


        class TranslateNode : public IDrawableNode {
        public:
            TranslateNode(const std::string& name) : IDrawableNode(name) { }
            void draw() {
                tk_info(core::format("Hello World %%", name));

                IDrawableNode::draw();
            }
        };


    }
}
