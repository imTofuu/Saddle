#pragma once

namespace Saddle {

	#ifdef SDL_PLATFORM_WINDOWS
		#define SDL_CORE_ASSERT(val, msg) if (!(val)) { Logger::getCoreLogger().log("Assert failed: " msg, Logger::FATAL); __debugbreak(); }
		#define SDL_CLIENT_ASSET(val, msg) if (!(val)) { Logger::getClientLogger().log("Assert failed: " msg, Logger::FATAL); __debugbreak(); }
		#ifdef SDL_BUILD_DLL
			#define SDL_API __declspec(dllexport)
		#else
			#define SDL_API __declspec(dllimport)
		#endif
	#elif defined(SDL_PLATFORM_LINUX) || defined(SDL_PLATFORM_MAC)
		#define SDL_CORE_ASSERT(val, msg) if (!(val)) { Logger::getCoreLogger().log("Assert failed: " msg, Logger::FATAL); }
		#define SDL_CLIENT_ASSERT(val, msg) if (!(val)) { Logger::getClientLogger().log("Assert failed: " msg, Logger::FATAL); }
		#define SDL_API
	#endif
}