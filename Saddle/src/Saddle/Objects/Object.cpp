#include "Object.h"
#include "Component.h"

namespace Saddle {

	std::string Object::toString(int indents) const {
		std::string str = std::string(indents, '	') += getName();
		int i = 0;
		for (const auto * component : m_components.getConst()) {
			if (i == 0) str += ":\n";
			str += component->toString(indents + 1);
			i++;
		}
		return str;
	}
}