#pragma once

#include "HazelPVR/Renderer/OrthographicCamera.hpp"
#include "HazelPVR/Renderer/Texture.hpp"

namespace HazelPVR
{
    class Renderer2D
    {
        public:
            static void Init();
            static void ShutDown();

            static void BeginScene(const OrthographicCamera& camera);
            static void EndScene();

            // Primitives
            static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
            static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
            static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture);
            static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture);
            static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, float scale);
            static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, float scale);
            static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec4& texcolblend);
            static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec4& texcolblend);
    };

} // namespace HazelPVR
