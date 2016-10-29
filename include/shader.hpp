#pragma once
#include <string>
#include <GL/glew.h>
#include <detail/gl_object.hpp>
#include <linkage.hpp>
#include <vector.hpp>
#include <matrix.hpp>
#include <map>

namespace tk {
    namespace graphics {

        class TK_GRAPHICS Shader {
            class Impl;
            Impl* impl;

        public:

            Shader(const std::string& vertex, const std::string& fragment);
            ~Shader();

            void apply();

            void setUniform(const std::string& name, const core::Vec2f& vec);
            void setUniform(const std::string& name, const core::Vec3f& vec);
            void setUniform(const std::string& name, const core::Vec4f& vec);

            void setUniform(const std::string& name, const core::Mat4f& mat);
        };

    }
}
