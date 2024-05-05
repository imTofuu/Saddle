#include "Sprite.h"

namespace Saddle {

	Sprite::Sprite() : transform(addDependency<Transform>()) {
		
	}

}