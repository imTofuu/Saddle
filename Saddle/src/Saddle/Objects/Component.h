#pragma once

#include <SaddleLogging.h>
#include <SaddleSerializing.h>

#include "Object.h"

namespace Saddle {
	class SDL_API Component : public Loggable, public Serializable {
	private:
		friend class Object;

	public:
		
		std::string toString(int indents) const override;

		Object& getObject() const { return *m_object; }

	protected:

		Component() {}

		template<class T> T& addDependency() { return m_object->addComponentAsDependency<T>(); }

		template<class T> T* getOrCreateExposedValue(std::string key) {
			T* val = new T();
			m_exposedValues.emplace(key, val);
			return val;
		}

	private:
		void serialize(std::ofstream& file) const override;
		void deserialize(std::unordered_map<std::string, void*> values) override;

		std::unordered_map<std::string, void*> m_exposedValues;

		Object* m_object = nullptr;

		bool m_dependency = false;

	};
}