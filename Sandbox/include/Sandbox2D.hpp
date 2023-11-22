#pragma once

#include <HazelPVR.hpp>

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

    private:
        HazelPVR::OrthographicCameraController m_CameraController;

        // tmp
        HazelPVR::Ref<HazelPVR::VertexArray> m_SquareVA;
        HazelPVR::Ref<HazelPVR::Shader> m_FlatColorShader;

        glm::vec4 m_SquareColor = {0.2f, 0.3f, 0.8f, 1.0f};
};
