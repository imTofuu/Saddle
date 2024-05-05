#include "Timer.h"

namespace Saddle {

	void Timer::start() {
		startc = std::chrono::high_resolution_clock::now();
	}

	double Timer::current() {
		endc = std::chrono::high_resolution_clock::now();

		std::chrono::duration<double> time = endc - startc;
		return time.count() * 1000;
	}

}