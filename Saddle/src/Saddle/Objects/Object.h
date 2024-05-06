#pragma once

#include <SaddleLogging.h>
#include "Component.h"
#include <unordered_map>

namespace Saddle {
	class Component;
	class SDL_API Object : public Loggable, public Serializable {
	public:

		std::string toString(int indents) const override;
		std::string getName() const { return *m_name; }

		template<class T> T& addComponent();
		template<class T> T& getComponent();

	private:
		Object() : Object("Object") {}
		Object(std::string name);

		template<class T> T& addComponentAsDependency();

		std::string serialize() const override;
		void deserialize(std::unordered_map<std::string, void*> values) override;

		std::string* m_name;

		std::unordered_map<std::string, Component*>* m_components;

		friend class Scene;
		friend class Component;
	};

	template<class T>
	T& Object::addComponent() {
		T* component = new T();
		component->m_object = this;
		m_components->emplace(component->id(), component);
		return *component;
	}

	template<class T>
	T& Object::addComponentAsDependency() {
		T& component = addComponent<T>();
		component.dependency = true;
		return component;
	}

	template<class T>
	T& Object::getComponent() {
		return m_components->at(component->id());
	}
}