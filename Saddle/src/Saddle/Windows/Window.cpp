#include "Window.h"

#include <SaddleObjects.h>
#include <SaddleComponents.h>

namespace Saddle {
	Window* Window::m_activeWindow = nullptr;

	Window::Window(const WindowProperties& properties) {
		if (!m_activeWindow) m_activeWindow = this;

		const Logger& coreLogger = Logger::getCoreLogger();

		// Creating copy of properties and logging them
		this->m_properties = new WindowProperties(properties);
		coreLogger.log("Initialising window with properties:\n", Logger::INFO, *this);

		// Validating GLFW
		bool success = true;
		success &= glfwInit();
		m_glfwwindow = glfwCreateWindow(properties.w, properties.h, properties.title.c_str(), nullptr, nullptr);
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
		ImGui::StyleColorsDark();
		success &= ImGui_ImplGlfw_InitForOpenGL(m_glfwwindow, true);
		success &= ImGui_ImplOpenGL3_Init();
		SDL_CORE_ASSERT(success, "Failed to initialise imgui");
		coreLogger.log("imgui initialised", Logger::DEBUG);

		setVsync(this->m_properties->vsync);
		setMaximised(this->m_properties->maximised);

		coreLogger.log("Window properties applied", Logger::DEBUG);

		Scene scene;
		Object& obj = scene.addObject("valuetest");
		obj.addComponent<TransformComponent>();
		scene.addObject("gergs");
		coreLogger.log(Logger::INFO, scene);
	}

	std::string Window::toString(int indents) const
	{
		std::string str = m_properties->title += ":\n";
		str += std::string(indents + 1, '	') += "width: ";
		str += std::to_string(m_properties->w);
		str += "\n";
		str += std::string(indents + 1, '	') += "height: ";
		str += std::to_string(m_properties->h);
		str += "\n";
		str += std::string(indents + 1, '	') += "vsync: ";
		str += m_properties->vsync ? "true" : "false";
		str += "\n";
		str += std::string(indents + 1, '	') += "maximised: ";
		str += m_properties->maximised ? "true" : "false";
		str += "\n";
		return str;
	}

	void showStats(double ft, int fps, double fta) {
		bool closeButton = false;

		// Break out if not visible, collapsed
		if (!ImGui::Begin("Statistics", &closeButton)) {
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

	double frameTimeMillis = 0;
	int framesLastSecond = 0;
	int framesThisSecond = 0;
	double frameTimeAvg = 0;
	double thisavg = 0;
	Timer fpsTimer(true);
	void Window::update() {

		Timer timer;
		timer.start();

		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwPollEvents();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		
		showStats(frameTimeMillis, framesLastSecond, frameTimeAvg);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(m_glfwwindow);


		m_shouldstop = glfwWindowShouldClose(m_glfwwindow);

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
}