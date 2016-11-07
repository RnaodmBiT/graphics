#include <texture.hpp>

namespace tk {
    namespace graphics {

        void Texture::deleteTexture() {
            glDeleteTextures(1, &object);
        }

        Texture::Texture(GLenum target) : target(target) {
            glGenTextures(1, &object);
        }

        Texture::~Texture() { 
            deleteTexture();
        }

        void Texture::bind() const {
            glBindTexture(target, object);
        }

        void Texture::useRedAsAlpha() {
            bind();
            GLint swizzle[] = { GL_ONE, GL_ONE, GL_ONE, GL_RED };
            glTexParameteriv(target, GL_TEXTURE_SWIZZLE_RGBA, swizzle);
        }

    }
}
