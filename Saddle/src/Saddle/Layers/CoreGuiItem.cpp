#include "CoreGuiItem.h"

#include <imgui.h>

namespace Saddle {

    CoreGuiItem::CoreGuiItem(const char* name) { ImGui::Begin(name); }
    CoreGuiItem::~CoreGuiItem() { ImGui::End(); }
    
    void CoreGuiItem::text(const char* text) { ImGui::Text(text); }
    void CoreGuiItem::text(const std::string& text) { ImGui::Text(text.c_str()); }

    bool CoreGuiItem::button(const char* text) { return ImGui::Button(text); }
    bool CoreGuiItem::button(const std::string& text) { return button(text.c_str()); }

    void CoreGuiItem::slider(const char* text, float* location, float min, float max) { ImGui::SliderFloat(text, location, min, max); }
    void CoreGuiItem::slider(const std::string& text, float* location, float min, float max) { slider(text.c_str(), location, min, max); }
    void CoreGuiItem::slider(const char* text, int* location, int min, int max) { ImGui::SliderInt(text, location, min, max); }
    void CoreGuiItem::slider(const std::string& text, int* location, int min, int max) { slider(text.c_str(), location, min, max); }

    void CoreGuiItem::end() { ImGui::End(); }

}