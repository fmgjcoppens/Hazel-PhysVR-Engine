#include "hzpvrpch.hpp"

#include "HazelPVR/Renderer/OrthographicCameraController.hpp"

#include "HazelPVR/Core/Input.hpp"
#include "HazelPVR/Core/KeyCodes.hpp"

namespace HazelPVR
{
    OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
        : m_AspectRatio(aspectRatio)
        , m_Rotation(rotation)
        , m_Camera(-aspectRatio * m_ZoomLevel, aspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel)
    {}

    void OrthographicCameraController::OnUpdate(Timestep ts)
    {

        if (Input::IsKeyPressed(HZPVR_KEY_J))
            m_CameraPosition.x -= m_CameraTranslationSpeed * ts;
        else if (Input::IsKeyPressed(HZPVR_KEY_L))
            m_CameraPosition.x += m_CameraTranslationSpeed * ts;

        if (Input::IsKeyPressed(HZPVR_KEY_I))
            m_CameraPosition.y += m_CameraTranslationSpeed * ts;
        else if (Input::IsKeyPressed(HZPVR_KEY_K))
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

	void OrthographicCameraController::OnResize(float width, float height)
	{
        HZPVR_WARN("Current zoom level: {0}", m_ZoomLevel);
        HZPVR_WARN("Current aspect ratio: {0}", m_AspectRatio);
        HZPVR_WARN("Current aspect ratio x zoom level: {0}", m_AspectRatio * m_ZoomLevel);

		m_AspectRatio = width / height;

        HZPVR_WARN("New window width: {0}", width);
        HZPVR_WARN("New window height: {0}", height);
        HZPVR_WARN("New aspect ratio: {0}", m_AspectRatio);

		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		m_ZoomLevel -= e.GetYOffset() * 0.25f;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		OnResize((float)e.GetWidth(), (float)e.GetHeight());
		return false;
	}

} // namespace HazelPVR