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
            // PushLayer(HazelPVR::CreateRef<ExampleLayer>());
            PushLayer(HazelPVR::CreateRef<Sandbox2D>());
            // PushLayer(HazelPVR::CreateRef<ParticleSimulation2D>());
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
