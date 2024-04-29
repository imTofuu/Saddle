#pragma once

#include "./../Component.h"
#include <Vector3.h>

namespace Saddle {

	class Transform : public Component {
	public:
		Vector3 position, rotation, scale;

		std::string toString() const override { return id() + ": {\n" + position.toString() + ",\n" + rotation.toString() + ",\n" + scale.toString() + "\n}"; }

		static std::string id() { return "Transform"; }

	};

}