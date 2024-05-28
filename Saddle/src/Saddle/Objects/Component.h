#pragma once

#include "../Logging/Loggable.h"
#include "../Inspectable.h"
#include "Object.h"

#include "../util/Color.h"
#include "../util/Vector3.h"

#include <unordered_map>
#include <vector>

#include "./../EventDispatcher.h"

namespace Saddle {
	class EventDispatcher;
	class Object;
	class SDL_API Component : public Loggable {
	private:
		friend class Object;
		friend class EventDispatcher;

	public:

		virtual ~Component();
		
		std::string toString(int indents) const override;

		Object& getObject() const { return m_object; }

	protected: // EVENTS

		/**
		 * \brief Last code that runs before the screen buffer is switched.
		 * Any shaders that need to be applied to the screen should be run
		 * here.
		*/
		virtual void preRender() {}


		/**
		 * \brief Runs on a component when it is created. This is when the
		 * component is created, meaning there is no guarantee that other
		 * things, like scenes, objects, or components will exist. To guarantee
		 * references to other objects, use start(). You may not destroy the
		 * components in this event, rather wait to try on the first frame it
		 * is rendered.
		*/
		virtual void created() {}

		/**
		 * \brief Runs when the game is started, if the component exists.
		*/
		virtual void start() {}

		/**
		 * \brief Run after a frame is rendered, if the component exists.
		 * 
		 * \param delta The time that has passed since the last update.
		*/
		virtual void update(double delta) {}

	protected:

		Component(Object& object) : m_object(object) { m_components->push_back(this); }

		template<class T> T& addDependency() { return m_object.addComponentAsDependency<T>(); }

		char& getOrCreateChar(std::string key) { return getOrCreateExposedValue<            char          >(key, InspectableType::NUMBER); }
		short& getOrCreateShort(std::string key) { return getOrCreateExposedValue<          short         >(key, InspectableType::NUMBER); }
		int& getOrCreateInt(std::string key) { return getOrCreateExposedValue<              int           >(key, InspectableType::NUMBER); }
		float& getOrCreateFloat(std::string key) { return getOrCreateExposedValue<          float         >(key, InspectableType::NUMBER); }
		double& getOrCreateDouble(std::string key) { return getOrCreateExposedValue<        double        >(key, InspectableType::NUMBER); }
		std::string& getOrCreateString(std::string key) { return getOrCreateExposedValue<   std::string   >(key, InspectableType::STRING); }
		Color& getOrCreateColor(std::string key) { return getOrCreateExposedValue<          Color         >(key, InspectableType::COLOR); }
		Vector3& getOrCreateVector3(std::string key) { return getOrCreateExposedValue<      Vector3       >(key, InspectableType::VECTOR3); }


	private:

		static std::vector<Component*>* m_components;

		template<class T>
		T& getOrCreateExposedValue(std::string key, InspectableType type) {

			std::unordered_map<std::string, void*>::iterator iter = m_exposedValues.find(key);
			if (iter != m_exposedValues.end()) return *(T*)iter->second;

			T* val = new T();
			m_exposedValues.emplace(key, val);
			return *val;
		}

		std::unordered_map<std::string, void*> m_exposedValues;

		Object& m_object;

		bool m_dependency = false;

	};
}