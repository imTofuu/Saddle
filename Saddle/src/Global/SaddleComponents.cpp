#include "SaddleComponents.h"

SADDLE {

	//Transform component

	std::string TransformComponent::toString(int indents) const {
		std::string str = std::string(indents, '	') + id() + ":\n";
		str += std::string(indents + 1, '	') + "position: " + position.toString(0) + "\n";
		str += std::string(indents + 1, '	') + "rotation: " + rotation.toString(0) + "\n";
		str += std::string(indents + 1, '	') + "scale: " + scale.toString(0);
		return str;
	}

	//Sprite component

	SpriteComponent::SpriteComponent() : transform(addDependency<TransformComponent>()) {}

	std::string SpriteComponent::toString(int indents) const {
		return "SpriteComponent";
	}

}