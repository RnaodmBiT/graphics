#include <render_state.hpp>

#include <stack>

namespace tk {
    namespace graphics {

        class RenderState::Impl {
        public:
            std::stack<core::Mat4f> matrices;
            Shader* currentShader;

            Impl() :
                currentShader(nullptr) {
                matrices.push(core::Mat4f());
            }
        };

        RenderState::RenderState() {
            impl = new Impl();
        }

        RenderState::~RenderState() {
            delete impl;
        }

        void RenderState::pushMatrix() {
            impl->matrices.push(impl->matrices.top());
        }

        void RenderState::popMatrix() {
            impl->matrices.pop();
            tk_assert(impl->matrices.size(), "There must be at least one matrix on the stack.");
        }

        void RenderState::setMatrix(const core::Mat4f& matrix) {
            impl->matrices.top() = matrix;
        }

        void RenderState::transform(const core::Mat4f& matrix) {
            impl->matrices.top() *= matrix;
        }

        const core::Mat4f& RenderState::getTransform() const {
            return impl->matrices.top();
        }

        void RenderState::setShader(Shader* shader) {
            impl->currentShader = shader;
            shader->apply();
        }

        Shader* RenderState::getShader() const {
            return impl->currentShader;
        }

    }
}
