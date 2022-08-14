#include <HazelPVR.h>

class Sandbox : public HazelPVR::Application {
public:
    Sandbox() {
        // Constructor implementation code
        HZPVR_INFO("Sandbox::Sandbox() (constructor)");
    }

    ~Sandbox() {
        // Destructor implementation code
        HZPVR_INFO("Sandbox::~Sandbox() (destructor)");
    }
};

HazelPVR::Application* HazelPVR::CreateApplication() {
    HZPVR_INFO("HazelPVR::CreateApplication()");
    return new Sandbox();
}
