#pragma warning ( disable : 4805 )

#include <glad/glad.h>

#include "Window.h"

#include "../util/Timer.h"

#include "./../EventDispatcher.h"

#include "../Logging/Logger.h"

#include "../Layers/LayerManager.h"

#include "../Layers/ImGuiLayer.h"

namespace Saddle {
	Window* Window::m_activeWindow = nullptr;
	ImGuiLayer imguilayer;

	Window::Window(const std::string& title, int width, int height, uint64_t flags = 0) {
		if (!m_activeWindow) m_activeWindow = this;

		const Logger& coreLogger = Logger::getCoreLogger();

		m_title = title;
		m_width = width;
		m_height = height;
		m_flags = flags;

		// Creating copy of properties and logging them
		coreLogger.log("Initialising window with properties:\n", Logger::INFO, *this);

		// Validating GLFW
		bool success = true;
		success &= glfwInit();
		m_glfwwindow = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
		success &= m_glfwwindow != 0;
		glfwMakeContextCurrent(m_glfwwindow);
		SDL_CORE_ASSERT(success, "Failed to initialise GLFW");
		coreLogger.log("GLFW initialised", Logger::DEBUG);

		// Validating glad
		success = true;
		success &= gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		SDL_CORE_ASSERT(success, "Failed to load glad");
		coreLogger.log("glad loaded", Logger::DEBUG);

		// Validating imgui
		PassedArgs args;
		args.next(m_glfwwindow);
		imguilayer = LayerManager::addLayer<ImGuiLayer>(0, &args);

		glfwSwapInterval(flags & SaddleWindowFlags_UseVsync);
		if (flags & SaddleWindowFlags_StartMaximised) glfwMaximizeWindow(m_glfwwindow);

		coreLogger.log("Window properties applied", Logger::DEBUG);
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

	static double frameTimeMillis = 0;
	static int framesLastSecond = 0;
	static int framesThisSecond = 0;
	static double frameTimeAvg = 0;
	static double thisavg = 0;
	static Timer fpsTimer(true);

	void updateFPS(Timer& timer) {
		framesThisSecond++;
		thisavg += frameTimeMillis;
		if (fpsTimer.current() >= 1000) {
			framesLastSecond = framesThisSecond;
			framesThisSecond = 0;

			frameTimeAvg = thisavg;
			thisavg = 0;

			fpsTimer.start();
		}

		frameTimeMillis = timer.current();
	}

	void Window::update() {

		// Make stats window
		PassedArgs args;
		args.next(&frameTimeMillis);
		args.next(&frameTimeAvg);
		args.next(&framesLastSecond);
        imguilayer.addImGuiObjectForFrame([] (const PassedArgs* args) -> void {
            if(!ImGui::Begin("Statistics")) {
                ImGui::End();
                return;
            }
            
            std::string fts = std::to_string(*(double*)(*args)[0]);
            fts += "ms (Frame time)";
            ImGui::Text(fts.c_str());

            std::string fta = std::to_string((*(double*)(*args)[1]) / (*(double*)(*args)[2]));
            fta += "ms (Frame time average last second)";
            ImGui::Text(fta.c_str());

            std::string fpsc = std::to_string((int)(1000 / (*(double*)(*args)[0])));
            fpsc += "fps (Current)";
            ImGui::Text(fpsc.c_str());

            std::string fpsa = std::to_string(*(double*)(*args)[2]);
            fpsa += "fps (Last second)";
            ImGui::Text(fpsa.c_str());

            ImGui::End();
        }, &args);

		Timer timer;
		timer.start();

		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwPollEvents();

		//doImGui();
		for(auto & layer : LayerManager::getLayers()) {
			layer->onUpdate(0);
		}

		glfwSwapBuffers(m_glfwwindow);

		m_shouldstop = glfwWindowShouldClose(m_glfwwindow);

		updateFPS(timer);

		EventDispatcher::getMainDispatcher().dispatchUpdate(frameTimeMillis);
	}
}