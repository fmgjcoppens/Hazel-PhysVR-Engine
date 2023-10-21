#include <HazelPVR.hpp>

#include "Platform/OpenGL/OpenGLShader.hpp"

#include <imgui/imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public HazelPVR::Layer
{
    public:
        ExampleLayer()
            : Layer("Example")
            , m_Camera(-1.6f, 1.6f, -1.0f, 1.0f)
            , m_CameraPosition(0.0f)
            , m_SquarePosition(0.0f)
            , m_SquareScaleFactor(0.075f)
        {
            HZPVR_INFO("Creating new ExampleLayer instance");

            m_VertexArray.reset(HazelPVR::VertexArray::Create());

            // clang-format off
            float vertices[3 * 7] = {
                -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
                 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
                 0.0f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f
            };
            // clang-format on

            HazelPVR::Ref<HazelPVR::VertexBuffer> vertexBuffer;
            vertexBuffer = HazelPVR::VertexBuffer::Create(vertices, sizeof(vertices));

            HazelPVR::BufferLayout layout = {
                {HazelPVR::ShaderDataType::Float3, "a_Position"}, {HazelPVR::ShaderDataType::Float4, "a_Color"}};
            vertexBuffer->SetLayout(layout);

            m_VertexArray->AddVertexBuffer(vertexBuffer);

            uint32_t indices[3] = {0, 1, 2};
            HazelPVR::Ref<HazelPVR::IndexBuffer> indexBuffer;
            indexBuffer = HazelPVR::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
            m_VertexArray->SetIndexBuffer(indexBuffer);

            m_SquareVA.reset(HazelPVR::VertexArray::Create());

            // clang-format off
            float squareVertices[4 * 5] = {
                -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
                 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
                 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
                -0.5f,  0.5f, 0.0f, 0.0f, 1.0f
            };
            // clang-format on

            HazelPVR::Ref<HazelPVR::VertexBuffer> squareVB;
            squareVB = HazelPVR::VertexBuffer::Create(squareVertices, sizeof(squareVertices));

            // clang-format off
            squareVB->SetLayout({
                {HazelPVR::ShaderDataType::Float3, "a_Position"},
                {HazelPVR::ShaderDataType::Float2, "a_TexCoord"}
            });
            // clang-format on
            m_SquareVA->AddVertexBuffer(squareVB);

            uint32_t squareIndices[6] = {0, 1, 2, 2, 3, 0};
            HazelPVR::Ref<HazelPVR::IndexBuffer> squareIB;
            squareIB = HazelPVR::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
            m_SquareVA->SetIndexBuffer(squareIB);

            auto basicShader = m_ShaderLibrary.Load("assets/shaders/Basic.glsl");
            auto flatColorShader = m_ShaderLibrary.Load("assets/shaders/FlatColor.glsl");
            auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

            m_Texture = HazelPVR::Texture2D::Create("assets/textures/Checkerboard.png");
            m_MyLogoTexture = HazelPVR::Texture2D::Create("assets/textures/ChernoLogo.png");

            std::dynamic_pointer_cast<HazelPVR::OpenGLShader>(textureShader)->Bind();
            std::dynamic_pointer_cast<HazelPVR::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);
        }

        ~ExampleLayer()
        {
            HZPVR_INFO("Destroying ExampleLayer instance");
        }

    public:
        void OnUpdate(HazelPVR::Timestep ts) override
        {
            // HZPVR_TRACE("Delta time: {0}s, {1}ms", ts.GetSeconds(), ts.GetMilliseconds());

            if (HazelPVR::Input::IsKeyPressed(HZPVR_KEY_J))
                m_SquarePosition.x -= m_SquareMoveSpeed * ts;
            else if (HazelPVR::Input::IsKeyPressed(HZPVR_KEY_L))
                m_SquarePosition.x += m_SquareMoveSpeed * ts;

            if (HazelPVR::Input::IsKeyPressed(HZPVR_KEY_I))
                m_SquarePosition.y += m_SquareMoveSpeed * ts;
            else if (HazelPVR::Input::IsKeyPressed(HZPVR_KEY_K))
                m_SquarePosition.y -= m_SquareMoveSpeed * ts;

            if (HazelPVR::Input::IsKeyPressed(HZPVR_KEY_LEFT))
                m_CameraPosition.x -= m_CameraMoveSpeed * ts;
            else if (HazelPVR::Input::IsKeyPressed(HZPVR_KEY_RIGHT))
                m_CameraPosition.x += m_CameraMoveSpeed * ts;

            if (HazelPVR::Input::IsKeyPressed(HZPVR_KEY_UP))
                m_CameraPosition.y += m_CameraMoveSpeed * ts;
            else if (HazelPVR::Input::IsKeyPressed(HZPVR_KEY_DOWN))
                m_CameraPosition.y -= m_CameraMoveSpeed * ts;

            if (HazelPVR::Input::IsKeyPressed(HZPVR_KEY_A))
                m_CameraRotation += m_CameraRotationSpeed * ts;
            else if (HazelPVR::Input::IsKeyPressed(HZPVR_KEY_D))
                m_CameraRotation -= m_CameraRotationSpeed * ts;

            if (HazelPVR::Input::IsKeyPressed(HZPVR_KEY_W))
                m_SquareScaleFactor += m_SquareScaleSpeed * ts;
            else if (HazelPVR::Input::IsKeyPressed(HZPVR_KEY_S))
                m_SquareScaleFactor -= m_SquareScaleSpeed * ts;

            HazelPVR::RenderCommand::SetClearColor({0.1f, 0.1f, 0.15f, 1});
            HazelPVR::RenderCommand::Clear();

            m_Camera.SetPosition(m_CameraPosition);
            m_Camera.SetRotation(m_CameraRotation);

            HazelPVR::Renderer::BeginScene(m_Camera);
            {
                { // Grid of colored squares
                    glm::mat4 scale = glm::scale(glm::mat4(1.0f), m_SquareScaleFactor);
                    glm::mat4 translate = glm::translate(glm::mat4(1.0f), m_SquarePosition);

                    auto flatColorShader = m_ShaderLibrary.Get("FlatColor");
                    std::dynamic_pointer_cast<HazelPVR::OpenGLShader>(flatColorShader)->Bind();
                    for (int x = 0; x < 20; ++x)
                    {
                        for (int y = 0; y < 20; ++y)
                        {
                            glm::vec3 pos(0.085f * x, 0.085f * y, 0.0f);
                            glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * translate * scale;
                            if ((x + y) % 2 == 0)
                                std::dynamic_pointer_cast<HazelPVR::OpenGLShader>(flatColorShader)
                                    ->UploadUniformFloat4("u_Color", m_SquareColor1);
                            else
                                std::dynamic_pointer_cast<HazelPVR::OpenGLShader>(flatColorShader)
                                    ->UploadUniformFloat4("u_Color", m_SquareColor2);

                            HazelPVR::Renderer::Submit(flatColorShader, m_SquareVA, transform);
                        }
                    }
                }

                // { // Render triangle
                //     auto basicShader = m_ShaderLibrary.Get("Basic");
                //     HazelPVR::Renderer::Submit(basicShader, m_VertexArray);
                // }

                { // A square with 2 superimposed textures with blending
                    auto textureShader = m_ShaderLibrary.Get("Texture");
                    m_Texture->Bind();
                    HazelPVR::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

                    m_MyLogoTexture->Bind();
                    HazelPVR::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
                }
            }
            HazelPVR::Renderer::EndScene();
        }

        void OnImGuiRender() override
        {
            ImGui::Begin("Settings");

            ImGui::ColorEdit4("Square Color 1", glm::value_ptr(m_SquareColor1));
            ImGui::ColorEdit4("Square Color 2", glm::value_ptr(m_SquareColor2));

            ImGui::End();
        }

        void OnEvent(HazelPVR::Event& event) override
        {
            HazelPVR::EventDispatcher keyPressDispacher(event);
            keyPressDispacher.Dispatch<HazelPVR::KeyPressedEvent>(HZPVR_BIND_EVENT_FN(ExampleLayer::OnKeyPressedEvent));
        }

        bool OnKeyPressedEvent(HazelPVR::KeyPressedEvent& event)
        {
            if (event.GetKeyCode() == HZPVR_KEY_ESCAPE || event.GetKeyCode() == HZPVR_KEY_Q)
            {
                HazelPVR::Application& app = HazelPVR::Application::Get();
                app.Close();
            }

            return false;
        }

    private:
        HazelPVR::ShaderLibrary m_ShaderLibrary;

        HazelPVR::Ref<HazelPVR::VertexArray> m_VertexArray;
        HazelPVR::Ref<HazelPVR::VertexArray> m_SquareVA;

        HazelPVR::Ref<HazelPVR::Texture2D> m_Texture;
        HazelPVR::Ref<HazelPVR::Texture2D> m_MyLogoTexture;

        HazelPVR::OrthographicCamera m_Camera;

        glm::vec3 m_CameraPosition;
        float m_CameraMoveSpeed = 1.0f;

        float m_CameraRotation = 0.0f;
        float m_CameraRotationSpeed = 180.0f;

        glm::vec3 m_SquarePosition;
        float m_SquareMoveSpeed = 1.0f;

        glm::vec3 m_SquareScaleFactor;
        float m_SquareScaleSpeed = 0.1f;

        glm::vec4 m_SquareColor1 = {0.2f, 0.3f, 0.8f, 0.5f};
        glm::vec4 m_SquareColor2 = {0.8f, 0.3f, 0.2f, 0.5f};
};

class Sandbox : public HazelPVR::Application
{
    public:
        Sandbox()
        {
            HZPVR_INFO("Creating new Sandbox instance");
            PushLayer(new ExampleLayer());
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
