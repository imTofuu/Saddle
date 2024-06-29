#include "EditorLayer.h"

#include <Saddle/Layers/CoreGuiItem.h>
#include <Saddle/Windows/Window.h>

#include <iomanip>

namespace Saddle {

    void EditorLayer::onUpdate(const PassedArgs* args) {
        makeStatsWindow();
        makeDebugWindow();
    }

    void EditorLayer::makeDebugWindow() {
        CoreGuiItem item("Debug");
        item.text("ergsdf");
        item.slider("width", m_width, 1, 2560);
        item.slider("height", m_height, 1, 1664);
        m_window->resize(*m_width, *m_height);
        if(item.button("close")) {
            m_window->close();
            exit(0);
        }
        item.text("anything else");
        item.text("fgrhtjyhgfsedgh");
        item.text("helo");
    }


    void EditorLayer::makeStatsWindow() {
        CoreGuiItem stats("Statistics");
        const Time& time = Window::getActiveWindow()->getTimeInfo();
        stats.text(std::to_string(time.delta) + "ms     (Frame time)");
        stats.text(std::to_string(time.avg_delta) + "ms     (Frame time avg)");
        stats.text(std::to_string(time.fps) + "fps      (Average fps)");
        stats.text(std::to_string(time.fls) + "fps      (Frames last second)");
    }
        
}