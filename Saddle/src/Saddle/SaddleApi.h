#pragma once

#include <stdint.h>

namespace Saddle {

	#ifndef LAPTOP
		#define SDL_CORE_ASSERT(val, msg) if (!val) { Logger::getCoreLogger().log("Assert failed: "  msg, Logger::FATAL); __debugbreak(); }
		#define SDL_CLIENT_ASSET(val, msg) if (!val) { Logger::getClientLogger().log("Assert failed: "  msg, Logger::FATAL); __debugbreak(); }
		#ifdef SDL_BUILD_DLL
			#define SDL_API __declspec(dllexport)
		#else
			#define SDL_API __declspec(dllimport)
		#endif
	#else
		#define SDL_CORE_ASSERT(val, msg)
		#define SDL_CLIENT_ASSERT(val, msg)
		#define SDL_API
	#endif
}