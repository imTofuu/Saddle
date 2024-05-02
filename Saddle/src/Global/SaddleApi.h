#pragma once

namespace Saddle {
	#define SDL_CORE_ASSERT(val, msg) if (!val) { Logger::getCoreLogger().log("Assert failed: "  msg, Logger::ERROR); __debugbreak(); }
	#define SDL_CLIENT_ASSET(val, msg) if (!val) { Logger::getClientLogger().log("Assert failed: "  msg, Logger::ERROR); __debugbreak(); }

	#if defined(SDL_PLATFORM_WINDOWS) || defined(SDL_PLATFORM_LINUX)
		#ifdef SDL_BUILD_DLL
			#define SDL_API __declspec(dllexport)
		#else
			#define SDL_API __declspec(dllimport)
		#endif
	#else
		#error Saddle only has support for Windows.
	#endif

	#ifdef SDL_BUILD_DLL
		#define SDL_SERIAL : public Serializable
	#endif
}