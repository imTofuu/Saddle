#pragma warning ( disable : 4805 )

#include <glad/glad.h>

#include "Window.h"

#include "../util/Time.h"
#include "../util/Timer.h"
#include "../EventDispatcher.h"
#include "../Logging/Logger.h"
#include "../Layers/LayerManager.h"
#include "../Layers/SaddleLayers.h"

#include "../Scenes/Scene.h"

namespace Saddle {
	Window* Window::m_activeWindow = nullptr;

	Window::Window(const std::string& title, int width, int height, uint64_t flags = 0) {
		if (!m_activeWindow) m_activeWindow = this;

		const Logger& coreLogger = Logger::getCoreLogger();

		m_title = title;
		m_width = width;
		m_height = height;
		m_flags = flags;
		m_time = Time();

		// Creating copy of properties and logging them
		coreLogger.log("Initialising window with properties:\n", Logger::INFO, *this);

		// Validating GLFW
		bool success = true;
		success &= glfwInit();
		const GLFWvidmode* mode = 0;
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
		if(flags & SaddleWindowFlags_IsBorderless) {
			const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
			glfwWindowHint(GLFW_RED_BITS, mode->redBits);
			glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
			glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
			glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
		}
		glfwWindowHint(GLFW_DECORATED, !(flags & SaddleWindowFlags_IsBorderless));
		m_glfwwindow = glfwCreateWindow(width, height, title.c_str(), 
			flags & (SaddleWindowFlags_IsFullscreen | SaddleWindowFlags_IsBorderless) ? 
				glfwGetPrimaryMonitor() : 0, 0);
		success &= m_glfwwindow != 0;
		glfwMakeContextCurrent(m_glfwwindow);
		glfwSwapInterval(flags & SaddleWindowFlags_UseVsync);
		if (flags & SaddleWindowFlags_StartMaximised) glfwMaximizeWindow(m_glfwwindow);
		SDL_CORE_ASSERT(success, "Failed to initialise GLFW");
		coreLogger.log("GLFW initialised", Logger::DEBUG);

		// Validating glad
		PassedArgs args;
		args.next((void*)glfwGetProcAddress);
		LayerManager::addLayer<GameLayer>(0, &args);
		coreLogger.log("glad loaded", Logger::DEBUG);

		// Validating imgui
		args = PassedArgs();
		args.next(m_glfwwindow);
		LayerManager::addLayer<CoreGuiLayer>(0, &args);
		coreLogger.log("imgui loaded", Logger::DEBUG);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		coreLogger.log("Window created", Logger::DEBUG);
	}

	static int framesThisSecond = 0;
	static Timer fpsTimer(true);
	static Timer frameTimer;

	void Window::update() {

		frameTimer.start();

		glfwPollEvents();

		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		for(auto & layer : LayerManager::getLayers()) {
			layer->onUpdate();
		}

		glfwSwapBuffers(m_glfwwindow);

		m_shouldstop = glfwWindowShouldClose(m_glfwwindow);

		m_time.delta = frameTimer.current();
		framesThisSecond++;
		if(fpsTimer.current() >= 1000) {
			m_time.fls = framesThisSecond;
			framesThisSecond = 0;
			fpsTimer.start();
		}
		m_time.fps = 1000 / m_time.delta;
		m_time.avg_delta = (m_time.delta + m_time.avg_delta) / 2;


		EventDispatcher::getMainDispatcher().dispatchUpdate(m_time.delta);
	}

	std::string Window::toString(int indents) const
	{
		std::string str = m_title + ":\n";
		str += std::string(indents + 1, '	') += "width: ";
		str += std::to_string(m_width);
		str += "\n";
		str += std::string(indents + 1, '	') += "height: ";
		str += std::to_string(m_height);
		str += "\n";
		str += std::string(indents + 1, '	') += "flags: ";
		str += std::to_string(m_flags);
		str += "\n";
		return str;
	}
}