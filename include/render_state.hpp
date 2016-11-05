#pragma once
#include <linkage.hpp>
#include <matrix.hpp>
#include <shader.hpp>

namespace tk {
    namespace graphics {

        class TK_GRAPHICS RenderState {
            class Impl;
            Impl* impl;

        public:

            RenderState(); 
            ~RenderState();

            // Matrix Transforms
            void pushMatrix();
            void popMatrix();

            void setMatrix(const core::Mat4f& matrix);
            void transform(const core::Mat4f& matrix);

            const core::Mat4f& getTransform() const;

            // Shader
            void setShader(Shader* shader);
            Shader* getShader() const;

        };

    }
}
