#include "Component.h"

namespace Saddle {

	std::string Component::toString(int indents) const {
		return std::string(indents, '	') += "Component";
	}

	std::string Component::serialize() const {
		std::string str;
		for (auto& pair : m_exposedValues) {
			str += pair.first + ":" + reinterpret_cast<char*>(pair.second) + "\\";
		}
		return str;
	}

	void Component::deserialize(std::unordered_map<std::string, void*> values) {
		m_exposedValues = values;
	}

}