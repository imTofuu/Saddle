#pragma once

#include <SaddleApi.h>

namespace Saddle {
	class SDL_API Logger {
	public:
		static const Logger& getCoreLogger() { return *coreLogger; }
		static const Logger& getClientLogger() { return *clientLogger; }
	private:
		static Logger* coreLogger;
		static Logger* clientLogger;
	};
}