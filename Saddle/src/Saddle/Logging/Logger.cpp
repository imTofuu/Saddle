#include "Logger.h"

#include "Loggable.h"

namespace Saddle {
    Logger* Logger::m_clientLogger = nullptr;
    Logger* Logger::m_coreLogger = nullptr;

    void Logger::initLoggers() {
        m_coreLogger = new Logger("ENGINE");
        m_clientLogger = new Logger("CLIENT");

        m_coreLogger->log("Loggers initialised", Severity::INFO);
    }

    void Logger::log(std::string message, Severity severity) const {
        std::string color;
        switch (severity)
        {
            case Logger::DEBUG:
                #ifndef SDL_DEBUG
                    return;
                #endif
                color = "\033[1;32m";
                break;
            case Logger::INFO:
                color = "\033[0m";
                break;
            case Logger::WARN:
                color = "\033[1;33m";
                break;
            case Logger::ERROR:
                color = "\033[1;31m";
                break;
            case Logger::FATAL:
                color = "\033[1;31m";
                break;
        }
        std::cout << color << "[" << getAlias() << "] " << message << "\033[0m" << std::endl;
        if (severity == Saddle::Logger::FATAL)
            #ifdef SDL_PLATFORM_WINDOWS
                __debugbreak()
            #endif
            ;
    }

    void Logger::log(Severity severity, const Loggable& loggable) const {
	    log(loggable.toString(0), severity);
    }

    void Logger::log(std::string message, Severity severity, const Loggable& loggable) const {
	    log(message + " " + loggable.toString(0), severity);
    }
}
