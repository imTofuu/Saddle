#include "Timer.h"

SADDLE {

	void Timer::start() {
		m_startc = std::chrono::high_resolution_clock::now();
	}

	double Timer::current() {
		m_endc = std::chrono::high_resolution_clock::now();

		std::chrono::duration<double> time = m_endc - m_startc;
		return time.count() * 1000;
	}

}