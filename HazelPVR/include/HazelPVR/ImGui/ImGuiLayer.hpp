#pragma once

#include "HazelPVR/Layer.hpp"

#include "HazelPVR/Events/MouseEvent.hpp"
#include "HazelPVR/Events/KeyEvent.hpp"
#include "HazelPVR/Events/ApplicationEvent.hpp"

namespace HazelPVR {

	class HAZELPVR_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnImGuiRender() override;

        void Begin();
        void End();

	private:
		// float m_Time = 0.0f;
	};

}