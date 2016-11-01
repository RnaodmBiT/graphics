#pragma once

#include <linkage.hpp>
#include <detail/gl_object.hpp>

namespace tk {
    namespace graphics {

        class TK_GRAPHICS Texture : public GLObject {
            GLenum target;

            void deleteTexture();

        public:

            Texture(GLenum target);
            ~Texture();

            void bind() const;

            template <class T>
            void setData(T* data, int width, int height, GLenum internalFormat, GLenum format, GLenum type) {
                bind();
                glTexImage2D(target, 0, internalFormat, width, height, 0, format, type, data);
                glGenerateMipmap(target);

                glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

                glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            }
        };

    }
}