#pragma once

#include "./../Component.h"
#include <Vector3.h>

namespace Saddle {

	class SDL_API Transform : public Component {
	public:
		Vector3 position, rotation, scale;

		std::string toString(int indents) const override;

		static std::string id() { return "Transform"; }

	};

}