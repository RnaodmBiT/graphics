#include <shader.hpp>
#include <GL/glew.h>
#include <cstdio>
#include <map>

#include <log.hpp>
#include <file.hpp>

namespace tk {
    namespace graphics {

        class Shader::Impl : public GLObject {
            std::map<std::string, int> uniforms;
            int textureUnit;

            void deleteProgram() {
                if (object) {
                    glDeleteProgram(object);
                    object = 0;
                }
            }


            void loadProgram(const std::string& vertexFile, const std::string& fragmentFile) {
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
                if (len > 1) {
                    glGetInfoLogARB(object, len, &size, &log[0]);
                    tk_debug(log);
                }

                tk_assert(linked, core::format("Error linking shaders: %% and %%", vertexFile, fragmentFile));

                findUniforms();
                tk_info(core::format("Built shader: (%%, %%)", vertexFile, fragmentFile));
            }


            GLuint loadShader(const std::string& file, GLenum type) {
                GLuint shader = glCreateShader(type);

                std::string sourceCode = core::readFile(file);
                tk_assert(sourceCode.size(), core::format("Error reading code from shader: %%", file));

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
                if (len > 1) {
                    glGetInfoLogARB(shader, len, &size, &log[0]);
                    tk_debug(log);
                }

                tk_assert(compiled, core::format("Error compiling shader: %%", file));

                return shader;
            }


            void findUniforms() {
                uniforms.clear();

                char nameBuffer[256];

                int numUniforms;
                glGetProgramiv(object, GL_ACTIVE_UNIFORMS, &numUniforms);

                for (int i = 0; i < numUniforms; ++i) {
                    glGetActiveUniformName(object, i, 256, nullptr, nameBuffer);
                    int location = glGetUniformLocation(object, nameBuffer);
                    uniforms.insert({ nameBuffer, location });
                }
            }

        public:
            Impl(const std::string& vertex, const std::string& fragment) {
                loadProgram(vertex, fragment);
            }

            ~Impl() {
                deleteProgram();
            }

            void apply() {
                glUseProgram(object);
                textureUnit = 0;
            }


            void setUniform(const std::string& name, int value) {
                glUniform1i(uniforms[name], value);
            }


            void setUniform(const std::string& name, float value) {
                glUniform1f(uniforms[name], value);
            }


            void setUniform(const std::string& name, const core::Vec2f& vec) {
                glUniform2fv(uniforms[name], 1, vec.data.data());
            }


            void setUniform(const std::string& name, const core::Vec3f& vec) {
                glUniform3fv(uniforms[name], 1, vec.data.data());
            }


            void setUniform(const std::string& name, const core::Vec4f& vec) {
                glUniform4fv(uniforms[name], 1, vec.data.data());
            }


            void setUniform(const std::string& name, const core::Mat4f& mat) {
                glUniformMatrix4fv(uniforms[name], 1, true, mat.data.data());
            }


            void setUniform(const std::string& name, const Texture& texture) {
                glActiveTexture(GL_TEXTURE0 + textureUnit);
                texture.bind();

                glUniform1i(uniforms[name], textureUnit++);
            }


            void clearTexture(const std::string& name) {
                glActiveTexture(GL_TEXTURE0 + textureUnit);
                glBindTexture(GL_TEXTURE_2D, 0);

                glUniform1i(uniforms[name], textureUnit++);
            }
        };


        Shader::Shader(const std::string& vertex, const std::string& fragment) {
            impl = new Impl(vertex, fragment);
        }


        Shader::~Shader() {
            delete impl;
        }


        core::IResource* Shader::loadFromFile(const std::string& vertex, const std::string& fragment) {
            return new Shader(vertex, fragment);
        }


        void Shader::apply() {
            impl->apply();
        }


        void Shader::setUniform(const std::string& name, int vec) {
            impl->setUniform(name, vec);
        }

        void Shader::setUniform(const std::string& name, float vec) {
            impl->setUniform(name, vec);
        }

        void Shader::setUniform(const std::string& name, const core::Vec2f& vec) {
            impl->setUniform(name, vec);
        }

        void Shader::setUniform(const std::string& name, const core::Vec3f& vec) {
            impl->setUniform(name, vec);
        }

        void Shader::setUniform(const std::string& name, const core::Vec4f& vec) {
            impl->setUniform(name, vec);
        }

        void Shader::setUniform(const std::string& name, const core::Mat4f& mat) {
            impl->setUniform(name, mat);
        }

        void Shader::setUniform(const std::string& name, const Texture& texture) {
            impl->setUniform(name, texture);
        }

        void Shader::clearTexture(const std::string& name) {
            impl->clearTexture(name);
        }

    }
}

