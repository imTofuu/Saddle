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

		inline bool hasVsync() const override { return vsync; }
		void setVsync(bool vsync) override;

		std::string toString(int indents) const override;

	private:
		bool vsync = false;
		WindowProperties* properties;
		GLFWwindow* window;
	};
}