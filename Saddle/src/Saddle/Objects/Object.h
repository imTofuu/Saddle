#pragma once

#include "../Logging/Loggable.h"
#include <unordered_map>
#include <vector>

#include "../Scenes/Scene.h"

#include "../EventDispatcher.h"

namespace Saddle {
	class Component;
	class EventDispatcher;

	/**
     * \brief Saddle Object class. An object contains 
     * 
     * \extends Loggable Can be converted to a string and passed into a logger
     * loggable.
    */
	class SDL_API Object : public Loggable {
	public:

		template<class T> T& addComponent();
		template<class T> T& getComponent();
		std::vector<Component*> getComponents() { return m_components.get(); }
		std::vector<const Component*> getComponents() const { return m_components.getConst(); }
		template<class T> static std::vector<T*> getAllComponents();
		template<class T> bool removeComponent();
		template<class T> bool hasComponent();
		template<class T> static bool componentIs(Component* component);

		Scene& getScene() { return m_scene; }
		const Scene& getScene() const { return m_scene; }

		/**
		 * \return The name of the scene.
		*/
		std::string getName() const { return m_name; }

		std::string toString(int indents) const override;

	private:
		Object(Scene& scene) : Object("Object", scene) {}
		Object(std::string name, Scene& scene) : m_scene(scene), m_name(name) {}

		template<class T> T& addComponentAsDependency();

		Scene& m_scene;

		std::string m_name;

		ObjectList<Component> m_components;

		friend class Scene;
		friend class Component;
	};


	// Template definitions

	template<class T>
	T& Object::addComponent() {
		T* component = new T(*this);
		m_components.add(component);
		EventDispatcher::getMainDispatcher().dispatchCreated(component);
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
		for(auto & component : m_components.get()) {
			T* newType  = dynamic_cast<T*>(&component);
			if(newType != 0) return newType;
		}
		SDL_CORE_ASSERT(false, "Object does not contain component of type T");
	}
	
	template<class T>
	std::vector<T*> Object::getAllComponents() {
		std::vector<T*> components;
		for(auto * scene : Scene::getAllScenes()) {
			for(auto * object : scene->getObjects()) {
				for(auto * component : object->getComponents()) {
					if(componentIs<T>(component)) components.push_back((T*)component);
				}
			}
		}
		return components;
	}

	template<class T>
	bool Object::componentIs(Component* component) {
		return dynamic_cast<T*>(component) != 0;
	}

	template<class T>
	bool Object::removeComponent() {
		T& component = getComponent<T>();

		if(component.m_dependency) {
			Logger::getCoreLogger().log("Component is dependency.", Logger::ERROR);
			return false;
		}

		m_components.remove(component);

		return true;
	}

	template<class T>
	bool Object::hasComponent() {
		for(auto & component : m_components.get()) {
			T* newType = dynamic_cast<T*>(&component);
			if(newType != 0) return true;
		}
		return false;
	}
}