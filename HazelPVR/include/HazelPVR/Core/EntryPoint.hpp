#pragma once

int main(int argc, char** argv)
{
    HazelPVR::Log::Init();

    HZPVR_PROFILE_BEGIN_SESSION("Startup", "HazelPVRProfile_Startup.json");
    auto app = HazelPVR::CreateApplication();
    HZPVR_PROFILE_END_SESSION();

    HZPVR_PROFILE_BEGIN_SESSION("Runtime", "HazelPVRProfile_Runtime.json");
    app->Run();
    HZPVR_PROFILE_END_SESSION();

    HZPVR_PROFILE_BEGIN_SESSION("Shutdown", "HazelPVRProfile_Shutdown.json");
    delete app;
    HZPVR_PROFILE_END_SESSION();

    HZPVR_INFO("Application destroyed");
    return 0;
}