#include "EditorLayer.h"

#include <Saddle/Layers/CoreGuiItem.h>
#include <Saddle/Windows/Window.h>

#include <iomanip>

namespace Saddle {

    void EditorLayer::onUpdate(const PassedArgs* args) {
        makeStatsWindow();
    }


    void EditorLayer::makeStatsWindow() {
        CoreGuiItem stats("Statistics");
        const Time& time = Window::getActiveWindow()->getTimeInfo();
        stats.text(std::to_string((float)((int)(time.delta * 100)) / 100) + "ms     (Frame time)");
        stats.text(std::to_string(time.avg_delta) + "ms     (Frame time avg)");
        stats.text(std::to_string(time.fps) + "fps      (Average fps)");
        stats.text(std::to_string(time.fls) + "fps      (Frames last second)");
    }
        
}