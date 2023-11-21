#pragma once

#include "HazelPVR/Core/Core.hpp"
#include "HazelPVR/Core/Window.hpp"
#include "HazelPVR/Core/LayerStack.hpp"
#include "HazelPVR/Core/Timestep.hpp"

#include "HazelPVR/ImGui/ImGuiLayer.hpp"


namespace HazelPVR
{

    class Application
    {
        public:
            Application();
            virtual ~Application();

        public:
            void Run();
            void OnEvent(Event& e);
            void PushLayer(Ref<Layer> layer);
            void PushOverlay(Ref<Layer> layer);
            inline Scope<Window>& GetWindow()
            {
                return m_Window;
            }
            inline static Application& Get()
            {
                return *s_Instance;
            }
            void Close();

        private:
            bool OnWindowClose(WindowCloseEvent& e);
            bool OnWindowResize(WindowResizeEvent& e);

        private:
            Scope<Window> m_Window; // Contains a member function that returns a raw pointer to the native window object (GLFW)
            Ref<ImGuiLayer> m_ImGuiLayer;
            bool m_Running = true;
            bool m_Minimized = false;
            LayerStack m_LayerStack;
            float m_LastFrameRenderTime = 0.0f;

        private:
            static Application* s_Instance;
    };

    // To be defined in the CLIENT
    Application* CreateApplication();
} // namespace HazelPVR
