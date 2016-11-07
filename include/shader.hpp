#pragma once
#include <string>
#include <GL/glew.h>
#include <detail/gl_object.hpp>
#include <linkage.hpp>
#include <vector.hpp>
#include <matrix.hpp>
#include <texture.hpp>
#include <resource.hpp>

namespace tk {
    namespace graphics {

        class TK_GRAPHICS Shader : public core::IResource {
            class Impl;
            Impl* impl;

        public:

            Shader(const std::string& vertex, const std::string& fragment);
            ~Shader();

            static core::IResource* loadFromFile(const std::string& vertex, const std::string& fragment);

            void apply();

            void setUniform(const std::string& name, int value);
            void setUniform(const std::string& name, float value);

            void setUniform(const std::string& name, const core::Vec2f& vec);
            void setUniform(const std::string& name, const core::Vec3f& vec);
            void setUniform(const std::string& name, const core::Vec4f& vec);

            void setUniform(const std::string& name, const core::Mat4f& mat);
            
            void setUniform(const std::string& name, const Texture& texture);

            void clearTexture(const std::string& name);
        };

    }
}
