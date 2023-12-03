#pragma once

#include <HazelPVR.hpp>
#include <array>

class Sandbox2D : public HazelPVR::Layer
{
    public:
        Sandbox2D();
        virtual ~Sandbox2D() = default;

    public:
        virtual void OnAttach() override;
        virtual void OnDetach() override;

        void OnUpdate(HazelPVR::Timestep ts) override;
        void OnImGuiRender() override;
        void OnEvent(HazelPVR::Event& e) override;
        bool OnKeyPressedEvent(HazelPVR::KeyPressedEvent& e);

    private:
        HazelPVR::OrthographicCameraController m_CameraController;

        // tmp
        HazelPVR::Ref<HazelPVR::VertexArray> m_SquareVA;
        HazelPVR::Ref<HazelPVR::Shader> m_FlatColorShader;
        HazelPVR::Ref<HazelPVR::Texture2D> m_Texture;

        glm::vec2 m_Position;
        glm::vec2 m_Size;
        glm::vec4 m_Color;
        float m_MoveSpeed = 5.0f;  
};  
