#pragma once

#include "SaddleSerializing.h"

namespace Saddle {

#if defined(SDL_PLATFORM_WINDOWS) || defined(SDL_PLATFORM_LINUX)
	#ifdef SDL_BUILD_DLL
		#define SDL_API __declspec(dllexport)
	#else
		#define SDL_API __declspec(dllimport)
	#endif
#else
	#error Saddle only has support for windows.
#endif

#ifdef SDL_BUILD_DLL
	#define SDL_SERIAL : public Serializable
#endif
}