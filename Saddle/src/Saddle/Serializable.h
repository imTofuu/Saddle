#pragma once

#include <string>
#include <unordered_map>

namespace Saddle {

	class Serializable {
	protected:

		virtual std::string serialize() const = 0;
		virtual void deserialize(std::unordered_map<std::string, void*> values) = 0;

	private:
		friend class Serializer;
	};

}