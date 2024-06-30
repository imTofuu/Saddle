#include "ShaderProgram.h"

#include "OpenGL/OpenGLShaderProgram.h"

namespace Saddle {

    ShaderProgram* ShaderProgram::createShaderProgram(Shader** shaders, int numShaders) {
        return new OpenGLShaderProgram(shaders, numShaders);
    }

}