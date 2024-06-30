#include "OpenGLShaderProgram.h"

#include "../../Logging/Logger.h"

#include "OpenGLShader.h"

#include <glad/glad.h>

namespace Saddle {

    OpenGLShaderProgram::OpenGLShaderProgram(Shader** shaders, int numShaders) {

        shaderProgram = glCreateProgram();

        for(int i = 0; i < numShaders; i++) {
            //SDL_CORE_ASSERT(dynamic_cast<OpenGLShader*>(&shaders[i]) != 0, "Passed shader is not OpenGL type");
            Shader* shader = shaders[i];
            OpenGLShader* openGLShader = (OpenGLShader*)shader;
            glAttachShader(shaderProgram, openGLShader->getShaderPointer());
        }

        glLinkProgram(shaderProgram);

        int linkSuccess;
        char infolog[512] = {};
        glGetShaderiv(shaderProgram, GL_LINK_STATUS, &linkSuccess);
        if(!linkSuccess) {
            glGetShaderInfoLog(shaderProgram, 512, NULL, infolog);
            Logger::getCoreLogger().log("Shaders failed to link into program.", Logger::FATAL);
            Logger::getCoreLogger().log(infolog, Logger::DEBUG);
        }

        for(int i = 0; i < numShaders; i++) {
            glDeleteShader(((OpenGLShader*)&shaders[i])->getShaderPointer());
        }

    }

    void OpenGLShaderProgram::use() {
        glUseProgram(shaderProgram);
    }

}