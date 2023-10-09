#pragma once

#include "Window.hpp"
#include "Renderer/GraphicsContext.hpp"

namespace HazelPVR
{
	class LinuxWindow : public Window
	{
		public:
			explicit LinuxWindow(const WindowProperties& properties);
			~LinuxWindow() override;

			void OnUpdate() override;

			inline unsigned int GetWidth() const override { return m_Data.Width; }
			inline unsigned int GetHeight() const override { return m_Data.Height; }

			// Window attributes
			inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
			void SetVSync(bool enabled) override;
			bool IsVSync() const override;

			inline void* GetNativeWindow() const override { return m_Window; }

		private:
			virtual void Init(const WindowProperties& properties);
			virtual void Shutdown();

			GLFWwindow* m_Window;
			GraphicsContext* m_Context;

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
