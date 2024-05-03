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
		bool maximised;

		WindowProperties(const std::string& Title, int width, int height, bool Vsync, bool Maximised) : 
			w(width), h(height), title(Title), vsync(Vsync), maximised(Maximised) {}
	};

	class SDL_API Window : public Loggable {
	public:
		Window(const WindowProperties& properties = WindowProperties {"Saddle", 1280, 720, false, true});

		inline int w() const { return properties->w; }
		inline int h() const { return properties->h; }

		inline bool hasVsync() const { return vsync; }
		inline void setVsync(bool vsync) { glfwSwapInterval(vsync); this->vsync = vsync; }

		inline bool isMaximised() const { return maximised; }
		inline void setMaximised(bool maximised) { if (maximised) glfwMaximizeWindow(glfwwindow); this->maximised = maxismised }

		void update();

		inline bool shouldStop() const { return shouldstop; }

		inline static Window& getActiveWindow() { return *activeWindow; }

		std::string toString(int indents) const override;

	private:

		bool vsync;
		bool maximised;

		static Window* activeWindow;
		WindowProperties* properties;
		GLFWwindow* glfwwindow;

		bool shouldstop = false;
	};
}