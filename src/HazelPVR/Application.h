#pragma once

#include <stdio.h>

namespace HazelPVR {


    class Application {
    public:
        Application();
        virtual ~Application();
        void Run();
    };

    // To be defined in the CLIENT
    Application* CreateApplication();


}