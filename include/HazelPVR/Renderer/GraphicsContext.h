#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace HazelPVR
{
    class GraphicsContext
    {
        public:
            virtual void Init() = 0;
            virtual void SwapBuffers() = 0;
    };
}