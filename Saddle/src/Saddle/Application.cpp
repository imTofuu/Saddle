#include "Application.h"

namespace Saddle {

	Application::Application() {}

	Application::~Application() {}

	void Application::Run() {
		Logger::initLoggers();

		Window window;

		Logger::getCoreLogger().log("Main loop started", Logger::INFO);

		while (!Window::getActiveWindow()->shouldStop()) {
			Window::getActiveWindow()->update();	
		}

		glfwTerminate();
	}
}