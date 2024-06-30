#include "SaddleLayers.h"

#include "../Logging/Logger.h"

#include "../Rendering/OpenGL/OpenGLVertexBuffer.h"
#include "../Rendering/OpenGL/OpenGLVertexArray.h"
#include "../Rendering/OpenGL/OpenGLShader.h"
#include "../Rendering/OpenGL/OpenGLShaderProgram.h"

#include "../Objects/Object.h"
#include "../Objects/SaddleComponents.h"

#include <glad/glad.h>

namespace Saddle {

    ImGuiContext* CoreGuiLayer::m_imguicontext = nullptr;

    void CoreGuiLayer::onLayerAdded(const PassedArgs* args) {
        bool success = true;
		IMGUI_CHECKVERSION();
		m_imguicontext = ImGui::CreateContext();
		ImGui::SetCurrentContext(m_imguicontext);
		success &= ImGui::GetCurrentContext() != 0;
		ImGui::StyleColorsDark();
        success &= ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)((*args)[0]), true);
        success &= ImGui_ImplOpenGL3_Init("#version 410 core");
		SDL_CORE_ASSERT(success, "Failed to load imgui");
        m_imguicontext = ImGui::CreateContext();
    }

    void CoreGuiLayer::onUpdate() {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void CoreGuiLayer::onLayerRemoved() {
        ImGui::DestroyContext(m_imguicontext);
    }


    void GameLayer::onLayerAdded(const PassedArgs* args) {
        bool success = true;
        GLADloadproc proc = (GLADloadproc)((*args)[0]);
        success &= gladLoadGLLoader(proc);
        SDL_CORE_ASSERT(success, "Failed to load glad");

        float verticies[] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f, 0.5f, 0.0f
        };

        VertexBuffer* vertexBuffer = VertexBuffer::createVertexBuffer(verticies, sizeof(verticies));
        vertexArray = VertexArray::createVertexArray(vertexBuffer, 1);

        const char* vertexShaderSource = "#version 410 core\n"
            "layout (location = 0) in vec3 aPos;\n"
            "void main()\n"
            "{\n"
            "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
            "}\0"; // The vertex shader is responsible for where the pixels are put on the screen.
                   // The fourth value of gl_Position is because it uses homogeneous coordinates. A
                   // value of 1 will cause the projection to be orthographic rather than perspective.
                   //
                   // location is the index of the vertex shader. 

        const char* fragmentShaderSource = "#version 410 core\n"
            "out vec4 FragColor;\n"
            "void main()\n"
            "{\n"
            "   FragColor = vec4(gl_FragCoord.x / 2560, gl_FragCoord.y / 1664, 1.0f, 1.0f);\n"
            "}\0"; // The fragment shader is responsible for the colour of pixels. 

        Shader* vertexShader = Shader::createShader(vertexShaderSource, ShaderType::VERTEX);
        Shader* fragmentShader = Shader::createShader(fragmentShaderSource, ShaderType::FRAGMENT);

        Shader* shaders[2] = {vertexShader, fragmentShader};

        shaderProgram = ShaderProgram::createShaderProgram(shaders, 2);

        delete vertexShader;
        delete fragmentShader;
    }

    void GameLayer::onUpdate() {
        /*std::vector<SpriteComponent*> sprites = Object::getAllComponents<SpriteComponent>();
        for(SpriteComponent * sprite : sprites) {
            if(&sprite->getObject().getScene() == &Scene::getActiveScene()) {
                
            }
        }*/
        shaderProgram->use();
        vertexArray->bind();
        glDrawArrays(GL_TRIANGLES, 0, 3);

    }

}