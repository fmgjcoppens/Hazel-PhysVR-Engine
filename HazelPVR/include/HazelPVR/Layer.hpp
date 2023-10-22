#pragma once

#include "Core.hpp"
#include "Events/Event.hpp"

#include "Core/Timestep.hpp"

namespace HazelPVR
{
    class HAZELPVR_API Layer
    {
        public:
            explicit Layer(const std::string& name = "Layer");
            virtual ~Layer();

            virtual void OnAttach() {}
            virtual void OnDetach() {}
            virtual void OnUpdate(Timestep ts) {}
            virtual void OnImGuiRender() {}
            virtual void OnEvent(Event& event) {}

            inline const std::string& GetName() const
            {
                return m_DebugName;
            }

        protected:
            std::string m_DebugName;
    };
} // namespace HazelPVR
