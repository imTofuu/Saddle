#include "Component.h"

namespace Saddle {

	std::string Component::toString(int indents) const {
		return std::string(indents, '	') += "Component";
	}

	Component::~Component() {
		for (auto& pair : m_exposedValues) {
			delete pair.second;
		}
	}

}