#pragma once

#include "HazelPVR/Renderer/VertexArray.hpp"

namespace HazelPVR
{
    class OpenGLVertexArray : public VertexArray
    {
        public:
            OpenGLVertexArray();
            virtual ~OpenGLVertexArray();

        public:
            virtual void Bind() const override;
            virtual void Unbind() const override;

            virtual void AddVertexBuffer(const Ref<VertexBuffer>& VertexBuffer) override;
            virtual void SetIndexBuffer(const Ref<IndexBuffer>& IndexBuffer) override;

            virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const override
            {
                return m_VertexBuffers;
            }
            virtual const Ref<IndexBuffer>& GetIndexexBuffer() const override
            {
                return m_IndexBuffer;
            }

        private:
            uint32_t m_RendererID;
            std::vector<Ref<VertexBuffer>> m_VertexBuffers;
            Ref<IndexBuffer> m_IndexBuffer;
    };
} // namespace HazelPVR