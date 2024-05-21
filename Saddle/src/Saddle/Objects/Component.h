#pragma once

#include <SaddleLogging.h>

#include "Object.h"

namespace Saddle {
	class SDL_API Component : public Loggable {
	private:
		friend class Object;

	public:
		
		std::string toString(int indents) const override;

		Object& getObject() const { return *m_object; }

	public:

		virtual void preRender() {}

		void update(double delta) {}

	protected:

		Component(Object& object) : m_object(object) {}
		~Component() { for(auto * val : m_exposedValues) { delete val; } }

		template<>

		template<class T> T& addDependency() { return m_object->addComponentAsDependency<T>(); }

		char& getOrCreateChar(std::string key) { return getOrCreateExposedValue<char>(key); }
		short& getOrCreateShort(std::string key) { return getOrCreateExposedValue<short>(key); }
		int& getOrCreateInt(std::string key) { return getOrCreateExposedValue<int>(key); }
		float& getOrCreateFloat(std::string key) { return getOrCreateExposedValue<float>(key); }
		double& getOrCreateDouble(std::string key) { return getOrCreateExposedValue<double>(key); }

		std::string& getOrCreateString(std::string key) { return getOrCreateExposedValue<std::string>(key); }

		Color& getOrCreateColor(std::string key) { return getOrCreateExposedValue<Color>(key); }

		Vector3& getOrCreateVector3(std::string key) { return getOrCreateExposedValue<Vector3>(key); }


	private:

		template<class T> T& getOrCreateExposedValue(std::string key) {
			T* val = new T();
			m_exposedValues.emplace(key, val);
			return *val;
		}

		std::unordered_map<std::string, void*> m_exposedValues;

		Object& m_object;

		bool m_dependency = false;

	};
}