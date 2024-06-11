#include "SaddleLayers.h"

#include "../Logging/Logger.h"

#include <glad/glad.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace Saddle {

    ImGui::ImGuiContext* CoreGuiLayer::m_imguicontext = nullptr;

    void CoreGuiLayer::onLayerAdded(const PassedArgs* args) {
        bool success = true;
		IMGUI_CHECKVERSION();
		m_imguicontext = ImGui::CreateContext();
		ImGui::SetCurrentContext(m_imguicontext);
		success &= ImGui::GetCurrentContext() != 0;
		ImGui::StyleColorsDark();
        success &= ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)((*args)[0]), true);
        success &= ImGui_ImplOpenGL3_Init();
		SDL_CORE_ASSERT(success, "Failed to load imgui");
        m_imguicontext = ImGui::CreateContext();
    }

    void CoreGuiLayer::onUpdate() {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void CoreGuiLayer::onLateUpdate() {
        ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
    }

    void CoreGuiLayer::onLayerRemoved() {
        ImGui::DestroyContext(m_imguicontext);
    }


    void GameLayer::onLayerAdded(const PassedArgs* args) {
        bool success = true;
        GLADloadproc proc = *(GLADloadproc*)(*args)[0];
        success &= gladLoadGLLoader(proc);
        SDL_CORE_ASSERT(success, "Failed to load glad");
    }

}