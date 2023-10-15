#pragma once

int main(int argc, char** argv)
{
    HazelPVR::Log::Init();
    HZPVR_CORE_WARN("Initialized Log!");

    auto app = HazelPVR::CreateApplication();
    app->Run();

    delete app;
    HZPVR_INFO("Application destroyed");

    return 0;
}