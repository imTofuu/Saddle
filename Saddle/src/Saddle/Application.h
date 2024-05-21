#pragma once

#include "./../Global/SaddleApi.h"

SADDLE {

	class SDL_API Application {
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	Application* createApplication();

}