#pragma once

#include <SaddleLogging.h>
#include "Component.h"
#include <unordered_map>

namespace Saddle {
	class Component;
	class SDL_API Object : public Loggable {
	public:

		std::string toString() const override;
		std::string getName() const { return *m_name; }

		template<class T> T& addComponent();
		template<class T> T& getComponent();

	private:
		Object() : Object("Object") {}
		Object(std::string name);

		std::string* m_name;

		std::unordered_map<std::string, Component*>* m_components;

		friend class Scene;
	};

	template<class T>
	T& Object::addComponent() {
		T* component = new T();
		m_components->emplace(component->id(), component);
		return (T&)*m_components->at(component->id());
	}

	template<class T>
	T& Object::getComponent() {
		return m_components->at(component->id());
	}
}