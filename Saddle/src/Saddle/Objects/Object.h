#pragma once

#include <SaddleLogging.h>
#include "Component.h"
#include <unordered_map>

namespace Saddle {
	class Component;

	/**
     * \brief Saddle Object class. An object contains 
     * 
     * \extends Loggable Can be converted to a string and passed into a logger
     * loggable.
    */
	class SDL_API Object : public Loggable {
	public:

		/**
		 * \brief Adds a component to the object.
		 * 
		 * \tparam T The type of component. Component types must have a static
		 * member std::string id() that returns a unique id and must extend
		 * Component.
		 * 
		 * \return A reference to the added component.
		*/
		template<class T> T& addComponent();

		/**
		 * \brief Gets a component from the object.
		 * 
		 * \tparam T The type of component. Component types must have a static
		 * member std::string id() that returns a unique id and must extend
		 * Component.
		 * 
		 * \return A reference to the component, if the object has it. If the
		 * object does not have a component of type T an exception will be
		 * thrown.
		*/
		template<class T> T& getComponent();


		/**
		 * \return The name of the scene.
		*/
		std::string getName() const { return *m_name; }

		std::string toString(int indents) const override;

	private:
		Object() : Object("Object") {}
		Object(std::string name);

		template<class T> T& addComponentAsDependency();

		std::string* m_name;

		std::unordered_map<std::string, Component*>* m_components;

		friend class Scene;
		friend class Component;
	};


	// Template definitions

	template<class T>
	T& Object::addComponent() {
		T* component = new T(*this);
		m_components->emplace(T::id(), component);
		return *component;
	}

	template<class T>
	T& Object::addComponentAsDependency() {
		T& component = addComponent<T>();
		component.m_dependency = true;
		return component;
	}

	template<class T>
	T& Object::getComponent() {
		return *(T*)m_components->at(component->id());
	}
}