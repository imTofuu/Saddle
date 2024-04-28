#include "Logger.h"

namespace Saddle {
    void Logger::initLoggers() {
        this->coreLogger = new Logger("ENGINE");
        this->clientLogger = new Logger("CLIENT");

        coreLogger.log("Loggers initialised", Severity.INFO);
    }

    void Logger::log(std::string message, Severity severity) const {
        std::string color = "\x1b[";
        std::cout << color << "[" << getAlias() << "] " << message << std::endl;
    }
}