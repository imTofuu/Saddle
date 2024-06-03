#include "ImGuiLayer.h"

#include "../Logging/Logger.h"

#include <string>

namespace Saddle {

    ImGuiContext* ImGuiLayer::m_imguicontext = nullptr;

    void ImGuiLayer::onLayerAdded(const PassedArgs* args) {
        bool success = true;
        IMGUI_CHECKVERSION();
        SDL_CORE_ASSERT(success, "Failed to initialise imgui");
    }

    void ImGuiLayer::onLayerRemoved(const PassedArgs* args) {
        ImGui::DestroyContext(m_imguicontext);
    }

    void ImGuiLayer::onUpdate(const PassedArgs* args) {
        ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

        for(auto & imguiobject : m_imguiobjects) {
            imguiobject.first(imguiobject.second);
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

}