#pragma once
#include <utility>
#include <GL/glew.h>
#include <linkage.hpp>


namespace tk {
    namespace graphics {

        class TK_GRAPHICS GLObject {
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
                return *this;
            }

            GLObject(const GLObject& copy) = delete;
            GLObject& operator=(const GLObject& copy) = delete;
        };

    }
}