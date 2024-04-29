#pragma once

#include <SaddleLogging.h>

namespace Saddle {

	class Vector3 : public Loggable {
	public:
		float x = 0, y = 0, z = 0;

		std::string toString() const override { return "{ " + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + " }"; }

	};

}