#pragma once

#include "../../SaddleApi.h"

#include "../ShaderProgram.h"

namespace Saddle {

    class SDL_API OpenGLShaderProgram : public ShaderProgram {
    public:

        OpenGLShaderProgram(Shader** shaders, int numShaders);

        void use() override;

    private:

        unsigned int shaderProgram;

    };

}