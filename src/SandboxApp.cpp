#include <HazelPVR.h>

class Sandbox : public HazelPVR::Application {
public:
    Sandbox() {
        // Constructor implementation code
        HZPVR_TRACE("Sandbox::Sandbox()");
    }

    ~Sandbox() {
        // Destructor implementation code
        HZPVR_TRACE("Sandbox::~Sandbox()");
    }
};

HazelPVR::Application* HazelPVR::CreateApplication() {
    HZPVR_TRACE("HazelPVR::CreateApplication()");
    return new Sandbox();
}
