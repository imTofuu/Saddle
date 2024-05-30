#include "Timer.h"

namespace Saddle {

	void Timer::start() {
		m_startc = std::chrono::high_resolution_clock::now();
	}

	double Timer::current() const {
		std::chrono::duration<double> time = std::chrono::high_resolution_clock::now() - m_startc;
		return time.count() * 1000;
	}

}