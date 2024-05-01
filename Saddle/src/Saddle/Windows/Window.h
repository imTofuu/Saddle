#pragma once

#include <SaddleApi.h>
#include <SaddleLogging.h>
#include <string>
#include <GLFW/glfw3.h>

namespace Saddle {

	struct WindowProperties {
		int w;
		int h;

		std::string title;

		WindowProperties(const std::string& Title, int width, int height) : w(width), h(height), title(Title) {}
	};

	class SDL_API Window : public Loggable {
	public:
		virtual ~Window() {}

		virtual int w() const = 0;
		virtual int h() const = 0;
		
		static Window* createWindow(const WindowProperties& properties = WindowProperties("Saddle", 1280, 720));
	};
}