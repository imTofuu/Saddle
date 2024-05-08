#pragma once

#include <glad/glad.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <SaddleLogging.h>
#include <SaddleApi.h>

#include <GLFW/glfw3.h>

#include "./../Application.h"

#include <Timer.h>

#include <thread>

namespace Saddle {

	/**
	 * \brief Contains window properties used for window initialisation.
	*/
	struct WindowProperties {
		/**
		 * \brief Width of the window.
		*/
		int w;

		/**
		 * \brief Height of the window.
		*/
		int h;


		/**
		 * \brief Name of the window.
		*/
		std::string title;

		/**
		 * \brief Whether the window used vsync or not.
		*/
		bool vsync;

		/**
		 * \brief Whether the window is maximised.
		*/
		bool maximised;


		/**
		 * \brief Creates an instance used to initialise a window.
		 * 
		 * \param Title The name of the window.
		 * 
		 * \param width The width of the window.
		 * 
		 * \param height The height of the window.
		 * 
		 * \param Vsync Whether the window uses vsync or not.
		 * 
		 * \param Maximised Whether the window is maximised or not.
		*/
		WindowProperties(const std::string& Title, int width, int height, bool Vsync, bool Maximised) : 
			w(width), h(height), title(Title), vsync(Vsync), maximised(Maximised) {}
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
		Window(const WindowProperties& properties = WindowProperties {"Saddle Window", 1280, 720, false, true});


		/**
		 * \returns A reference to the active window.
		*/
		inline static Window& getActiveWindow() { return *m_activeWindow; }


		/**
		 * \returns The width of the window.
		*/
		inline int w() const { return m_properties->w; }

		/**
		 * \returns The height of the window.
		*/
		inline int h() const { return m_properties->h; }


		/**
		 * \returns Whether the window uses vsync or not.
		*/
		inline bool hasVsync() const { return m_vsync; }

		/**
		 * \param vsync Sets whether the window uses vsync or not.
		*/
		inline void setVsync(bool vsync) { glfwSwapInterval(vsync); this->m_vsync = vsync; }


		/**
		 * \returns Whether the window is maximised or not.
		*/
		inline bool isMaximised() const { return m_maximised; }

		/**
		 * \param maximised Sets whether the window is maximised or not.
		*/
		inline void setMaximised(bool maximised) { if (maximised) glfwMaximizeWindow(m_glfwwindow); this->m_maximised = maximised; }

		std::string toString(int indents) const override;

	private:

		bool m_vsync;
		bool m_maximised;

		friend class Application;

		void update();

		inline bool shouldStop() const { return m_shouldstop; }

		static Window* m_activeWindow;
		WindowProperties* m_properties;
		GLFWwindow* m_glfwwindow;

		bool m_shouldstop = false;
	};
}