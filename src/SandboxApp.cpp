#include <HazelPVR.h>
#include <imgui.h>

class ExampleLayer : public HazelPVR::Layer
{
public:
    ExampleLayer() : Layer("Example")
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
            -0.75f, -0.75f, 0.0f,
             0.75f, -0.75f, 0.0f,
             0.75f,  0.75f, 0.0f,
            -0.75f,  0.75f, 0.0f
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

            out vec3 v_Position;
            out vec4 v_Color;

            void main()
            {
                v_Position = a_Position + 0.0;
                v_Color = a_Color;
                gl_Position = vec4(a_Position - 0.0, 1.0);
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

            out vec3 v_Position;

            void main()
            {
                v_Position = a_Position + 0.0;
                gl_Position = vec4(a_Position - 0.0, 1.0);
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
    void OnUpdate() override
    {
        HazelPVR::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
        HazelPVR::RenderCommand::Clear();

        HazelPVR::Renderer::BeginScene();
        {
            m_BlueShader->Bind();  
            HazelPVR::Renderer::Submit(m_SquareVA);
            
            m_Shader->Bind();
            HazelPVR::Renderer::Submit(m_VertexArray);
        }
        HazelPVR::Renderer::EndScene();
    }

    void OnImGuiRender() override
    {
    }

    void OnEvent(HazelPVR::Event& event) override
    {
        if (event.GetEventType() == HazelPVR::EventType::KeyPressed)
        {
            auto& e = (HazelPVR::KeyPressedEvent&) event;

            if (e.GetKeyCode() == HZPVR_KEY_ESCAPE || e.GetKeyCode() == HZPVR_KEY_Q)
            {
                HazelPVR::Application& app = HazelPVR::Application::Get();
                app.Close();
            }
            
            HZPVR_TRACE("{0}", (char)e.GetKeyCode());
        }
    }

private:
    std::shared_ptr<HazelPVR::Shader> m_Shader;
    std::shared_ptr<HazelPVR::VertexArray> m_VertexArray;

    std::shared_ptr<HazelPVR::Shader> m_BlueShader;
    std::shared_ptr<HazelPVR::VertexArray> m_SquareVA;
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
