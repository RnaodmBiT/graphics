#include <graphics.hpp>
#include <GL/glew.h> 

namespace tk {
    namespace graphics {

        bool initializeExtensions() {
            glewExperimental = true;
            return glewInit() == GLEW_OK;
        }

    }
}

