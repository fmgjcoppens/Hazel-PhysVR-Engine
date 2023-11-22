#include "Sandbox2D.hpp"

#include "Platform/OpenGL/OpenGLShader.hpp"

#include <imgui/imgui.h>
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
    : Layer("Sandbox2D")
    , m_CameraController((float)HazelPVR::Application::Get().GetWindow()->GetWidth() /
                         (float)HazelPVR::Application::Get().GetWindow()->GetHeight()) // AR = 2.3888...
{}

void Sandbox2D::OnAttach()
{
    m_SquareVA = HazelPVR::VertexArray::Create();

    // clang-format off
    float squareVertices[4 * 3] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f
    };
    // clang-format on

    HazelPVR::Ref<HazelPVR::VertexBuffer> squareVB;
    squareVB = HazelPVR::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
    squareVB->SetLayout({{HazelPVR::ShaderDataType::Float3, "a_Position"}});
    m_SquareVA->AddVertexBuffer(squareVB);

    uint32_t squareIndices[6] = {0, 1, 2, 2, 3, 0};
    HazelPVR::Ref<HazelPVR::IndexBuffer> squareIB;
    squareIB = HazelPVR::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
    m_SquareVA->SetIndexBuffer(squareIB);

    m_FlatColorShader = HazelPVR::Shader::Create("assets/shaders/FlatColor.glsl");
}

void Sandbox2D::OnDetach() {}

void Sandbox2D::OnUpdate(HazelPVR::Timestep ts)
{
    // Update
    m_CameraController.OnUpdate(ts);

    // Render
    HazelPVR::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
    HazelPVR::RenderCommand::Clear();

    HazelPVR::Renderer::BeginScene(m_CameraController.GetCamera());
    {
        std::dynamic_pointer_cast<HazelPVR::OpenGLShader>(m_FlatColorShader)->Bind();
        std::dynamic_pointer_cast<HazelPVR::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);

        HazelPVR::Renderer::Submit(m_FlatColorShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
    }
    HazelPVR::Renderer::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
    ImGui::Begin("Settings");
    ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
    ImGui::End();
}

void Sandbox2D::OnEvent(HazelPVR::Event& e)
{
    m_CameraController.OnEvent(e);
}
