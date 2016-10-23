#include <buffer.hpp>


namespace tk {
    namespace graphics {

        void Buffer::deleteBuffer() {
            if (object) {
                glDeleteBuffers(1, &object);
                object = 0;
            }
        }


        Buffer::Buffer(GLenum target, GLenum usage) : target(target), usage(usage) {
            glGenBuffers(1, &object);
        }


        Buffer::~Buffer() {
            deleteBuffer();
        }


        void Buffer::bind() const {
            glBindBuffer(target, object);
        }

    }
}