#pragma once

#include <Saddle/Layers/Layer.h>
#include <Saddle/Windows/Window.h>

namespace Saddle {

    class EditorLayer : public Layer {
    public:

        void onUpdate(const PassedArgs* args) override;

    private:

        int* m_width = new int(500);
        int* m_height = new int(500);

        Window* m_window = new Window("Saddle Editor", 2560, 1664, SaddleWindowFlags_IsBorderless);

        void makeDebugWindow();
        void makeStatsWindow();

    };

}