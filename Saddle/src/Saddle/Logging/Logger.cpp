#include "Logger.h"

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

    void Logger::log(std::string message, Severity severity, const Loggable& loggables...) const {
        //TODO
    }
}