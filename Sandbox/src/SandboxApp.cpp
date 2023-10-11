#include <HazelPVR.hpp>

#include <glm/gtc/matrix_transform.hpp>

class ExampleLayer : public HazelPVR::Layer
{
public:
    ExampleLayer()
        : Layer("Example"),
          m_Camera(-1.6f, 1.6f, -1.0f, 1.0f),
          m_CameraPosition(0.0f),
          m_SquarePosition(0.0f)
    {
        HZPVR_INFO("Creating new ExampleLayer instance");

        m_VertexArray.reset(HazelPVR::VertexArray::Create());

        float vertices[3 * 7] = {
            -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
             0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
             0.0f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f
        };

        std::shared_ptr<HazelPVR::VertexBuffer> vertexBuffer;
        vertexBuffer.reset(HazelPVR::VertexBuffer::Create(vertices, sizeof(vertices)));
        HazelPVR::BufferLayout layout = {
            { HazelPVR::ShaderDataType::Float3, "a_Position" },
            { HazelPVR::ShaderDataType::Float4, "a_Color" }
        };
        vertexBuffer->SetLayout(layout);
        m_VertexArray->AddVertexBuffer(vertexBuffer);

        uint32_t indices[3] = {0, 1, 2};
        std::shared_ptr<HazelPVR::IndexBuffer> indexBuffer;
        indexBuffer.reset(HazelPVR::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
        m_VertexArray->SetIndexBuffer(indexBuffer);

        m_SquareVA.reset(HazelPVR::VertexArray::Create());

        float squareVertices[3 * 4] = {
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.5f,  0.5f, 0.0f,
            -0.5f,  0.5f, 0.0f
        };

        std::shared_ptr<HazelPVR::VertexBuffer> squareVB;
        squareVB.reset(HazelPVR::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
        squareVB->SetLayout({
            { HazelPVR::ShaderDataType::Float3, "a_Position" }
        });
        m_SquareVA->AddVertexBuffer(squareVB);

        uint32_t squareIndices[6] = {0, 1, 2, 2, 3, 0};
        std::shared_ptr<HazelPVR::IndexBuffer> squareIB;
        squareIB.reset(HazelPVR::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
        m_SquareVA->SetIndexBuffer(squareIB);

        std::string vertexSrc = R"(
            #version 330 core

            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec4 a_Color;

            uniform mat4 u_ViewProjection;
            uniform mat4 u_Transform;

            out vec3 v_Position;
            out vec4 v_Color;

            void main()
            {
                v_Position = a_Position + 0.0;
                v_Color = a_Color;
                gl_Position = u_ViewProjection * u_Transform * vec4(a_Position - 0.0, 1.0);
            }
        )";

        std::string fragmentSrc = R"(
            #version 330 core

            layout(location = 0) out vec4 color;

            in vec3 v_Position;
            in vec4 v_Color;

            void main()
            {
                color = vec4(v_Position * 0.5 + 0.5, 1.0);
                color = v_Color;
            }
        )";

        m_Shader.reset(new HazelPVR::Shader(vertexSrc, fragmentSrc));

        std::string blueShaderVertexSrc = R"(
            #version 330 core

            layout(location = 0) in vec3 a_Position;

            uniform mat4 u_ViewProjection;
            uniform mat4 u_Transform;

            out vec3 v_Position;

            void main()
            {
                v_Position = a_Position + 0.0;
                gl_Position = u_ViewProjection * u_Transform * vec4(a_Position - 0.0, 1.0);
            }
        )";

        std::string blueShaderFragmentSrc = R"(
            #version 330 core

            layout(location = 0) out vec4 color;

            in vec3 v_Position;

            void main()
            {
                color = vec4(0.2f, 0.3f, 0.8f, 1.0);
            }
        )";

        m_BlueShader.reset(new HazelPVR::Shader(blueShaderVertexSrc, blueShaderFragmentSrc));
    }

    ~ExampleLayer() { HZPVR_INFO("Destroying ExampleLayer instance"); }

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
        if (HazelPVR::Input::IsKeyPressed(HZPVR_KEY_D))
            m_CameraRotation -= m_CameraRotationSpeed * ts;

        HazelPVR::RenderCommand::SetClearColor({0.1f, 0.1f, 0.15f, 1});
        HazelPVR::RenderCommand::Clear();

        m_Camera.SetPosition(m_CameraPosition);
        m_Camera.SetRotation(m_CameraRotation);

        HazelPVR::Renderer::BeginScene(m_Camera);

        static glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.075f));
        glm::mat4 translate = glm::translate(glm::mat4(1.0f), m_SquarePosition);

        for (int i = 0; i < 20; ++i)
        {
            for (int j = 0; j < 20; ++j)
            {
                glm::vec3 pos(0.085f * i, 0.085f * j, 0.0f);
                glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * translate * scale;
                HazelPVR::Renderer::Submit(m_BlueShader, m_SquareVA, transform);
            }
        }

        // HazelPVR::Renderer::Submit(m_BlueShader, m_SquareVA, translate);
        HazelPVR::Renderer::Submit(m_Shader, m_VertexArray);

        HazelPVR::Renderer::EndScene();
    }

    void OnImGuiRender() override
    {
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
    std::shared_ptr<HazelPVR::Shader> m_Shader;
    std::shared_ptr<HazelPVR::VertexArray> m_VertexArray;

    std::shared_ptr<HazelPVR::Shader> m_BlueShader;
    std::shared_ptr<HazelPVR::VertexArray> m_SquareVA;

    HazelPVR::OrthographicCamera m_Camera;

    glm::vec3 m_CameraPosition;
    float m_CameraMoveSpeed = 1.0f;

    float m_CameraRotation = 0.0f;
    float m_CameraRotationSpeed = 180.0f;

    glm::vec3 m_SquarePosition;
    float m_SquareMoveSpeed = 1.0f;
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
