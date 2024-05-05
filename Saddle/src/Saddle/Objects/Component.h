#pragma once

#include <SaddleLogging.h>

namespace Saddle {
	class SDL_API Component : public Loggable {
	public:
		
		std::string toString(int indents) const override;

		Object& getObject() const { return *object; }

	protected:

		Component() { dependency = false; }

		template<class T> T& addDependency();

	private:

		friend class Object;
		Object* object;

		bool dependency;

	};

	template<class T>
	T& Component::addDependency() {
		return object->addComponentAsDependency<T>();
	}
}