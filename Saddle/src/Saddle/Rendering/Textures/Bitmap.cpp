#include "Bitmap.h"

#include <fstream>
#include <SaddleLogging.h>

namespace Saddle {

	Bitmap::Bitmap(std::string filepath, GLuint& tex) {
		std::ifstream f;
		f.open(filepath, std::ios::in | std::ios::binary);

		if (!f.is_open()) {
			Logger::getCoreLogger().log("Failed to open bitmap file at path: " + filepath, Logger::ERROR);
			return;
		}

		const int fileHeaderSize = 14;
		const int informationHeaderSize = 40;

		unsigned char fileHeader[fileHeaderSize];
		f.read(reinterpret_cast<char*>(fileHeader), fileHeaderSize);

		unsigned char informationHeader[informationHeaderSize];
		f.read(reinterpret_cast<char*>(informationHeader), informationHeaderSize);

		int fileSize = fileHeader[2] + (fileHeader[3] << 8) + (fileHeader[4] << 16) + (fileHeader[5] << 24);
		w = informationHeader[4] + (informationHeader[5] << 8) + (informationHeader[6] << 16) + (informationHeader[7] << 24);
		h = informationHeader[8] + (informationHeader[9] << 8) + (informationHeader[10] << 16) + (informationHeader[11] << 24);

		values = new Color[w * h];

		const int paddingAmount = ((4 - (w * 3) % 4) % 4);

		for (int y = 0; y < h; y++) {
			for (int x = 0; x < w; x++) {
				uint8_t color[4];
				f.read(reinterpret_cast<char*>(color), 4);

				values[(y * w) + x].r = color[3];
				values[(y * w) + x].g = color[2];
				values[(y * w) + x].b = color[1];
				values[(y * w) + x].a = color[0];
			}
		}
		f.ignore(paddingAmount);

		f.close();
	}

}
