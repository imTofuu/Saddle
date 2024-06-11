#include "CoreGuiItem.h"

#include <imgui.h>

namespace Saddle {

    CoreGuiItem::CoreGuiItem(const char* name) { ImGui::Begin(name); }
    CoreGuiItem::~CoreGuiItem() { ImGui::End(); }
    
    void CoreGuiItem::text(const char* text) { ImGui::Text(text); }
    void CoreGuiItem::text(const std::string& text) { ImGui::Text(text.c_str()); }

    void CoreGuiItem::end() { ImGui::End(); }

}