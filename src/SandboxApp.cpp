#include "HazelPVR.h"

class Sandbox : public HazelPVR::Application {
public:
    Sandbox() {
        // Constructor implementation code
        printf("Sandbox::Sandbox() (constructor)\n");
    }

    ~Sandbox() {
        // Destructor implementation code
        printf("Sandbox::~Sandbox() (destructor)\n");
    }
};

HazelPVR::Application* HazelPVR::CreateApplication() {
    printf("HazelPVR::CreateApplication()\n");
    return new Sandbox();
}
