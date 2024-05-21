#pragma once

#include <SaddleLogging.h>
#include "./../Inspectable.h"
#include <Color.h>
#include <Vector3.h>

#include <unordered_map>

#include "Object.h"

namespace Saddle {
	class SDL_API Component : public Loggable {
	private:
		friend class Object;

	public:
		
		std::string toString(int indents) const override;

		Object& getObject() const { return m_object; }

	public:

		virtual void preRender() {}

		void update(double delta) {}

	protected:

		Component(Object& object) : m_object(object) {}
		virtual ~Component();

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