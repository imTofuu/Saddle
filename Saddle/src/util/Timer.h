#pragma once

#include <chrono>

namespace Saddle {

	class Timer {
	public:

		Timer() : Timer(false) {}
		Timer(bool start) { if (start) this->start(); }

		void start();
		double current();

	private:

		std::chrono::time_point<std::chrono::high_resolution_clock> m_startc, m_endc;

	};

}