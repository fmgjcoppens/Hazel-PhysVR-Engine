#pragma once

extern HazelPVR::Application* HazelPVR::CreateApplication();

int main (int argc, char** argv) {
    printf("Welcome to Hazel Physics VR Engine!\n");
    auto app = HazelPVR::CreateApplication();
    app->Run();
    delete app;
    return 0;
}