#pragma once

#include "Renderer/GraphicsContext.hpp"

namespace HazelPVR
{
    class OpenGLContext : public GraphicsContext
    {
        public:
            OpenGLContext(GLFWwindow* windowHandle);

            virtual void Init() override;
            virtual void SwapBuffers() override;

        private:
            GLFWwindow* m_windowHandle;
    };
}
