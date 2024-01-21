#include "ParticleSimulation2D.hpp"

#include <imgui/imgui.h>
#include <glm/gtc/type_ptr.hpp>

ParticleSimulation2D::ParticleSimulation2D()
    : Layer("ParticleSimulation2D")
    , m_CameraController((float)HazelPVR::Application::Get().GetWindow()->GetWidth() /
                         (float)HazelPVR::Application::Get().GetWindow()->GetHeight()) // AR = 2.3888...
    , m_ParticleInitSize({0.1f, 0.1f})
    , m_Bounds(GetBounds(m_CameraController.GetAspectRatio(), m_CameraController.GetZoomLevel(), m_ParticleInitSize))
{}

void ParticleSimulation2D::OnAttach()
{
    m_ParticleTexture = HazelPVR::Texture2D::Create("assets/textures/Particle.png");

    for (auto& particle : m_Particles)
    {
        particle.Init(m_ParticleInitSize, m_Bounds, Distributions::RANDOM_GAUSSIAN);
        m_CameraController.SetZoomLevel(15);
    }
}

void ParticleSimulation2D::OnDetach() {}

void ParticleSimulation2D::OnUpdate(HazelPVR::Timestep ts)
{
    // Update particle properties
    for (auto& particle : m_Particles)
    {
        auto pos = particle.GetPosition();
        auto vel = particle.GetVelocity();

        // Update particel positions
        particle.SetPosition({pos.x + vel.x * ts, pos.y + vel.y * ts});

        // Update screen bounds if zoomlevel changed
        m_Bounds = GetBounds(m_CameraController.GetAspectRatio(), m_CameraController.GetZoomLevel(), m_ParticleInitSize);

        // Invert velocity if particles collide with window bounds
        if (particle.GetPosition().x <= m_Bounds.left || particle.GetPosition().x >= m_Bounds.right)
        {
            if (!particle.HasFlipped(Direction::X))
            {
                vel.x *= -1.0f;
                particle.HasFlipped(Direction::X, true);
            }
        }
        else
            particle.HasFlipped(Direction::X, false);
        if (particle.GetPosition().y <= m_Bounds.bottom || particle.GetPosition().y >= m_Bounds.top)
        {
            if (!particle.HasFlipped(Direction::Y))
            {
                vel.y *= -1.0f;
                particle.HasFlipped(Direction::Y, true);
            }
        }
        else
            particle.HasFlipped(Direction::Y, false);
        particle.SetVelocity(vel);
    }

    // Check for particle-particle collisions
    // for (size_t outer = 0; outer < m_Particles.size(); ++outer) {
    //     for (size_t inner = 0; inner < m_Particles.size(); ++inner) {
    //         if (inner != outer) // Avoid self-interaction
    //         {
    //             float xouter = m_Particles[outer].GetPosition().x;
    //             float youter = m_Particles[outer].GetPosition().y;
    //             float xinner = m_Particles[inner].GetPosition().x;
    //             float yinner = m_Particles[inner].GetPosition().y;
    
    //             auto vel =  m_Particles[outer].GetVelocity();
    //             float radius = 0.25f;
    //             if (xouter > xinner - radius && xouter < xinner + radius) vel.x *= -1.0f;
    //             if (youter > yinner - radius && youter < yinner + radius) vel.y *= -1.0f;
    //             m_Particles[outer].SetVelocity(vel);
    //         }
    //     }
    // }

    // Update
    m_CameraController.OnUpdate(ts);

    // Render
    HazelPVR::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
    HazelPVR::RenderCommand::Clear();

    HazelPVR::Renderer2D::BeginScene(m_CameraController.GetCamera());
    {
        for (auto& particle : m_Particles)
        {
            HazelPVR::Renderer2D::DrawQuad(particle.GetPosition(), particle.GetSize(), m_ParticleTexture, 1.0f, particle.GetColor());
        }
    }
    HazelPVR::Renderer2D::EndScene();
}

void ParticleSimulation2D::OnImGuiRender()
{
    // ImGui::Begin("Engine controls", nullptr, ImGuiWindowFlags_MenuBar);
    // if (ImGui::BeginMenuBar())
    // {
    //     if (ImGui::MenuItem("Exit", "Esc"))
    //     {
    //         HazelPVR::Application& app = HazelPVR::Application::Get();
    //         app.Close();
    //     }
    //     ImGui::EndMenuBar();
    // }
    // // ImGui::ColorEdit4("Quad 1", glm::value_ptr(m_QuadColor1));
    // // ImGui::ColorEdit4("Quad 2", glm::value_ptr(m_QuadColor2));
    // ImGui::End();
}

void ParticleSimulation2D::OnEvent(HazelPVR::Event& e)
{
    HazelPVR::EventDispatcher eventDispatcher(e);
    eventDispatcher.Dispatch<HazelPVR::KeyPressedEvent>(HZPVR_BIND_EVENT_FN(ParticleSimulation2D::OnKeyPressedEvent));

    m_CameraController.OnEvent(e);
}

bool ParticleSimulation2D::OnKeyPressedEvent(HazelPVR::KeyPressedEvent& e)
{
    if (e.GetKeyCode() == HZPVR_KEY_ESCAPE)
    {
        HazelPVR::Application& app = HazelPVR::Application::Get();
        app.Close();
    }
    return false;
}
