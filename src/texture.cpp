#include <texture.hpp>
#include <algorithm>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

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

        Texture::Texture(Texture&& move) {
            *this = std::move(move);
        }

        void Texture::operator=(Texture&& move) {
            std::swap(object, move.object);
            std::swap(target, move.target);
        }

        core::IResource* Texture::loadFromFile(const std::string& filename) {
            int width, height, components;
            stbi_uc* data = stbi_load(filename.c_str(), &width, &height, &components, 4);
            tk_assert(data, core::format("Error loading image file %%", filename));

            Texture* texture = new Texture(GL_TEXTURE_2D);
            texture->setData(data, width, height, GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE);
            return texture;
        }

        void Texture::bind() const {
            glBindTexture(target, object);
        }

        void Texture::setWrapMode(WrapMode x, WrapMode y) {
            static GLenum modes[] = { GL_REPEAT, GL_CLAMP_TO_EDGE, GL_MIRRORED_REPEAT };

            bind();
            glTexParameteri(target, GL_TEXTURE_WRAP_S, modes[x]);
            glTexParameteri(target, GL_TEXTURE_WRAP_T, modes[y]);
        }

        void Texture::useRedAsAlpha() {
            bind();
            GLint swizzle[] = { GL_ONE, GL_ONE, GL_ONE, GL_RED };
            glTexParameteriv(target, GL_TEXTURE_SWIZZLE_RGBA, swizzle);
        }

        core::Vec2i Texture::getSize() const {
            return{ textureWidth, textureHeight };
        }

    }
}
