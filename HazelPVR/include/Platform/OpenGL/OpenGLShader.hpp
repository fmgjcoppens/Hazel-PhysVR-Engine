#pragma once

#include "HazelPVR/Renderer/Shader.hpp"

#include <glm/glm.hpp>

namespace HazelPVR
{
    class OpenGLShader : public Shader
    {
        public:
            OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
            virtual ~OpenGLShader();

        public:
            virtual void Bind() const override;
            virtual void UnBind() const override;

            void UploadUniformInt(const std::string& name, const int value);

            void UploadUniformFloat(const std::string& name, const float value);
            void UploadUniformFloat2(const std::string& name, const glm::vec2& vector);
            void UploadUniformFloat3(const std::string& name, const glm::vec3& vector);
            void UploadUniformFloat4(const std::string& name, const glm::vec4& vector);

            void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
            void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);

        private:
            uint32_t m_RendererID;
    };
} // namespace HazelPVR