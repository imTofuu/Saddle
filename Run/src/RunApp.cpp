#include <Saddle.h>

class RunEnv : public Saddle::Application {
public:
	RunEnv() {}
	~RunEnv() {}
};

Saddle::Application* Saddle::createApplication() {
	return new RunEnv();
}