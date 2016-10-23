#pragma once
#include <utility>
#include <GL/glew.h>


namespace tk {
    namespace graphics {

        class GLObject {
        protected:
            GLuint object;
        public:
            GLObject() : object(0) { }
            virtual ~GLObject() { }

            GLObject(GLObject&& move) {
                std::swap(object, move.object);
            }

            GLObject& operator=(GLObject&& move) {
                std::swap(object, move.object);
            }

            GLObject(const GLObject& copy) = delete;
            GLObject& operator=(const GLObject& copy) = delete;
        };

    }
}