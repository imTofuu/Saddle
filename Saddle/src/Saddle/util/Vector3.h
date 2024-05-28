#pragma once

#include "../Logging/Loggable.h"

namespace Saddle {

	class SDL_API Vector3 : public Loggable {
	public:
		float x = 0, y = 0, z = 0;

		std::string toString(int indents) const override {
			std::string str = std::string(indents, '	');
			str += std::to_string(x) += ", ";
			str += std::to_string(y) += ", ";
			str += std::to_string(z);
			return str;
		}

	};

}