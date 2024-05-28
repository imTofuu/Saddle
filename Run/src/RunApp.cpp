#include <Saddle.h>

#include <Saddle/Logging/Logger.h>
#include <Saddle/Windows/Window.h>

#include <Saddle/Scenes/Scene.h>
#include <Saddle/Objects/Object.h>
#include <Saddle/Objects/SaddleComponents.h>


void Saddle::Start() {

	Window window("Saddle Editor", 1280, 720, 
		SaddleWindowFlags_UseVsync | SaddleWindowFlags_StartMaximised);

	Scene scene = Scene::createScene();

	Object& object = scene.addObject("efgrhtgs");
	object.addComponent<TransformComponent>();

	

	Logger::getClientLogger().log("rgwfe", Logger::DEBUG);
}