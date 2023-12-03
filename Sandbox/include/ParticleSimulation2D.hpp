#pragma once

#include "Particle2D.hpp"

#include <HazelPVR.hpp>
#include <array>

class ParticleSimulation2D : public HazelPVR::Layer
{
    public:
        ParticleSimulation2D();
        virtual ~ParticleSimulation2D() = default;

    public:
        virtual void OnAttach() override;
        virtual void OnDetach() override;

        void OnUpdate(HazelPVR::Timestep ts) override;
        void OnImGuiRender() override;
        void OnEvent(HazelPVR::Event& e) override;
        bool OnKeyPressedEvent(HazelPVR::KeyPressedEvent& e);

    private:
        Bound GetBounds(float aspect_ratio, float zoomlevel, glm::vec2 size)
        {
            Bound bound;
            bound.left = (-aspect_ratio + 0.5f * size.x) * zoomlevel;
            bound.right = (aspect_ratio - 0.5f * size.x)* zoomlevel;
            bound.top = (1.0f - 0.5f * size.y) * zoomlevel;
            bound.bottom = (-1.0f + 0.5f * size.y) * zoomlevel;
            return bound;
        }

    private:
        HazelPVR::OrthographicCameraController m_CameraController;

        // tmp
        HazelPVR::Ref<HazelPVR::VertexArray> m_SquareVA;
        HazelPVR::Ref<HazelPVR::Shader> m_FlatColorShader;
        HazelPVR::Ref<HazelPVR::Texture2D> m_ParticleTexture;
        std::array<Particle2D, 1000> m_Particles;
        glm::vec2 m_ParticleInitSize;
        Bound m_Bounds;
};
