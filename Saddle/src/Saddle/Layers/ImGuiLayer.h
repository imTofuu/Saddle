#pragma once

#include "../SaddleApi.h"
#include "Layer.h"

#include <unordered_map>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace Saddle {

    class SDL_API ImGuiLayer : public Layer {
    public:

        void onLayerAdded(const PassedArgs* args) override;
        void onLayerRemoved(const PassedArgs* args) override;
        void onUpdate(const PassedArgs* args) override;

        void addImGuiObjectForFrame(void (*fn)(const PassedArgs*), PassedArgs* args) { m_imguiobjects.emplace(fn, args); }
    
    private:
        ImGuiContext* m_imguicontext;

        std::unordered_map<void (*)(const PassedArgs*), PassedArgs*> m_imguiobjects;
    };

}