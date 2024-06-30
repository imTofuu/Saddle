#include "Shader.h"

#include "OpenGL/OpenGLShader.h"

namespace Saddle {

    Shader* Shader::createShader(const char* source, ShaderType type) {
        return new OpenGLShader(source, type);
    }

}