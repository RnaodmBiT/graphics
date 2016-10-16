#pragma once
#include <GL/glew.h>

namespace tk {
    namespace graphics {

        class RenderTarget {
            int target;

            RenderTarget(int target);

        public:

            static RenderTarget getFrameBuffer();

            void apply();
        };

    }
}

