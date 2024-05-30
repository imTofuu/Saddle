#pragma once

#include <chrono>
#include "../SaddleApi.h"

namespace Saddle {

	class SDL_API Timer {
	public:

		/**
		 * \brief Creates an timer that has not been started.
		*/
		Timer() : Timer(false) {}

		/**
		 * \param start If true automatically starts the timer on creation.
		*/
		Timer(bool start) { if (start) this->start(); }


		/**
		 * \brief Starts or resets the current timer.
		*/
		void start();

		/**
		 * \return The time since the timer was last started in ms.
		*/
		double current() const;

	private:

		std::chrono::time_point<std::chrono::high_resolution_clock> m_startc;

	};

}