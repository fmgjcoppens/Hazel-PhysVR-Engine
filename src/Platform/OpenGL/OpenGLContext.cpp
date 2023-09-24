#include "hzpvrpch.h"
#include "OpenGL/OpenGLContext.h"

namespace HazelPVR
{

    OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) 
        : m_windowHandle(windowHandle)
    {
        HZPVR_CORE_ASSERT(windowHandle, "Window handle is null!");
    }

    void OpenGLContext::Init()
    {
        glfwMakeContextCurrent(m_windowHandle);
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        HZPVR_CORE_ASSERT(status, "Failed to initialize Glad!");
    }

    void OpenGLContext::SwapBuffers()
    {
        glfwSwapBuffers(m_windowHandle);
    }

}
