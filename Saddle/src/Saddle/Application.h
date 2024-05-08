#pragma once

#include "./../Global/SaddleApi.h"
#include "Windows/Window.h"

namespace Saddle {

	class SDL_API Application {
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	Application* createApplication();

}