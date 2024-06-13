#include "Object.h"
#include "Component.h"

namespace Saddle {

	std::string Object::toString(int indents) const {
		std::string str = std::string(indents, '	') += getName();
		int i = 0;
		for (auto& kv : m_components.getConst()) {
			if (i == 0) str += ":\n";
			Component* component = kv.second;
			str += component->toString(indents + 1);
			if (i == m_components.size() - 1) str;
			i++;
		}
		return str;
	}
}