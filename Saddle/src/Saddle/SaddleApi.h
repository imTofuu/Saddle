#pragma once

#ifdef SDL_PLTFRM_WINDOWS
	#ifdef SDL_BUILD_DLL
		#define SDL_API __declspec(dllexport)
	#else
		#define SDL_API __declspec(dllimport)
	#endif
#else
	#error Saddle only has support for windows.
#endif