#include "Component.h"

#include "Object.h"

namespace Saddle {

	std::vector<Component*> Component::m_components = std::vector<Component*>();

	std::string Component::toString(int indents) const {
		return std::string(indents, '	') += getAlias();
	}

	Component::~Component() {
		for (auto& pair : m_exposedValues) {
			delete pair.second;
		}
	}

}