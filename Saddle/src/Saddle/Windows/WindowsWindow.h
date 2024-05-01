#pragma once

#include <SaddleApi.h>
#include "Window.h"

namespace Saddle {
	class WindowsWindow : public Window {
	public:
		WindowsWindow(const WindowProperties& properties);
		~WindowsWindow() override;

		int w() const override { return properties->w; }
		int h() const override { return properties->h; }

		std::string toString(int indents) const override;

	private:
		WindowProperties* properties;
		GLFWwindow* window;
	};
}