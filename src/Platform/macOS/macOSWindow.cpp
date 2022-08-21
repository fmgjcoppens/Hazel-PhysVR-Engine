#include "hzpvrpch.h"
#include "macOS/macOSWindow.h"

namespace HazelPVR {
	
	static bool s_GLFWInitialized = false;

	Window* Window::Create(const WindowProperties& props) {
		return new macOSWindow(props);
	}

	macOSWindow::macOSWindow(const WindowProperties& props) {
		Init(props);
	}

	macOSWindow::~macOSWindow()	{
		Shutdown();
	}

	void macOSWindow::Init(const WindowProperties& props) {
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

        HZPVR_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

		if (!s_GLFWInitialized)	{
			// TODO: glfwTerminate on system shutdown
			int success = glfwInit();
			HZPVR_CORE_ASSERT(success, "Could not initialize GLFW!");

			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);
	}

	void macOSWindow::Shutdown() {
		glfwDestroyWindow(m_Window);
	}

	void macOSWindow::OnUpdate() {
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void macOSWindow::SetVSync(bool enabled) {
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}

	bool macOSWindow::IsVSync() const {
		return m_Data.VSync;
	}

}
