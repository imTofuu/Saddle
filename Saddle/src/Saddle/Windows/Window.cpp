#include "Window.h"

namespace Saddle {
	Window* Window::activeWindow = nullptr;

	Window::Window(const WindowProperties& properties) {
		if (!activeWindow) activeWindow = this;

		this->properties = new WindowProperties(properties);
		Logger::getCoreLogger().log("Initialising window with properties:\n", Logger::INFO, *this);

		SDL_CORE_ASSERT(glfwInit(), "Failed to initialise GLFW");
		Logger::getCoreLogger().log("GLFW initialised", Logger::DEBUG);

		glfwwindow = glfwCreateWindow(properties.w, properties.h, properties.title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(glfwwindow);
		gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);


		setVsync(this->properties->vsync);
		setMaximised(this->properties->maximised);
	}

	std::string Window::toString(int indents) const
	{
		std::string str = properties->title += ":\n";
		str += std::string(indents + 1, '	') += "width: ";
		str += std::to_string(properties->w);
		str += "\n";
		str += std::string(indents + 1, '	') += "height: ";
		str += std::to_string(properties->h);
		str += "\n";
		str += std::string(indents + 1, '	') += "vsync: ";
		str += properties->vsync ? "true" : "false";
		str += "\n";
		return str;
	}

	void Window::update() {

		glfwSwapBuffers(glfwwindow);

		glfwPollEvents();

		shouldstop = glfwWindowShouldClose(glfwwindow);

	}
}