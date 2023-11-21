#pragma once

#include "Core.hpp"
#include "Layer.hpp"

namespace HazelPVR
{

    class HAZELPVR_API LayerStack
    {
        public:
            LayerStack();
            ~LayerStack();

            void PushLayer(Ref<Layer> layer);
            void PushOverlay(Ref<Layer> overlay);
            void PopLayer(Ref<Layer> layer);
            void PopOverlay(Ref<Layer> overlay);

            std::vector<Ref<Layer>>::iterator begin()
            {
                return m_Layers.begin();
            }

            std::vector<Ref<Layer>>::iterator end()
            {
                return m_Layers.end();
            }

        private:
            std::vector<Ref<Layer>> m_Layers;
            std::vector<Ref<Layer>>::iterator m_LayerInsert;
            unsigned int m_LayerInsertIndex = 0;
    };

} // namespace HazelPVR
