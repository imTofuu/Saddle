#pragma once

#include "../../SaddleApi.h"

#include "../Shader.h"

namespace Saddle {

    class OpenGLShader : public Shader {
    public:

        OpenGLShader(const char* source, ShaderType type);

        unsigned int getShaderPointer() { return shader; } // seg fault

    private:

        unsigned int shader = 0;

    };

}