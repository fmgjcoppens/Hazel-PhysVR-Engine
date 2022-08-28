#include <HazelPVR.h>

class ExampleLayer : public HazelPVR::Layer {
public:
    ExampleLayer()
            : Layer("Example") {
    }

    void OnUpdate() override {
        HZPVR_INFO("ExampleLayer::Update");
    }

    void OnEvent(HazelPVR::Event& event) override {
        HZPVR_TRACE("{0}", event);
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
