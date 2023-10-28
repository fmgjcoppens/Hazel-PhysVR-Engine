#include "hzpvrpch.hpp"

#include "HazelPVR/OrthographicCameraController.hpp"

#include "HazelPVR/Input.hpp"
#include "HazelPVR/KeyCodes.hpp"

namespace HazelPVR
{
    OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
        : m_AspectRatio(aspectRatio)
        , m_Rotation(rotation)
        , m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel)
    {}

    void OrthographicCameraController::OnUpdate(Timestep ts)
    {

        if (Input::IsKeyPressed(HZPVR_KEY_LEFT))
            m_CameraPosition.x -= m_CameraTranslationSpeed * ts;
        else if (Input::IsKeyPressed(HZPVR_KEY_RIGHT))
            m_CameraPosition.x += m_CameraTranslationSpeed * ts;

        if (Input::IsKeyPressed(HZPVR_KEY_UP))
            m_CameraPosition.y += m_CameraTranslationSpeed * ts;
        else if (Input::IsKeyPressed(HZPVR_KEY_DOWN))
            m_CameraPosition.y -= m_CameraTranslationSpeed * ts;

        if (m_Rotation)
        {
            if (Input::IsKeyPressed(HZPVR_KEY_RIGHT_SHIFT))
                m_CameraRotation += m_CameraRotationSpeed * ts;
            else if (Input::IsKeyPressed(HZPVR_KEY_END))
                m_CameraRotation -= m_CameraRotationSpeed * ts;

            m_Camera.SetRotation(m_CameraRotation);
        }

        m_Camera.SetPosition(m_CameraPosition);
        m_CameraTranslationSpeed = m_ZoomLevel;
    }

    void OrthographicCameraController::OnEvent(Event& e)
    {
        EventDispatcher dispacher(e);
        dispacher.Dispatch<MouseScrolledEvent>(HZPVR_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
        dispacher.Dispatch<WindowResizeEvent>(HZPVR_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
    }

    bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent e)
    {
        m_ZoomLevel -= e.GetYOffset() * 0.5f;
        m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
        m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);

        return false;
    }

    bool OrthographicCameraController::OnWindowResized(WindowResizeEvent e)
    {
        m_AspectRatio -= (float)e.GetWidth() / (float)e.GetHeight();
        m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
        return false;
    }

} // namespace HazelPVR