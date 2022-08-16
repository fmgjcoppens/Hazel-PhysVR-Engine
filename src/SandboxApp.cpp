#include <HazelPVR.h>

class Sandbox : public HazelPVR::Application {
public:
    Sandbox() {
        // Constructor implementation code
        HZPVR_INFO("Sandbox::Sandbox() (CONSTRUCTOR)");
    }

    ~Sandbox() {
        // Destructor implementation code
        HZPVR_INFO("Sandbox::~Sandbox() (DESTRUCTOR)");
    }
};

HazelPVR::Application* HazelPVR::CreateApplication() {
    HZPVR_INFO("HazelPVR::CreateApplication()");
    return new Sandbox();
}
