#pragma once

#include "Core.hpp"

#include "Window.hpp"
#include "LayerStack.hpp"
#include "ImGui/ImGuiLayer.hpp"

#include "HazelPVR/Core/Timestep.hpp"

namespace HazelPVR {

    class Application
    {
        public:
            Application();
            virtual ~Application();

        public:
            void Run();
            void onEvent(Event& event);
            void PushLayer(Layer* layer);
            void PushOverlay(Layer* layer);
            inline Window& GetWindow() { return *m_Window; }
            inline static Application& Get() { return *s_Instance; }
            void Close();

        private:
            bool onWindowClose(WindowCloseEvent& event);

        private:
            std::unique_ptr<Window> m_Window;
            ImGuiLayer* m_ImGuiLayer;
            bool m_Running = true;
            LayerStack m_LayerStack;
            float m_LastFrameRenderTime = 0.0f;

        private:
            static Application* s_Instance;
    };

    // To be defined in the CLIENT
    Application* CreateApplication();
}
