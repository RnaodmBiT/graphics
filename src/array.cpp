#include <array.hpp>


namespace tk {
    namespace graphics {

        void Array::deleteArray() {
            if (object) {
                glDeleteVertexArrays(1, &object);
                object = 0;
            }
        }


        Array::Array(GLenum topology) : topology(topology), attributeCount(0) {
            glGenVertexArrays(1, &object);
        }


        Array::~Array() {
            deleteArray();
        }


        Array::Array(Array&& move) {
            *this = std::move(move);
        }


        void Array::operator=(Array&& move) {
            std::swap(object, move.object);
            std::swap(topology, move.topology);
            std::swap(attributeCount, move.attributeCount);
        }


        void Array::bind() const {
            glBindVertexArray(object);
        }


        void Array::addBuffer(const Buffer& buffer, GLenum dataType, int vectorSize) {
            bind();
            buffer.bind();

            glEnableVertexAttribArray(attributeCount);
            glVertexAttribPointer(attributeCount++, vectorSize, dataType, GL_FALSE, 0, 0);
        }


        void Array::draw(uint32_t offset, uint32_t count) const {
            bind();
            glDrawArrays(topology, offset, count);
        }

    }
}