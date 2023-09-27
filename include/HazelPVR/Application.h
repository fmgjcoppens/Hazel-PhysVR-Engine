#pragma once

#include "Core.h"
#include "Window.h"
#include "LayerStack.h"
#include "Events/ApplicationEvent.h"

#include "ImGui/ImGuiLayer.h"

#include "Renderer/Shader.h"

namespace HazelPVR {

    class HAZELPVR_API Application
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
            unsigned int GetVertexArray() { return m_VertexArray; }
            inline static Application& Get() { return *s_Instance; }
            void Close();

        private:
            bool onWindowClose(WindowCloseEvent& event);

        private:
            std::unique_ptr<Window> m_Window;
            ImGuiLayer* m_ImGuiLayer;
            bool m_Running = true;
            LayerStack m_LayerStack;
            static Application* s_Instance;

            unsigned int m_VertexArray, m_VertexBuffer, m_IndexBuffer;
            std::unique_ptr<Shader> m_Shader;
    };

    // To be defined in the CLIENT
    Application* CreateApplication();
}
