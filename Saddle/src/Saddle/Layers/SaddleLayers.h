#pragma once

#include "../SaddleApi.h"
#include "Layer.h"

namespace ImGui {
    class ImGuiContext;
}

namespace Saddle {

    class SDL_API CoreGuiLayer : public Layer {
    public:

        void onLayerAdded(const PassedArgs* args) override;
        void onUpdate() override;
        void onLateUpdate() override;
        void onLayerRemoved() override;
    
    private:

        static ImGui::ImGuiContext* m_imguicontext;
    };

    class SDL_API GameLayer : public Layer {
    public:

        void onLayerAdded(const PassedArgs* args) override;
        void onUpdate() override;
    };

}