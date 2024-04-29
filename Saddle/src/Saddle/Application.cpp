#include "Application.h"
#include "Logging/Logger.h"

#include <SaddleObjects.h>

namespace Saddle {

	Application::Application() {}

	Application::~Application() {}

	void Application::Run() {
		Logger::initLoggers();

		Scene scene;
		Object& object = scene.addObject("object1");
		scene.addObject("object2");
		object.addComponent<Transform>();

		Logger::getCoreLogger().log(Logger::Severity::DEBUG, scene);

		while (true);
	}
}