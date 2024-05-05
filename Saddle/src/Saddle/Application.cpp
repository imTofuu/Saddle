#include "Application.h"

#include "Windows/Window.h"

namespace Saddle {

	Application::Application() {}

	Application::~Application() {}

	void Application::Run() {
		Logger::initLoggers();

		Window window;

		Logger::getCoreLogger().log("Main loop started", Logger::INFO);

		while (!window.shouldStop()) {
			window.update();

		}

		glfwTerminate();
	}
}