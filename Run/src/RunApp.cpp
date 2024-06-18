#include <Saddle.h>

#include <Saddle/Logging/Logger.h>
#include <Saddle/Windows/Window.h>

#include <Saddle/Layers/CoreGuiItem.h>
#include <Saddle/Layers/LayerManager.h>

#include "EditorLayer.h"

void Saddle::Start() {

	Window* window = new Window("Saddle Editor", 1920, 1080, 
		0);

	LayerManager::addLayer<EditorLayer>(0, 0);

	Logger::getClientLogger().log(Logger::INFO, *Window::getActiveWindow());
	
}

void Saddle::Update() {

	CoreGuiItem item("hello");
	item.text("ergsdf");

}