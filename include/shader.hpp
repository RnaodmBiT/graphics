#pragma once
#include <string>
#include <GL/glew.h>
#include <detail/gl_object.hpp>

namespace tk {
    namespace graphics {

        class Shader : public GLObject {
            void loadProgram(const std::string& vertex, const std::string& fragment);
            GLuint loadShader(const std::string& file, GLenum type);

            void deleteProgram();

        public:

            Shader(const std::string& vertex, const std::string& fragment);
            ~Shader();
        };

    }
}