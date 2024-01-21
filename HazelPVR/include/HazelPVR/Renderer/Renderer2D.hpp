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


            //// Primitives

            // Quads
            static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
            static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
            static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = {1.0f, 1.0f, 1.0f, 1.0f});
            static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = {1.0f, 1.0f, 1.0f, 1.0f});

            // Rotated Quads
            static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color);
            static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color);
            static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = {1.0f, 1.0f, 1.0f, 1.0f});
            static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = {1.0f, 1.0f, 1.0f, 1.0f});
    };

} // namespace HazelPVR
