#pragma once

#include "../Logging/Loggable.h"
#include "../SaddleApi.h"
#include "../Application.h"
#include "../util/Time.h"

#include <GLFW/glfw3.h>

namespace Saddle {

	enum SDL_API WindowFlags {

		SaddleWindowFlags_UseVsync = 1,

		SaddleWindowFlags_StartMaximised = 1 << 1,
		SaddleWindowFlags_IsFullscreen = 1 << 2,
		SaddleWindowFlags_IsBorderless = 1 << 3,

		SaddleWindowFlags_IsUndecorated = 1 << 4

	};

	class Application;
	
	class SDL_API Window : public Loggable {
	public:

		Window(const std::string& title, int width, int height, uint64_t flags);

		static Window* getActiveWindow() { return m_activeWindow; }

		std::string toString(int indents) const override;

		const Time& getTimeInfo() { return m_time; }

	private:

		Time m_time;

		friend class Application;

		void update();

		inline bool shouldStop() const { return m_shouldstop; }

		static Window* m_activeWindow;
		GLFWwindow* m_glfwwindow;

		std::string m_title;

		int m_width, m_height;
		uint64_t m_flags;

		bool m_shouldstop = false;
	};
}