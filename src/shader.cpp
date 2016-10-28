#include <shader.hpp>
#include <GL/glew.h>
#include <cstdio>

#include <file.hpp>

namespace tk {
    namespace graphics {

        void Shader::deleteProgram() {
            if (object) {
                glDeleteProgram(object);
                object = 0;
            }
        }


        void Shader::loadProgram(const std::string& vertexFile, const std::string& fragmentFile) {
            deleteProgram();

            object = glCreateProgram();

            glAttachShader(object, loadShader(vertexFile, GL_VERTEX_SHADER));
            glAttachShader(object, loadShader(fragmentFile, GL_FRAGMENT_SHADER));

            glLinkProgram(object);

            GLint linked;
            glGetProgramiv(object, GL_LINK_STATUS, &linked);
            GLint len = 0;
            GLsizei size = 0;
            glGetProgramiv(object, GL_INFO_LOG_LENGTH, &len);
            std::string log(len, ' ');
            if (len > 1 && !linked) {
                glGetInfoLogARB(object, len, &size, &log[0]);
                printf("%s\n", log.c_str());
            }

            findUniforms();
        }


        GLuint Shader::loadShader(const std::string& file, GLenum type) {
            GLuint shader = glCreateShader(type);

            std::string sourceCode = core::readFile(file);
            const char* sourcePtr = sourceCode.data();
            GLint sourceLength = (GLint)sourceCode.size();

            glShaderSource(shader, 1, &sourcePtr, &sourceLength);
            glCompileShader(shader);

            GLint compiled;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
            GLint len = 0;
            GLsizei size = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
            std::string log(len, ' ');
            if (len > 1 && !compiled) {
                glGetInfoLogARB(shader, len, &size, &log[0]);
                printf("%s\n", log.c_str());
            }

            return shader;
        }


        void Shader::findUniforms() {
            uniforms.clear();

            char nameBuffer[256];

            int numUniforms;
            glGetProgramiv(object, GL_ACTIVE_UNIFORMS, &numUniforms);

            for (int i = 0; i < numUniforms; ++i) {
                glGetActiveUniformName(object, i, 256, nullptr, nameBuffer);
                int location = glGetUniformLocation(object, nameBuffer);
                uniforms.insert({ nameBuffer, location });

                printf("Uniform (%i): %s\n", location, nameBuffer);
            }
        }


        Shader::Shader(const std::string& vertex, const std::string& fragment) {
            loadProgram(vertex, fragment);
        }


        Shader::~Shader() {
            deleteProgram();
        }


        void Shader::apply() {
            glUseProgram(object);
        }


        void Shader::setUniform(const std::string& name, const core::Vec2f& vec) {
            glUniform2fv(uniforms[name], 1, vec.data.data());
        }


        void Shader::setUniform(const std::string& name, const core::Vec3f& vec) {
            glUniform3fv(uniforms[name], 1, vec.data.data());
        }


        void Shader::setUniform(const std::string& name, const core::Vec4f& vec) {
            glUniform4fv(uniforms[name], 1, vec.data.data());
        }


        void Shader::setUniform(const std::string& name, const core::Mat4f& mat) {
            glUniformMatrix4fv(uniforms[name], 1, true, mat.data.data());
        }

    }
}
