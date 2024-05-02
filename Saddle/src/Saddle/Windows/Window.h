#pragma once

#include <glad/glad.h>
#include <SaddleLogging.h>
#include <SaddleApi.h>
#include <GLFW/glfw3.h>

namespace Saddle {

	struct WindowProperties {
		int w;
		int h;

		std::string title;

		bool vsync;

		WindowProperties(const std::string& Title, int width, int height, bool Vsync = false) : w(width), h(height), title(Title), vsync(Vsync) {}
	};

	class SDL_API Window : public Loggable {
	public:
		Window(const WindowProperties& properties = WindowProperties {"Saddle", 1280, 720});

		inline int w() const { return properties->w; }
		inline int h() const { return properties->h; }

		inline bool hasVsync() const { return vsync; }
		inline void setVsync(bool vsync) { glfwSwapInterval(vsync); this->vsync = vsync; }

		void update();

		inline bool shouldStop() const { return shouldstop; }

		inline static Window& getActiveWindow() { return *activeWindow; }

		std::string toString(int indents) const override;

	private:

		bool vsync = false;

		static Window* activeWindow;
		WindowProperties* properties;
		GLFWwindow* glfwwindow;

		bool shouldstop = false;
	};
}