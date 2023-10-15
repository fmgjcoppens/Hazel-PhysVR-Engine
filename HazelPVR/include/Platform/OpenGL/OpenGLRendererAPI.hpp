#pragma once

#include "HazelPVR/Renderer/RendererAPI.hpp"

namespace HazelPVR
{
    class OpenGLRendererAPI : public RendererAPI
    {
        public:
            virtual void SetClearColor(const glm::vec4& color) override;
            virtual void Clear() override;

            virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) override;
    };
} // namespace HazelPVR