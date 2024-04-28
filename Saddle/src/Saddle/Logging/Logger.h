#pragma once

#include <SaddleApi.h>
#include <string>
#include <stdio.h>

namespace Saddle {
	class SDL_API Logger {
	public:
		enum Severity {
			INFO,
			WARN,
			ERROR
		}

		Logger(std::string alias) { this->alias = alias; }

		static void initLoggers();

		static const Logger& getCoreLogger() { return *coreLogger; }
		static const Logger& getClientLogger() { return *clientLogger; }

		std::string getAlias();

		void log(std::string message, Severity severity) const;

	private:
		std::string alias;

		static Logger* coreLogger;
		static Logger* clientLogger;
	};
}