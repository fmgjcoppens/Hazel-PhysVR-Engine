#pragma once

extern HazelPVR::Application* HazelPVR::CreateApplication();

int main (int argc, char** argv) {

    HazelPVR::Log::Init();
    auto app = HazelPVR::CreateApplication();
    app->Run();
    delete app;
    return 0;
}