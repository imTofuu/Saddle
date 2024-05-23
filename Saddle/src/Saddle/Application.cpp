#include "Application.h"

#include "Windows/Window.h"
#include <SaddleObjects.h>
#include "EventDispatcher.h"

namespace Saddle {

	Application::Application() {}

	Application::~Application() {}

	void Application::Run() {
		Logger::initLoggers();

		Window window;

		EventDispatcher::getMainDispatcher().dispatchStart();

		Logger::getCoreLogger().log("Main loop started", Logger::INFO);

		while (!Window::getActiveWindow().shouldStop()) {
			Window::getActiveWindow().update();	
		}

		delete& Scene::getActiveScene();

		glfwTerminate();
	}
}
