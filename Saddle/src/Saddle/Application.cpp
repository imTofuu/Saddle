#include "Application.h"

#include "Windows/Window.h"
#include "EventDispatcher.h"
#include "Logging/Logger.h"
#include "Scenes/Scene.h"

namespace Saddle {

	void Application::Run(void (*run)()) {
		Logger::initLoggers();

		run();

		EventDispatcher::getMainDispatcher().dispatchStart();

		Logger::getCoreLogger().log("Main loop started", Logger::INFO);

		Window* activeWindow;

		activeWindow = Window::getActiveWindow();

		if (!Window::m_activeWindow) {
			Logger::getCoreLogger().log("No window created, making a default one", Logger::ERROR);
			Window* window = new Window("Saddle", 1280, 720, SaddleWindowFlags_UseVsync);
			activeWindow = window;
		}

		while (!activeWindow->shouldStop()) {
			activeWindow->update();	
		}

		delete& Scene::getActiveScene();

		glfwTerminate();
	}
}
