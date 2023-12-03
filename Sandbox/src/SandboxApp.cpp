#include <HazelPVR.hpp>
#include <HazelPVR/Core/EntryPoint.hpp>

// #include "ExampleLayer.hpp"
#include "Sandbox2D.hpp"
#include "ParticleSimulation2D.hpp"

class Sandbox : public HazelPVR::Application
{
    public:
        Sandbox()
        {
            HZPVR_INFO("Creating new Sandbox instance");
            // PushLayer(std::make_shared<ExampleLayer>());
            PushLayer(std::make_shared<Sandbox2D>());
            // PushLayer(std::make_shared<ParticleSimulation2D>());
        }

        ~Sandbox()
        {
            HZPVR_INFO("Destroying Sandbox instance");
        }
};

HazelPVR::Application* HazelPVR::CreateApplication()
{
    HZPVR_INFO("Creating application");
    return new Sandbox();
}
