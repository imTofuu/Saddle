#pragma once

#include <glad/glad.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <SaddleLogging.h>
#include <SaddleApi.h>

#include <GLFW/glfw3.h>

#include <Timer.h>

#include <thread>

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

		inline int w() const { return m_properties->w; }
		inline int h() const { return m_properties->h; }

		inline bool hasVsync() const { return m_vsync; }
		inline void setVsync(bool vsync) { glfwSwapInterval(vsync); this->m_vsync = vsync; }

		inline bool isMaximised() const { return m_maximised; }
		inline void setMaximised(bool maximised) { if (maximised) glfwMaximizeWindow(m_glfwwindow); this->m_maximised = maximised; }

		void update();

		inline bool shouldStop() const { return m_shouldstop; }

		inline static Window& getActiveWindow() { return *m_activeWindow; }

		std::string toString(int indents) const override;

	private:

		bool m_vsync;
		bool m_maximised;

		static Window* m_activeWindow;
		WindowProperties* m_properties;
		GLFWwindow* m_glfwwindow;

		bool m_shouldstop = false;
	};
}