#include "SaddleLayers.h"

#include "../Logging/Logger.h"

#include <glad/glad.h>

#include "../Objects/Object.h"
#include "../Objects/SaddleComponents.h"

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
        success &= ImGui_ImplOpenGL3_Init("#version 150");
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
    }

    void GameLayer::onUpdate() {
        /*std::vector<SpriteComponent*> sprites = Object::getAllComponents<SpriteComponent>();
        for(SpriteComponent * sprite : sprites) {
            if(&sprite->getObject().getScene() == &Scene::getActiveScene()) {
                
            }
        }*/


        // SECTION 1: DATA CREATION

        float verticies[] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f, 0.5f, 0.0f
        }; // Creates an array of vertex position. Values are in normalized screen space coordinates.

        unsigned int vbo; // This is the vertex buffer object. It is the OpenGL id of the verticies array.
        glGenBuffers(1, &vbo); // This creates the buffers. 1 is the size of buffers and &vbo is an array of the location
                               // where the objects are stored. Since the size is only 1, vbo can be a single int.
            
        glBindBuffer(GL_ARRAY_BUFFER, vbo); // This binds the buffer to GL_ARRAY_BUFFER which means it is the currently
                                            // used GL_ARRAY_BUFFER on the gpu. Only a single buffer can be bound to
                                            // a location at a time.

        glBufferData(GL_ARRAY_BUFFER, 
                     sizeof(verticies), 
                     verticies, 
                     GL_STATIC_DRAW); // This populates the array with data. There are 3 options for the last argument:
                                      // GL_STATIC_DRAW : The data is set once and used multiple times.
                                      // GL_DYNAMIC_DRAW : The data is changed frequently and used multiple times.
                                      // GL_STREAM_DRAW : The data is set once and not used many times.

        // This creates the data to be drawn.

        // SECTION 2: SHADERS

        const char* vertexShaderSource = "#version 330 core\n"
            "layout (location = 0) in vec3 aPos;\n"
            "void main()\n"
            "{\n"
            "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
            "}\0"; // The vertex shader is responsible for where the pixels are put on the screen.
                   // The fourth value of gl_Position is because it uses homogeneous coordinates. A
                   // value of 1 will cause the projection to be orthographic rather than perspective.
                   //
                   // location is the index of the vertex shader. 

        unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER); // This allocates space for the
                                                                      // vertex shader.

        glShaderSource(vertexShader, 
                       1, 
                       &vertexShaderSource, 
                       NULL); // This populates the vertex shader with data. 1 is the number of strings
                              // being passed, which is only the 1 shader.
        glCompileShader(vertexShader); // This attempts to compile the shader.

        int compilationSuccess;
        char infolog[512];
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &compilationSuccess); // This puts the result of
                                                                             // the compilation into 
                                                                             // compilationSuccess.
        if (!compilationSuccess) { // This verifies the success of the shader compilation.
            glGetShaderInfoLog(vertexShader, 512, NULL, infolog);
            Logger::getCoreLogger().log("Vertex shader failed to compile.", Logger::FATAL);
            Logger::getCoreLogger().log(infolog, Logger::DEBUG);
        }

        const char* fragmentShaderSource = "#version 330 core\n"
            "out vec4 FragColor;\n"
            "void main()\n"
            "{\n"
            "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
            "}\0"; // The fragment shader is responsible for the colour of pixels. 

        unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragmentShader);

        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &compilationSuccess);
        if(!compilationSuccess) {
            glGetShaderInfoLog(fragmentShader, 512, NULL, infolog);
            Logger::getCoreLogger().log("Fragment shader failed to compile.", Logger::FATAL);
            Logger::getCoreLogger().log(infolog, Logger::DEBUG);
        }

        unsigned int shaderProgram = glCreateProgram(); // Creates a shader program which is used for
                                                        // for linking the shaders together.

        glAttachShader(shaderProgram, vertexShader);   // |
        glAttachShader(shaderProgram, fragmentShader); //  -> These attach the shaders to the created program.
        glLinkProgram(shaderProgram); // These link all the attached shaders together.

        int linkSuccess;
        glGetShaderiv(shaderProgram, GL_LINK_STATUS, &linkSuccess);
        if(!linkSuccess) {
            glGetShaderInfoLog(shaderProgram, 512, NULL, infolog);
            Logger::getCoreLogger().log("Shaders failed to link into program.", Logger::FATAL);
            Logger::getCoreLogger().log(infolog, Logger::DEBUG);
        }

        // SECTION 3: VAOs

        unsigned int vao; // This is the vertex array object. 
        glGenVertexArrays(1, &vao); // 1 is the number of arrays.
        
        glBindVertexArray(vao); // Bind the array
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 
                              3, 
                              GL_FLOAT, 
                              GL_FALSE, 
                              3 * sizeof(float), 
                              (void*)0); // 0 is the location set in the vertex shader. 3 is the size in elements of
                                         // a vertex. GL_FLOAT specifies the type of values in the vertex. GL_FALSE 
                                         // specifies if the data should be normalised. The next argument is the stride
                                         // which is the size of 1 vertex. The last argument is the offset of where
                                         // the data starts in the buffer.
        glEnableVertexAttribArray(0); // Same index as last call.

        glUseProgram(shaderProgram); // This tells OpenGL to use the program.
        glDeleteShader(vertexShader); //  |
        glDeleteShader(fragmentShader); // -> The shaders are no longer needed and can be deleted.
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);

    }

}