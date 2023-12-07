#pragma once

#include "HazelPVR/Core/Layer.hpp"

#include "HazelPVR/Events/MouseEvent.hpp"
#include "HazelPVR/Events/KeyEvent.hpp"
#include "HazelPVR/Events/ApplicationEvent.hpp"

namespace HazelPVR
{
    class HAZELPVR_API ImGuiLayer : public Layer
    {
        public:
            ImGuiLayer();
            ~ImGuiLayer();

            virtual void OnAttach() override;
            virtual void OnDetach() override;

            void Begin();
            void End();
    };
} // namespace HazelPVR