#pragma once

// TODO: Add includes for all of the state types. E.g. shaders and textures.
#include <render_target.hpp>

namespace tk {
    namespace graphics {

        class RenderState {
            RenderTarget* target;

        public:

            RenderState(); 

            void setRenderTarget(RenderTarget* target);

        };

    }
}
