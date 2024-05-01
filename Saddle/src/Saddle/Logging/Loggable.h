#pragma once

#include <string>
#include <SaddleApi.h>

namespace Saddle {
	class SDL_API Loggable
	{
	public:

		virtual std::string toString(int indents) const = 0;

	protected:
		Loggable() {}
	};
}