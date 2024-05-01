#include "Object.h"

namespace Saddle {

	Object::Object(std::string name) {
		this->m_name = new std::string(name);
		this->m_components = new std::unordered_map<std::string, Component*>();
	}

	std::string Object::toString(int indents) const {
		std::string str = std::string(indents, '	') += getName();
		int i = 0;
		for (auto& kv : *m_components) {
			if (i == 0) str += ":\n";
			Component* component = kv.second;
			str += component->toString(indents + 1);
			if (i == m_components->size() - 1) str += "\n";
			i++;
		}
		return str;
	}

}