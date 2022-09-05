#include <HazelPVR.h>

class ExampleLayer : public HazelPVR::Layer {
public:
    ExampleLayer()
            : Layer("Example") {
    }

    void OnUpdate() override {

        if (HazelPVR::Input::IsKeyPressed(HZPVR_KEY_TAB))
            HZPVR_TRACE("Tab key is pressed (poll)!");
    }

    void OnEvent(HazelPVR::Event& event) override {

        if (event.GetEventType() == HazelPVR::EventType::KeyPressed) {
            auto& e = (HazelPVR::KeyPressedEvent&)event;
            if (e.GetKeyCode() == HZPVR_KEY_TAB)
                HZPVR_TRACE("Tab key is pressed (event)!");
            HZPVR_TRACE("{0}", (char)e.GetKeyCode());
        }
    }

};

class Sandbox : public HazelPVR::Application {
public:
    Sandbox() {
        HZPVR_INFO("Creating new instance of Sandbox");
        PushLayer(new ExampleLayer());
        PushOverlay(new HazelPVR::ImGuiLayer());
    }

    ~Sandbox() override {
        HZPVR_INFO("Destroying instance of Sandbox");
    }
};

HazelPVR::Application* HazelPVR::CreateApplication() {
    HZPVR_INFO("Creating HazelPVR application");
    return new Sandbox();
}
