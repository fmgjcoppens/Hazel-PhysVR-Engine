#pragma once

#include "Core.h"
#include "Window.h"
#include "LayerStack.h"
#include "Events/ApplicationEvent.h"

namespace HazelPVR {

    class HAZELPVR_API Application {
    public:
        Application();
        virtual ~Application();
        void Run();
        void onEvent(Event& event);
        void PushLayer(Layer* layer);
        void PushOverLay(Layer* layer);

    private:
        bool onWindowClose(WindowCloseEvent& event);

        std::unique_ptr<Window> m_Window;
        bool m_Running = true;
        LayerStack  m_LayerStack;
    };

    // To be defined in the CLIENT
    Application* CreateApplication();

}
