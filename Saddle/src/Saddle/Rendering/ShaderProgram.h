#pragma once

#include "../SaddleApi.h"

#include "Shader.h"

namespace Saddle {

    class SDL_API ShaderProgram {
    public:

        virtual ~ShaderProgram() = default;

        static ShaderProgram* createShaderProgram(Shader** shaders, int numShaders);

        virtual void use() = 0;

    protected:
    
        ShaderProgram() = default;

    };

}