#pragma once

#include "HazelPVR/Renderer/OrthographicCamera.hpp"
#include "HazelPVR/Core/Timestep.hpp"

#include "HazelPVR/Events/ApplicationEvent.hpp"
#include "HazelPVR/Events/MouseEvent.hpp"

namespace HazelPVR
{
    class OrthographicCameraController
    {
        public:
            OrthographicCameraController(float aspectRatio, bool rotation = false);

        public:
            OrthographicCamera& GetCamera()
            {
                return m_Camera;
            }
            const OrthographicCamera& GetCamera() const
            {
                return m_Camera;
            }
            void OnUpdate(Timestep ts);
            void OnEvent(Event& e);

        private:
            bool OnMouseScrolled(MouseScrolledEvent e);
            bool OnWindowResized(WindowResizeEvent e);

        private:
            float m_AspectRatio;
            float m_ZoomLevel = 1.0f;
            OrthographicCamera m_Camera;

            bool m_Rotation;

            glm::vec3 m_CameraPosition = {0.0f, 0.0f, 0.0f};
            float m_CameraRotation = 0.0f;
            float m_CameraTranslationSpeed = 5.0f;
            float m_CameraRotationSpeed = 180.0f;
    };
} // namespace HazelPVR