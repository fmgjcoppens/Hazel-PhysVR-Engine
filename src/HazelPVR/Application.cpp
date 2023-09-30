#include "hzpvrpch.h" // Precompiled header. Include not necessary with CMake
#include "Application.h"

#include "Events/ApplicationEvent.h"

#include <glad/glad.h>

#include "Input.h"

namespace HazelPVR
{

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

    Application* Application::s_Instance = nullptr;

    static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
    {
        switch(type)
        {
            case ShaderDataType::None:   return GL_INT;
            case ShaderDataType::Bool:   return GL_BOOL;
            case ShaderDataType::Int:    return GL_INT;
            case ShaderDataType::Int2:   return GL_INT;
            case ShaderDataType::Int3:   return GL_INT;
            case ShaderDataType::Int4:   return GL_INT;
            case ShaderDataType::Float:  return GL_FLOAT;
            case ShaderDataType::Float2: return GL_FLOAT;
            case ShaderDataType::Float3: return GL_FLOAT;
            case ShaderDataType::Float4: return GL_FLOAT;
            case ShaderDataType::Mat3:   return GL_FLOAT;
            case ShaderDataType::Mat4:   return GL_FLOAT;
        }

        HZPVR_CORE_ASSERT(false, "Unknown ShaderDataType!");
        return 0;
    }

    Application::Application()
    {
        HZPVR_CORE_ASSERT(!s_Instance, "Application already exists!");
        HZPVR_CORE_INFO("Creating new Application instance");
        s_Instance = this;
        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(BIND_EVENT_FN(onEvent));

        // This can also be done in the Sandbox class (SandBoxApp.cpp) on the application side, but I chose to do it here because its creation is not optional; if it's not created GLFW/ImGui will not initialize correctly!
        m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

        glGenVertexArrays(1, &m_VertexArray);
        glBindVertexArray(m_VertexArray);

        float vertices[3 * 7] = {
            -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
             0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
             0.0f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f
        };
        m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

        {
            BufferLayout layout = {
                { ShaderDataType::Float3, "a_Position" },
                { ShaderDataType::Float4, "a_Color" }
            };

            m_VertexBuffer->SetLayout(layout);
        }

        uint32_t index = 0;
        const auto& layout = m_VertexBuffer->GetLayout();
        for (const auto& element : layout)
        {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(index,
                element.GetComponentCount(),
                ShaderDataTypeToOpenGLBaseType(element.Type),
                element.Normalized ? GL_TRUE : GL_FALSE,
                layout.GetStride(),
                (const void*)element.Offset);
            index++;
        }

        uint32_t indices[3] = {0, 1, 2};
        m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));


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

        m_Shader.reset(new Shader(vertexSrc, fragmentSrc));
    }

    Application::~Application() { HZPVR_INFO("Destroying Application instance"); }

    void Application::PushLayer(Layer* layer) {
        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer* layer) {
        m_LayerStack.PushOverlay(layer);
        layer->OnAttach();
    }

    void Application::onEvent(Event& event) {
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(onWindowClose));

        HZPVR_CORE_TRACE("{0}", event);

        for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); ) {
            (*--it)->OnEvent(event);
            if (event.Handled) break;
        }
    }

    void Application::Run() {
        while (m_Running)
        {
            glClearColor(0.1f, 0.1f, 0.1f, 1);
            glClear(GL_COLOR_BUFFER_BIT);

            m_Shader->Bind();
            glBindVertexArray(m_VertexArray);
            glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

            for (Layer* layer : m_LayerStack) layer->OnUpdate();

            m_ImGuiLayer->Begin();
            for (Layer* layer : m_LayerStack) layer->OnImGuiRender();
            m_ImGuiLayer->End();

            m_Window->OnUpdate();
        }
    }

    void Application::Close() { m_Running = false; }

    bool Application::onWindowClose(WindowCloseEvent& event) {
        m_Running = false;
        return true;
    }

}