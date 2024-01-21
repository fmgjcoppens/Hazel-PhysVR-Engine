#include "Sandbox2D.hpp"

#include <imgui/imgui.h>
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
    : Layer("Sandbox2D")
    , m_CameraController((float)HazelPVR::Application::Get().GetWindow()->GetWidth() /
                         (float)HazelPVR::Application::Get().GetWindow()->GetHeight()) // AR = 2.3888...
    , m_Position({0.0f, 0.0f})
    , m_Size({0.5f, 0.5f})
    , m_Color({0.5f, 0.5f, 1.0f, 1.0f})
{}

void Sandbox2D::OnAttach()
{
    HZPVR_PROFILE_FUNCTION();

    m_Texture = HazelPVR::Texture2D::Create("assets/textures/Checkerboard.png");
}

void Sandbox2D::OnDetach() { HZPVR_PROFILE_FUNCTION(); }

void Sandbox2D::OnUpdate(HazelPVR::Timestep ts)
{
    HZPVR_PROFILE_FUNCTION();

    // Update
    m_CameraController.OnUpdate(ts);

    {
        // Update quad positions
        HZPVR_PROFILE_SCOPE("Update quad position");
        if (HazelPVR::Input::IsKeyPressed(HZPVR_KEY_LEFT))
            m_Position.x -= m_MoveSpeed * ts;
        else if (HazelPVR::Input::IsKeyPressed(HZPVR_KEY_RIGHT))
            m_Position.x += m_MoveSpeed * ts;
        if (HazelPVR::Input::IsKeyPressed(HZPVR_KEY_UP))
            m_Position.y += m_MoveSpeed * ts;
        else if (HazelPVR::Input::IsKeyPressed(HZPVR_KEY_DOWN))
            m_Position.y -= m_MoveSpeed * ts;
    }

    // Render
    {
        HZPVR_PROFILE_SCOPE("Render Prep.");
        HazelPVR::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
        HazelPVR::RenderCommand::Clear();
    }

    {
        HZPVR_PROFILE_SCOPE("Render Draw");
        HazelPVR::Renderer2D::BeginScene(m_CameraController.GetCamera());
        {
            HazelPVR::Renderer2D::DrawRotatedQuad({0.0f, 0.0f, -0.1}, {10, 10}, glm::radians(10.0f), m_Texture, 10.0f, m_Color);
            HazelPVR::Renderer2D::DrawRotatedQuad((glm::vec2){-1, 0} + m_Position, {0.8, 0.8}, glm::radians(45.), {0.8, 0.2, 0.3, 1});
            HazelPVR::Renderer2D::DrawQuad(glm::vec2({0.5, -0.5}) + m_Position, {0.5, 0.75}, {0.2, 0.3, 0.8, 1});
        }
        HazelPVR::Renderer2D::EndScene();
    }
}

void Sandbox2D::OnImGuiRender()
{
    HZPVR_PROFILE_FUNCTION();

    ImGui::Begin("Engine controls", nullptr, ImGuiWindowFlags_MenuBar);
    if (ImGui::BeginMenuBar())
    {
        if (ImGui::MenuItem("Exit", "Esc"))
        {
            HazelPVR::Application& app = HazelPVR::Application::Get();
            app.Close();
        }
        ImGui::EndMenuBar();
    }
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
