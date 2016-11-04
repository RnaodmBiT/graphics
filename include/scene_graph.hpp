#pragma once
#include <node.hpp>
#include <log.hpp>

namespace tk {
    namespace graphics {

        class IRenderNode : public core::Node<IRenderNode> {
        public:
            IRenderNode(const std::string& name) : core::Node<IRenderNode>(name) { }
            virtual ~IRenderNode() { }
            virtual void draw() {
                for (auto& child : children) {
                    child->draw();
                }
            }
        };


        class TranslateNode : public IRenderNode {
        public:
            TranslateNode(const std::string& name) : IRenderNode(name) { }
            void draw() {
                tk_info(core::format("Hello World %%", name));

                IRenderNode::draw();
            }
        };


    }
}
