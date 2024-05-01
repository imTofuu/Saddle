#pragma once

#include "Loggable.h"

#include <string>
#include <iostream>

namespace Saddle {
	class SDL_API Logger {
	public:
		enum Severity {
			DEBUG,
			INFO,
			WARN,
			ERROR
		};

		~Logger() { delete alias; }

		static void initLoggers();

		static const Logger& getCoreLogger() { return *coreLogger; }
		static const Logger& getClientLogger() { return *clientLogger; }

		std::string& getAlias() const { return *alias; }

		void log(std::string message, Severity severity) const;
		void log(Severity severity, const Loggable& loggables) const;
		void log(std::string message, Severity severity, const Loggable& loggable) const;

	private:
		Logger(std::string alias) { this->alias = new std::string(alias); }

		std::string* alias;

		static Logger* coreLogger;
		static Logger* clientLogger;
	};
}
