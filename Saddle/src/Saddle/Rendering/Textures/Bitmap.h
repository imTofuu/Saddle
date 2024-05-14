#pragma once

#include <glad/glad.h>
#include <SaddleApi.h>
#include <string>
#include "./../Color.h"
#include <fstream>

namespace Saddle {

	class SDL_API Bitmap {
	public:

		Bitmap(std::string filepath, GLuint& tex);

		Color get(int x, int y) const { return values[(y * w) + x]; }
		void set(int x, int y, Color color) { values[(y * w) + x] = color; }
		Color& operator[](int i) { return values[i]; }

	private:

		int w, h;
		Color values[];

	};

}