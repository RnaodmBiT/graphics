#pragma once
#include <linkage.hpp>
#include <detail/gl_object.hpp>
#include <buffer.hpp>
#include <vector>
#include <cstdint>

namespace tk {
    namespace graphics {

        class TK_GRAPHICS Array {
            GLuint object;
            GLenum topology;
            int attributeCount;

            void deleteArray();

        public:

            Array() : object(0) { }
            Array(GLenum topology);
            ~Array();

            Array(const Array&) = delete;
            void operator=(const Array&) = delete;

            Array(Array&& move);
            void operator=(Array&& move);

            void bind() const;
            void addBuffer(const Buffer& buffer, GLenum dataType, int vectorSize);
            void draw(uint32_t offset, uint32_t count) const;
        };
    }
}