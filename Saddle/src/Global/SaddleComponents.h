#pragma once

#include <SaddleObjects.h>
#include <Vector3.h>

namespace Saddle {

	class SDL_API TransformComponent : public Component {
	public:
		Vector3& position = *getOrCreateExposedValue<Vector3>("position"), 
			& rotation = *getOrCreateExposedValue<Vector3>("rotation"), 
			& scale = *getOrCreateExposedValue<Vector3>("scale");

		std::string toString(int indents) const override;
		static std::string id() { return "Transform"; }

	};

	class SDL_API SpriteComponent : public Component {
	public:
		SpriteComponent();

		std::string toString(int indents) const override;
		static std::string id() { return "Sprite"; }
	
	private:

		TransformComponent& transform;

	}

}