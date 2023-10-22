#pragma once

#include "Buffer.hpp"

namespace HazelPVR
{
    class VertexArray
    {
        public:
            virtual ~VertexArray() {}

            virtual void Bind() const = 0;
            virtual void Unbind() const = 0;

            virtual void AddVertexBuffer(const Ref<VertexBuffer>& VertexBuffer) = 0;
            virtual void SetIndexBuffer(const Ref<IndexBuffer>& IndexBuffer) = 0;

            virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const = 0;
            virtual const Ref<IndexBuffer>& GetIndexexBuffer() const = 0;

            static Ref<VertexArray> Create();
    };
} // namespace HazelPVR
