#pragma once

#include <string>
#include <glm/glm.hpp>

namespace HazelPVR
{

    class Shader
    {
        public:
            Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
            ~Shader();
        
        public:
            void Bind() const;
            void UnBind() const;

            void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
        
        private:
            u_int32_t m_RendererID;
    };

}
