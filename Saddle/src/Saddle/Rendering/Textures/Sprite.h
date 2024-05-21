#pragma once

#include "Bitmap.h"

namespace Saddle {

	class SDL_API Sprite {
	public:
		Sprite();

		const Bitmap& getBitmap() { return *bmp; }

	private:

		int w = 0, h = 0;
		const Bitmap* bmp = nullptr;

	};

}