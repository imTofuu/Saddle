#include "Application.h"

#include <SaddleLogging.h>
#include <SaddleObjects.h>

#include "Windows/WindowsWindow.h"

namespace Saddle {

	Application::Application() {}

	Application::~Application() {}

	void Application::Run() {
		Logger::initLoggers();

		Window* window = WindowsWindow::createWindow();

		while (true);
	}
}