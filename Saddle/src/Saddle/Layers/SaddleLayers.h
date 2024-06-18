#pragma once

#include "../SaddleApi.h"
#include "Layer.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace Saddle {

    class SDL_API CoreGuiLayer : public Layer {
    public:

        void onLayerAdded(const PassedArgs* args) override;
        void onUpdate() override;
        void onLayerRemoved() override;

        static const ImGuiContext* getImGuiContext() { return m_imguicontext; }
    
    private:

        static ImGuiContext* m_imguicontext;
    };

    class SDL_API GameLayer : public Layer {
    public:

        void onLayerAdded(const PassedArgs* args) override;
        void onUpdate() override;
    };

}