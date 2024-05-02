#include "WindowsWindow.h"

namespace Saddle {

	Window* Window::createWindow(const WindowProperties& properties) {
		return new WindowsWindow(properties);
	}

	std::string WindowsWindow::toString(int indents) const
	{
		std::string str = properties->title += ":\n";
		str += std::string(indents + 1, '	') += "width: ";
		str += std::to_string(properties->w);
		str += "\n";
		str += std::string(indents + 1, '	') += "height: ";
		str += std::to_string(properties->h);
		str += "\n";
		return str;
	}

	WindowsWindow::WindowsWindow(const WindowProperties& properties) {
		this->properties = new WindowProperties(properties);
		Logger::getCoreLogger().log("Initialising window with properties:\n", Logger::INFO, *this);

		SDL_CORE_ASSERT(glfwInit(), "Failed to initialise GLFW");
		Logger::getCoreLogger().log("GLFW initialised", Logger::DEBUG);

		window = glfwCreateWindow(properties.w, properties.h, properties.title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(window);
		setVsync(true);
	}

	WindowsWindow::~WindowsWindow() {
		delete properties;
	}

	void setVsync(bool vsync) {
		glfwSwapInterval(vsync);
		this->vsync = vsync;
	}
}