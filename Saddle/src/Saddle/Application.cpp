#include "Application.h"
#include "Logging/Logger.h"

namespace Saddle {

	Application::Application() {}

	Application::~Application() {}

	void Application::Run() {
		Logger::initLoggers();

		while (true);
	}
}