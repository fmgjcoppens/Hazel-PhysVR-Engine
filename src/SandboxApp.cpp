#include <HazelPVR.h>

class Sandbox : public HazelPVR::Application {
public:
    Sandbox() {
        HZPVR_INFO("Creating new instance of Sandbox");
    }

    ~Sandbox() {
        HZPVR_INFO("Destroying instance of Sandbox");
    }
};

HazelPVR::Application* HazelPVR::CreateApplication() {
    HZPVR_INFO("Creating HazelPVR application");
    return new Sandbox();
}
