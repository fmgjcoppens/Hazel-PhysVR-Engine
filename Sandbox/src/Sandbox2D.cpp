#include "Sandbox2D.hpp"

#include <imgui/imgui.h>
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
    : Layer("Sandbox2D")
    , m_CameraController((float)HazelPVR::Application::Get().GetWindow()->GetWidth() /
                         (float)HazelPVR::Application::Get().GetWindow()->GetHeight()) // AR = 2.3888...
{}

void Sandbox2D::OnAttach() {}

void Sandbox2D::OnDetach() {}

void Sandbox2D::OnUpdate(HazelPVR::Timestep ts)
{
    // Update
    m_CameraController.OnUpdate(ts);

    // Render
    HazelPVR::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
    HazelPVR::RenderCommand::Clear();

    HazelPVR::Renderer2D::BeginScene(m_CameraController.GetCamera());
    {
        HazelPVR::Renderer2D::DrawQuad({0.0f, 0.0f}, {1.0f, 1.0f}, {0.8f, 0.2f, 0.3f, 1.0f});
    }
    HazelPVR::Renderer2D::EndScene();
    // TODO: Add these functions - Shader::SetMat4, Shader::SetFloat4
}

void Sandbox2D::OnImGuiRender()
{
    ImGui::Begin("Settings");
    ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
    ImGui::End();
}

void Sandbox2D::OnEvent(HazelPVR::Event& e)
{
    HazelPVR::EventDispatcher eventDispatcher(e);
    eventDispatcher.Dispatch<HazelPVR::KeyPressedEvent>(HZPVR_BIND_EVENT_FN(Sandbox2D::OnKeyPressedEvent));

    m_CameraController.OnEvent(e);
}

bool Sandbox2D::OnKeyPressedEvent(HazelPVR::KeyPressedEvent& e)
{
    if (e.GetKeyCode() == HZPVR_KEY_ESCAPE)
    {
        HazelPVR::Application& app = HazelPVR::Application::Get();
        app.Close();
    }
    return false;
}
