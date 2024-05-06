#include "SaddleComponents.h"

namespace Saddle {

	std::string TransformComponent::toString(int indents) const {
		std::string str = std::string(indents, '	') + id() + ":\n";
		str += std::string(indents + 1, '	') + "x: " + x.toString(0) + "\n";
		str += std::string(indents + 1, '	') + "y: " + y.toString(0) + "\n";
		str += std::string(indents + 1, '	') + "z: " + z.toString(0);
		return str;
	}

}