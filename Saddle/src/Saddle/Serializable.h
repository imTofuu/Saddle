#pragma once

namespace Saddle {

	class Serializable {
	public:

		#define SDL_VAL(val) setValue(val);

		void setValue(void* value);

	};

}