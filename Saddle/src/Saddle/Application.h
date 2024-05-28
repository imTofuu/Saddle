#pragma once

#include "SaddleApi.h"

namespace Saddle {

	class SDL_API Application {
	public:
		void Run(void (*run)());
	};

	void Start();

}