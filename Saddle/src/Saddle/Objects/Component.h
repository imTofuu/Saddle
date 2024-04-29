#pragma once

#include <SaddleLogging.h>

namespace Saddle {
	class SDL_API Component : public Loggable {
	public:
		

		std::string toString() const override;

	};
}