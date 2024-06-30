#include "OpenGLShader.h"

#include "../../Logging/Logger.h"

#include <glad/glad.h>

namespace Saddle {

    OpenGLShader::OpenGLShader(const char* source, ShaderType type) {
        switch(type) {
            case VERTEX:
                shader = glCreateShader(GL_VERTEX_SHADER);
                break;
            case FRAGMENT:
                shader = glCreateShader(GL_FRAGMENT_SHADER);
                break;
            default:
                SDL_CORE_ASSERT(false, "Unsupported shader type");
        }
        
        glShaderSource(shader, 1, &source, NULL);
        glCompileShader(shader);

        int compilationSuccess = 0;
        char infolog[512] = {};
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compilationSuccess);
        if(!compilationSuccess) {
            glGetShaderInfoLog(shader, 512, NULL, infolog);
            Logger::getCoreLogger().log("Shader failed to compile.", Logger::ERROR);
            Logger::getCoreLogger().log("Shader source:", Logger::DEBUG);
            Logger::getCoreLogger().log(source, Logger::DEBUG);
            Logger::getCoreLogger().log("infolog: ", Logger::DEBUG);
            Logger::getCoreLogger().log(infolog, Logger::DEBUG);
            SDL_CORE_ASSERT(false, "");
        }
    }

}