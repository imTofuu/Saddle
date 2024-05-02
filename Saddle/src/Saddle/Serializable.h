#pragma once

#include <string>
#include <vector>

namespace Saddle {

	class Serializable {
	public:

		void addPrimitive(void* data) { this-> } 

	private:
		friend class Serializer;

		std::vector<void**> data;

		bool isPrimitive = true;
	};

}