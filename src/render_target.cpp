#include <render_target.hpp>

namespace tk {
    namespace graphics {

        RenderTarget::RenderTarget(int target) : target(target) {
        }


        RenderTarget RenderTarget::getFrameBuffer() {
            return RenderTarget(0);
        }

    }
}

