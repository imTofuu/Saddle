#include <chrono>
#include "../SaddleApi.h"

namespace Saddle {

	class SDL_API Timer {
	public:

		Timer() : Timer(false) {}
		Timer(bool start) { if (start) this->start(); }


		void start() { m_startc = std::chrono::high_resolution_clock::now(); }

		double current() const {
			return (std::chrono::high_resolution_clock::now() - m_startc).count() * 1000;
		}

	private:

		std::chrono::time_point<std::chrono::high_resolution_clock> m_startc;

	};

}