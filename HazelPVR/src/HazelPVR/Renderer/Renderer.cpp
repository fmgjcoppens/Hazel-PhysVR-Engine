#include "hzpvrpch.hpp"

#include "HazelPVR/Renderer/Renderer.hpp"
#include "HazelPVR/Renderer/Renderer2D.hpp"
#include "Platform/OpenGL/OpenGLShader.hpp"

namespace HazelPVR
{
    Ref<Renderer::SceneData> Renderer::m_SceneData = std::make_shared<Renderer::SceneData>();

    void Renderer::Init()
    {
        HZPVR_PROFILE_FUNCTION();
        
        RenderCommand::Init();
        Renderer2D::Init();
    }

    void Renderer::OnWindowResize(uint32_t width, uint32_t height)
    {
        RenderCommand::SetViewPort(0, 0, width, height);
    }

    void Renderer::BeginScene(OrthographicCamera& camera)
    {
        m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
    }

    void Renderer::EndScene() {}

    void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform)
    {
        shader->Bind();
        std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
        std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_Transform", transform);

        vertexArray->Bind();
        RenderCommand::DrawIndexed(vertexArray);
    }
} // namespace HazelPVR
