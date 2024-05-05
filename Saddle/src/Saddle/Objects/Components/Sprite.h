#pragma once

#include "./../Component.h"
#include "Transform.h"

namespace Saddle {

	class SDL_API Sprite : public Component {
	public:

		Sprite();

	private:

		Transform& transform;

	};
}