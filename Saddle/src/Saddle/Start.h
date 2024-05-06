#pragma once

extern Saddle::Application* Saddle::createApplication();

int main(int argc, char** argv) {
	auto app = Saddle::createApplication();
	app->Run();
}