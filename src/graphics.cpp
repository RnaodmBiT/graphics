#include <graphics.hpp>
#include <GL/glew.h> 

namespace tk {
    namespace graphics {

        bool initialize() {
            if (!initializeExtensions()) {
                return false;
            }

            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            uint8_t data[] = { 255, 255, 255, 255 };
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

            return true;
        }

        bool initializeExtensions() {
            glewExperimental = true;
            return glewInit() == GLEW_OK;
        }

        void clipRectangle(const core::Vec2f& position, const core::Vec2f& size) {
            int viewport[4] = { 0 };
            glGetIntegerv(GL_VIEWPORT, viewport);

            glEnable(GL_SCISSOR_TEST);
            glScissor((int)position.x, viewport[3] - (int)position.y - (int)size.y, (int)size.x, (int)size.y);
        }

        void clearClip() {
            glDisable(GL_SCISSOR_TEST);
        }

    }
}

