#include "Object.h"

namespace Saddle {

	Object::Object(std::string name) {
		this->m_name = new std::string(name);
		this->m_components = new std::unordered_map<std::string, Component*>();
	}

	std::string Object::toString() const {
		std::string str = getName();
		int i = 0;
		for (auto& kv : *m_components) {
			if (i == 0) str += ": {\n";
			Component* component = kv.second;
			str += component->toString();
			if (i != m_components->size() - 1) str += ",\n"; else str += "\n}";
			i++;
		}
		return str;
	}

}