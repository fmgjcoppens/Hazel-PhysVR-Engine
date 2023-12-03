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
    m_Texture = HazelPVR::Texture2D::Create("assets/textures/Checkerboard.png");
}

void Sandbox2D::OnDetach() {}

void Sandbox2D::OnUpdate(HazelPVR::Timestep ts)
{
    // Update
    m_CameraController.OnUpdate(ts);

    // Change position of squares
    if (HazelPVR::Input::IsKeyPressed(HZPVR_KEY_LEFT))
        m_Position.x -= m_MoveSpeed * ts;
    else if (HazelPVR::Input::IsKeyPressed(HZPVR_KEY_RIGHT))
        m_Position.x += m_MoveSpeed * ts;
    if (HazelPVR::Input::IsKeyPressed(HZPVR_KEY_UP))
        m_Position.y += m_MoveSpeed * ts;
    else if (HazelPVR::Input::IsKeyPressed(HZPVR_KEY_DOWN))
        m_Position.y -= m_MoveSpeed * ts;

    // Render
    HazelPVR::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
    HazelPVR::RenderCommand::Clear();

    HazelPVR::Renderer2D::BeginScene(m_CameraController.GetCamera());
    {
        HazelPVR::Renderer2D::DrawQuad(m_Position, m_Size, m_Texture, m_Color);
    }
    HazelPVR::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
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
    // ImGui::ColorEdit4("Quad 1", glm::value_ptr(m_QuadColor1));
    // ImGui::ColorEdit4("Quad 2", glm::value_ptr(m_QuadColor2));
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
