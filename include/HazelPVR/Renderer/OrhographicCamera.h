#pragma once

#include <glm/glm.hpp>

namespace HazelPVR
{
    class OrhographicCamera
    {
    public:
        OrhographicCamera(float left, float right, float bottom, float top);
    
    public:
        const glm::vec3 GetPosition() const { return m_Position; }
        void SetPosition(const glm::vec3& position) { m_Position = position; RecalcualteViewMatrix(); }

        const float GetRotation() const { return m_Rotation; }
        void SetRotation(float rotation) { m_Rotation = rotation; RecalcualteViewMatrix(); } 

        const glm::mat4 GetProjectionMatrix() const { return m_ProjectionMatrix; }
        const glm::mat4 GetViewMatrix() const { return m_ViewMatrix; }
        const glm::mat4 GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

    private:
        void RecalcualteViewMatrix();

    private:
        glm::mat4 m_ProjectionMatrix;
        glm::mat4 m_ViewMatrix;
        glm::mat4 m_ViewProjectionMatrix;

        glm::vec3 m_Position;
        float m_Rotation = 0.0f;
    };
}