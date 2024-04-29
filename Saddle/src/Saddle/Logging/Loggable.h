#pragma once

#include <string>
#include <SaddleApi.h>

namespace Saddle {
	class SDL_API Loggable
	{
	public:

		virtual const std::string toString() const = 0;

	private:
		Loggable() {}
	};
}