#pragma warning ( disable : 4805 )

#include <glad/glad.h>

#include "Window.h"

#include <SaddleComponents.h>

#include <Timer.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "./../EventDispatcher.h"

namespace Saddle {
	Window* Window::m_activeWindow = nullptr;

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
		success = true;
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		//ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		ImGui::StyleColorsDark();
		success &= ImGui_ImplGlfw_InitForOpenGL(m_glfwwindow, true);
		success &= ImGui_ImplOpenGL3_Init();
		SDL_CORE_ASSERT(success, "Failed to initialise imgui");
		coreLogger.log("imgui initialised", Logger::DEBUG);

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
		str += m_flags;
		str += "\n";
		return str;
	}

	void showStats(double ft, int fps, double fta) {
		// Break out if not visible, collapsed
		if (!ImGui::Begin("Statistics")) {
			ImGui::End();
			return;
		}

		std::string frameTimeString = std::to_string(ft);
		frameTimeString += "ms (Frame time)";
		ImGui::Text(frameTimeString.c_str());

		std::string frameTimeAvg = std::to_string(fta / fps);
		frameTimeAvg += "ms (Frame average last second)";
		ImGui::Text(frameTimeAvg.c_str());

		std::string fpsCurrentString = std::to_string((int)(1000 / ft));
		fpsCurrentString += " fps (Current)";
		ImGui::Text(fpsCurrentString.c_str());

		std::string fpsLastString = std::to_string(fps);
		fpsLastString += " fps (Last second)";
		ImGui::Text(fpsLastString.c_str());

		ImGui::End();
	}

	void explorer() {
		if(!ImGui::Begin("Explorer")) {
			ImGui::End();
			return;
		}

		ImGui::Text("Explorer");
	}

	double frameTimeMillis = 0;
	int framesLastSecond = 0;
	int framesThisSecond = 0;
	double frameTimeAvg = 0;
	double thisavg = 0;
	Timer fpsTimer(true);

	void doImGui() {
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		
		showStats(frameTimeMillis, framesLastSecond, frameTimeAvg);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

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

		Timer timer;
		timer.start();

		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwPollEvents();

		doImGui();

		glfwSwapBuffers(m_glfwwindow);

		m_shouldstop = glfwWindowShouldClose(m_glfwwindow);

		updateFPS(timer);

		EventDispatcher::getMainDispatcher().dispatchUpdate(frameTimeMillis);
	}
}