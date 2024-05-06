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

		~Logger() { delete m_alias; }

		static void initLoggers();

		static const Logger& getCoreLogger() { return *m_coreLogger; }
		static const Logger& getClientLogger() { return *m_clientLogger; }

		std::string& getAlias() const { return *m_alias; }

		void log(std::string message, Severity severity) const;
		void log(Severity severity, const Loggable& loggables) const;
		void log(std::string message, Severity severity, const Loggable& loggable) const;

	private:
		Logger(std::string alias) { this->m_alias = new std::string(alias); }

		std::string* m_alias;

		static Logger* m_coreLogger;
		static Logger* m_clientLogger;
	};
}
