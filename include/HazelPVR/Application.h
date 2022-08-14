#pragma once

#include "Log.h"

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