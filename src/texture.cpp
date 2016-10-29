#pragma once

#include <texture.hpp>

namespace tk {
    namespace graphics {

        void Texture::deleteTexture() {
            glDeleteTextures(1, &object);
        }

        Texture::Texture(GLenum target) : target(target) { }

        Texture::~Texture() { }

        void Texture::bind() const {
            glBindTexture(target, object);
        }

    }
}