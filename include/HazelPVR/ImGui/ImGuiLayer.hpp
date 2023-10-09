#pragma once

#include "Layer.hpp"
#include "Events/MouseEvent.hpp"
#include "Events/KeyEvent.hpp"
#include "Events/ApplicationEvent.hpp"

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