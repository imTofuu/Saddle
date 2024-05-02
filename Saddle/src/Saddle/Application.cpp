#include "Application.h"

#include "Windows/Window.h"

namespace Saddle {

	Application::Application() {}

	Application::~Application() {}

	void Application::Run() {
		Logger::initLoggers();

		Window* window = &Window();

		while (!window->shouldStop()) {
			window->update();
		}

		glfwTerminate();
	}
}