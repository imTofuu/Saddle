#pragma once

#include <SaddleObjects.h>
#include <Vector3.h>

namespace Saddle {

	class SDL_API TransformComponent : public Component {
	public:
		Vector3 x, y, z;

		std::string toString(int indents) const override;
		static std::string id() { return "Transform"; }

	};

}