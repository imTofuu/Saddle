#pragma once

#include <Saddle/Layers/Layer.h>

namespace Saddle {

    class EditorLayer : public Layer {
    public:

        void onUpdate(const PassedArgs* args) override;

    private:

        void makeStatsWindow();

    };

}