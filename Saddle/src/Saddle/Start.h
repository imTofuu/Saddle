#pragma once

#ifdef SDL_PLATFORM_WINDOWS

extern Saddle::Application* Saddle::createApplication();

int main(int argc, char** argv) {
	auto app = Saddle::createApplication();
	app->Run();
	delete app;
}

#endif