#include "Logger.h"
#include <cstdarg>

namespace Saddle {
    Logger* Logger::clientLogger = nullptr;
    Logger* Logger::coreLogger = nullptr;

    void Logger::initLoggers() {
        coreLogger = new Logger("ENGINE");
        clientLogger = new Logger("CLIENT");

        coreLogger->log("Loggers initialised", Severity::INFO);
    }

    void Logger::log(std::string message, Severity severity) const {
        std::string color;
        switch (severity)
        {
            case Saddle::Logger::DEBUG:
                #ifndef SDL_DEBUG
                    return;
                #endif
                color = "\033[1;32m";
                break;
            case Saddle::Logger::INFO:
                color = "\033[0m";
                break;
            case Saddle::Logger::WARN:
                color = "\033[1;33m";
                break;
            case Saddle::Logger::ERROR:
                color = "\033[1;31m";
                break;
        }
        std::cout << color << "[" << getAlias() << "] " << message << "\033[0m" << std::endl;
    }

    void Logger::log(Severity severity, const Loggable& loggable) const {
	    log(loggable.toString(0), severity);
    }

    void Logger::log(std::string message, Severity severity, const Loggable& loggable) const {
	    log(message + " " + loggable.toString(0), severity);
    }
}
