#pragma once

#include <string>
#include <unordered_map>
#include <fstream>
#include <iostream>

namespace Saddle {

	class Serializable {
	protected:

		virtual void serialize(std::ofstream& file) const = 0;
		virtual void deserialize(std::unordered_map<std::string, void*> values) = 0;

	private:
		friend class Serializer;
	};

}