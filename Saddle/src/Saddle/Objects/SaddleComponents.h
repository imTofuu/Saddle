#pragma once

#include "Component.h"
#include "../util/Vector3.h"

namespace Saddle {

	class SDL_API TransformComponent : public Component {
	public:
		Vector3& position = getOrCreateVector3("position"),
			& rotation = getOrCreateVector3("rotation"),
			& scale = getOrCreateVector3("scale");

		std::string toString(int indents) const override;
		static std::string id() { return "Transform"; }

		TransformComponent(Object& object) : Component(object) {}

	};

	class SDL_API SpriteComponent : public Component {
	public:
		SpriteComponent(Object& object) : 
			transform(addDependency<TransformComponent>()), Component(object) {}

		std::string toString(int indents) const override;
		static std::string id() { return "Sprite"; }

		

	private:

		TransformComponent& transform;

	};

}