#include "HazelPVR.h"

class Sandbox : public HazelPVR::Application {
public:
    Sandbox() {
        // code
    }

    ~Sandbox() {
        // code
    }
};

    int main () {
        Sandbox *sandbox = new Sandbox();
        sandbox->Run();
        delete sandbox;
        return 0;
}