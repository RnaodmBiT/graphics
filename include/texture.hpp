#pragma once

#include <linkage.hpp>
#include <resource.hpp>
#include <vector.hpp>
#include <GL/glew.h>

namespace tk {
    namespace graphics {

        class TK_GRAPHICS Texture : public core::IResource {
            GLuint object;
            GLenum target;
            int textureWidth, textureHeight;

            void deleteTexture();

        public:

            enum WrapMode {
                Wrap = 0,
                Clamp = 1,
                Mirror = 2,
            };

            Texture(GLenum target);
            ~Texture();

            Texture(Texture&& move);
            void operator=(Texture&& move);

            static IResource* loadFromFile(const std::string& filename);

            void bind() const;

            template <class T>
            void setData(T* data, int width, int height, GLenum internalFormat, GLenum format, GLenum type) {
                textureWidth = width;
                textureHeight = height;

                bind();
                glTexImage2D(target, 0, internalFormat, width, height, 0, format, type, data);
                glGenerateMipmap(target);

                glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

                glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            }

            void setWrapMode(WrapMode x, WrapMode y);

            void useRedAsAlpha();

            core::Vec2i getSize() const;
        };

    }
}