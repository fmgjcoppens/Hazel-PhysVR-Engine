#pragma once

#include "Window.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace HazelPVR {

	class macOSWindow : public Window {
	public:
		explicit macOSWindow(const WindowProperties& properties);
		~macOSWindow() override;

		void OnUpdate() override;

		[[nodiscard]] inline unsigned int GetWidth() const override { return m_Data.Width; }
		[[nodiscard]] inline unsigned int GetHeight() const override { return m_Data.Height; }

		// Window attributes
		inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

        [[nodiscard]] inline void* GetNativeWindow() const override { return m_Window; }
    private:
		virtual void Init(const WindowProperties& properties);
		virtual void Shutdown();

		GLFWwindow* m_Window{};

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};

}