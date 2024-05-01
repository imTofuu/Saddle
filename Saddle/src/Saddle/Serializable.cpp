#include "Serializable.h"

namespace Saddle {
	void Serializable::setValue(void* value) {
		char* val = reinterpret_cast<char*>(value);
	}
}