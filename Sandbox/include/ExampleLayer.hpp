#pragma once

#include <HazelPVR.hpp>

class ExampleLayer : public HazelPVR::Layer
{
    public:
        ExampleLayer();
        ~ExampleLayer();

    public:
        void OnUpdate(HazelPVR::Timestep ts) override;
        void OnImGuiRender() override;
        void OnEvent(HazelPVR::Event& e) override;
        bool OnKeyPressedEvent(HazelPVR::KeyPressedEvent& e);

    private:
        HazelPVR::ShaderLibrary m_ShaderLibrary;

        HazelPVR::Ref<HazelPVR::VertexArray> m_VertexArray;
        HazelPVR::Ref<HazelPVR::VertexArray> m_SquareVA;

        HazelPVR::Ref<HazelPVR::Texture2D> m_Texture;
        HazelPVR::Ref<HazelPVR::Texture2D> m_MyLogoTexture;

        HazelPVR::OrthographicCameraController m_CameraController;

        glm::vec3 m_SquarePosition{};
        float m_SquareMoveSpeed = 1.0f;

        glm::vec3 m_SquareScaleFactor = {0.075f, 0.075f, 0.075f};
        float m_SquareScaleSpeed = 0.1f;

        glm::vec4 m_SquareColor1 = {0.2f, 0.3f, 0.8f, 1.0f};
        glm::vec4 m_SquareColor2 = {0.8f, 0.3f, 0.2f, 1.0f};
};
