#pragma once

#include <linkage.hpp>
#include <GL/glew.h>

namespace tk {
    namespace graphics {

        class TK_GRAPHICS Buffer {
            GLuint object;
            GLenum target, usage;

            void deleteBuffer();

        public:

            Buffer() : object(0) { }
            Buffer(GLenum target, GLenum usage);
            ~Buffer();

            Buffer(Buffer&& move);
            void operator=(Buffer&& move);

            void bind() const;
            
            template <class T>
            void setData(T* data, int count) {
                bind();
                glBufferData(target, sizeof(T) * count, data, usage);
            }
        };

    }
}