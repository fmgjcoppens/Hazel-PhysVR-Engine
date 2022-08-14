#include "../../include/HazelPVR/Application.h"

namespace HazelPVR {

    Application::Application() {
        // Constructor implementation code
        printf("HazelPVR::Application::Application() (constructor)\n");
    }

    Application::~Application() {
        // Destructor implementation code
        printf("HazelPVR::Application::~Application() (destructor)\n");
    }

    void Application::Run() {
        printf("HazelPVR::Application::Run()\n");
        while (true);
    }

}