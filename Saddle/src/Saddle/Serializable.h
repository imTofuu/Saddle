#pragma once

#include <string>
#include <unordered_map>

namespace Saddle {

	class Serializable {
	public:

		inline void addValue(std::string k, void* v) { data.emplace(k, v); }

		inline std::string serialize() const;

	private:
		friend class Serializer;

		std::unordered_map<std::string, void*> data;

		bool isPrimitive = true;
	};

}