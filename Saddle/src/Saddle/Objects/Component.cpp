#include "Component.h"

namespace Saddle {

	std::string Component::toString(int indents) const {
		return std::string(indents, '	') += "Component";
	}

}