#include <Saddle.h>

#include <Saddle/Logging/Logger.h>
#include <Saddle/Windows/Window.h>

#include <Saddle/Layers/CoreGuiItem.h>
#include <Saddle/Layers/LayerManager.h>

#include "EditorLayer.h"

void Saddle::Start() {

	Window* window = new Window("Saddle Editor", 1280, 720, 
		SaddleWindowFlags_UseVsync);

	LayerManager::addLayer<EditorLayer>(0, 0);

	Logger::getClientLogger().log(Logger::INFO, *Window::getActiveWindow());
	
}

void Saddle::Update() {

	CoreGuiItem item("Statistics");
	item.text("ergsdf");

}