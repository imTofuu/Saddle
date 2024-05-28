#pragma once

#include "../SaddleApi.h"

namespace Saddle {

	struct SDL_API Color {
	public:

		uint8_t r, g, b, a;

		Color() { Color(0, 0, 0, 1); }
		Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) : r(r), g(g), b(b), a(a) {}

	};

}