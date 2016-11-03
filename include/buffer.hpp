#pragma once

#include <linkage.hpp>
#include <detail/gl_object.hpp>

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

            Buffer(const Buffer&) = delete;
            void operator=(const Buffer&) = delete;

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