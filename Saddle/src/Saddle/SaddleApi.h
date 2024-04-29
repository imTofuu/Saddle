#pragma once

//for use on linux until better solution
#define SDL_PLATFORM_LINUX
#define SDL_BUILD_DLL

#if defined(SDL_PLATFORM_WINDOWS) || defined(SDL_PLATFORM_LINUX)
	#ifdef SDL_BUILD_DLL
		#define SDL_API __declspec(dllexport)
	#else
		#define SDL_API __declspec(dllimport)
	#endif
#else
	#error Saddle only has support for windows.
#endif