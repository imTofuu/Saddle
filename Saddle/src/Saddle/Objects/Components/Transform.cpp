#include "Transform.h"

namespace Saddle {

	std::string Transform::toString(int indents) const {
		std::string str = std::string(indents, '	') += id() += ":\n";
		str += std::string(indents + 1, '	') += "position: ";
		str += position.toString(0);
		str += std::string(indents + 1, '	') += "rotation: ";
		str += rotation.toString(0);
		str += std::string(indents + 1, '	') += "scale: ";
		str += scale.toString(0);

		return str;
	}

}