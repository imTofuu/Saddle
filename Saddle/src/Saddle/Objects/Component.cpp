#include "Component.h"

namespace Saddle {

	std::string Component::toString(int indents) const {
		return std::string(indents, '	') += "Component";
	}

	void Component::serialize(std::ofstream& file) const {
		for (auto& pair : m_exposedValues) {
			std::cout << ((char*)(pair.second)) << "efsd";
			file << pair.first << ":" << *reinterpret_cast<char*>(pair.second) << "\\";
		}
	}

	void Component::deserialize(std::unordered_map<std::string, void*> values) {
		m_exposedValues = values;
	}

}