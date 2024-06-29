#include <chrono>
#include "../SaddleApi.h"

namespace Saddle {

	class SDL_API Timer {
	public:

		Timer() : Timer(false) {}
		Timer(bool start) { if (start) this->start(); }


		void start() { m_startc = std::chrono::high_resolution_clock::now(); }

		float current() const {
			float milliseconds = (std::chrono::high_resolution_clock::now() - m_startc).count();
			return milliseconds / 1000000;
		}

	private:

		std::chrono::time_point<std::chrono::high_resolution_clock> m_startc;

	};

}