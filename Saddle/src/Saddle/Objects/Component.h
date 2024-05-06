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

		Object& getObject() const { return *object; }

	protected:

		Component() {}

		template<class T> T& addDependency();

	private:
		Object* object = nullptr;

		bool dependency = false;

	};

	template<class T>
	T& Component::addDependency() {
		return object->addComponentAsDependency<T>();
	}
}