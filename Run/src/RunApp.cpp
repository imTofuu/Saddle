#include <Saddle.h>

#include <Saddle/Logging/Logger.h>
#include <Saddle/Windows/Window.h>

#include <Saddle/Layers/LayerManager.h>
#include <Saddle/Layers/ImGuiLayer.h>


void Saddle::Start() {

	Window* window = new Window("Saddle Editor", 1280, 720, 
		SaddleWindowFlags_UseVsync | SaddleWindowFlags_IsBorderless);

	ImGuiLayer& imGuiLayer = LayerManager::addLayer<ImGuiLayer>(0, 0);
	
	imGuiLayer.addImGuiObject([](const PassedArgs* args) -> void {
		if(!ImGui::Begin("Statistics")) {
			ImGui::End();
			return;
		}

		ImGui::Text("rtdvfrt");

		ImGui::End();
	}, 0);

	Logger::getClientLogger().log(Logger::INFO, *Window::getActiveWindow());
	
}