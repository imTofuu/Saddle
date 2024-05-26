#include <Saddle.h>

#include "Saddle/Logging/Logger.h"

void Saddle::Start() {
	Logger::getClientLogger().log("rgwfe", Logger::DEBUG);
}