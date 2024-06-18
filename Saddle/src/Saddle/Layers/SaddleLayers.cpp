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
        success &= ImGui_ImplOpenGL3_Init("#version 130");
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
        std::vector<SpriteComponent*> sprites = Object::getAllComponents<SpriteComponent>();
        for(SpriteComponent * sprite : sprites) {
            if(&sprite->getObject().getScene() == &Scene::getActiveScene()) {
                
            }
        }
    }

}