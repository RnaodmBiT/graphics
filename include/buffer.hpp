#pragma once

#include <linkage.hpp>
#include <detail/gl_object.hpp>

namespace tk {
    namespace graphics {

        class TK_GRAPHICS Buffer : public GLObject {
            GLenum target, usage;

            void deleteBuffer();

        public:

            Buffer(GLenum target, GLenum usage);
            ~Buffer();

            void bind() const;
            
            template <class T>
            void setData(T* data, int count) {
                bind();
                glBufferData(target, sizeof(T) * count, data, usage);
            }
        };

    }
}