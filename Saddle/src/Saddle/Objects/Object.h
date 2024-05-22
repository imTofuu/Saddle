#pragma once

#include <SaddleLogging.h>
#include "Component.h"
#include <unordered_map>

#include "./../EventDispatcher.h"

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
		 * \brief Removes a component from the object.
		 * 
		 * \tparam T The type of component. Component types must have a static
		 * member std::string id() that returns a unique id and must extend
		 * Component.
		 * 
		 * \return Remove success.
		*/
		template<class T> bool removeComponent();

		/**
		 * \brief Checks if the object has a component of type T.
		 * 
		 * \tparam T The type of component. Component types must have a static
		 * member std::String id() that returns a unique id and must extend
		 * Component.
		 * 
		 * \return If the object has a component of type T.
		*/
		template<class T> bool hasComponent();


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
		EventDispatcher::dispatchCreated();
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
		auto iter = m_components->find(T::id());
		SDL_CORE_ASSERT(iter != m_components.end(), "Object does not contain component.")
		return *(T*)m_components->at(T::id());
	}

	template<class T>
	bool Object::removeComponent() {
		T& component = getComponent<T>();

		if(component.m_dependency) {
			Logger::getCoreLogger().log("Component is dependency.", Logger::ERROR);
			return false;
		}

		auto iter = m_components.find(component.id());
		m_components.erase(iter);

		return true;
	}

	template<class T>
	bool Object::hasComponent() {
		return m_components.find(T::id()) != m_components.end();
	}
}