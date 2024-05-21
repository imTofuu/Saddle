#pragma once

#include <stdint.h>

namespace Saddle {
	#define SDL_CORE_ASSERT(val, msg) if (!val) { Logger::getCoreLogger().log("Assert failed: "  msg, Logger::FATAL); __debugbreak(); }
	#define SDL_CLIENT_ASSET(val, msg) if (!val) { Logger::getClientLogger().log("Assert failed: "  msg, Logger::FATAL); __debugbreak(); }

	#if defined(SDL_PLATFORM_WINDOWS)
		#ifdef SDL_BUILD_DLL
			#define SDL_API __declspec(dllexport)
		#else
			#define SDL_API __declspec(dllimport)
		#endif
	#else
		#error Saddle only has support for Windows.
	#endif

	#define SADDLE namespace Saddle
}