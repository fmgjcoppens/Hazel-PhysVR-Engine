#pragma once

extern HazelPVR::Application* HazelPVR::CreateApplication();

int main (int argc, char** argv) {
    HazelPVR::Log::Init();
    HZPVR_CORE_INFO("Initialised Core Logger!");
    int a = 5;
    HZPVR_INFO("Initialised Client Logger! Var = {0}", a);

    auto app = HazelPVR::CreateApplication();
    app->Run();
    delete app;
    return 0;
}