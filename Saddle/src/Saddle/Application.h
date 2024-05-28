#pragma once

#include "SaddleApi.h"

namespace Saddle {

	class SDL_API Application {
	public:
		Application();

		void Run(void (*run)());
	};

	void Start();

}