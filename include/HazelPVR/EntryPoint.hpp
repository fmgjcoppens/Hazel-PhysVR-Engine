#pragma once

int main (int argc, char** argv)
{
    HazelPVR::Log::Init();

    auto app = HazelPVR::CreateApplication();
    app->Run();

    delete app;
    HZPVR_INFO("Application destroyed");

    return 0;
}