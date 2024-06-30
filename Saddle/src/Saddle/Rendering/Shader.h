#pragma once

#include "../SaddleApi.h"

namespace Saddle {

    enum SDL_API ShaderType {
        VERTEX,
        FRAGMENT
    };

    class SDL_API Shader {
    public:

        virtual ~Shader() = default;

        static Shader* createShader(const char* source, ShaderType type);
    
    protected:

        Shader() = default;

    };

}