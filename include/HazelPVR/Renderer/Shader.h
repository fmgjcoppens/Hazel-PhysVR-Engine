#pragma once

#include <string>

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
        
        private:
            u_int32_t m_RendererID;
    };

}
