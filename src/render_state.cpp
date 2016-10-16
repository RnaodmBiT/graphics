#include <render_state.hpp>

namespace tk {
    namespace graphics {

        RenderState::RenderState() :
            target(nullptr) {
        }


        void RenderState::setRenderTarget(RenderTarget* rt) {
            target = rt;
        }

    }
}
