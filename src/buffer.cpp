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


        Buffer::Buffer(Buffer&& move) {
            *this = std::move(move);
        }


        void Buffer::operator=(Buffer&& move) {
            std::swap(object, move.object);
            std::swap(target, move.target);
            std::swap(usage, move.usage);
        }


        void Buffer::bind() const {
            glBindBuffer(target, object);
        }

    }
}