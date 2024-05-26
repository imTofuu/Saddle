#pragma once

#include <SaddleLogging.h>
#include <SaddleApi.h>
#include <GLFW/glfw3.h>
#include "./../Application.h"

namespace Saddle {

	enum WindowFlags {

		SaddleWindowFlags_UseVsync = 1,

		SaddleWindowFlags_StartMaximised = 1 << 1

	};

	class Application;
	
	/**
	 * \brief GLFW window implementation.
	 * 
	 * \extends Loggable Can be converted to a string and passed into a logger
     * loggable.
	*/
	class SDL_API Window : public Loggable {
	public:

		/**
		 * \brief Creates and opens a glfw window.
		 * 
		 * \param properties Properties for the window to be opened with
		 * consisting of a name, window size, vsync, and maximisation. 
		 * Properties may be changed after the window's creation. Default
		 * values are name: Saddle Window, w h: 1280 720, vsync: false,
		 * maximised: true.
		*/
		Window(const std::string& title, int width, int height, uint64_t flags);

		/**
		 * \returns A reference to the active window.
		*/
		inline static Window* getActiveWindow() { return m_activeWindow; }

		std::string toString(int indents) const override;

	private:

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