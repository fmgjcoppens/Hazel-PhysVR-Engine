#include "hzpvrpch.hpp"

#include "Platform/OpenGL/OpenGLContext.hpp"

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

        HZPVR_CORE_INFO("OpenGL Info:");
        HZPVR_CORE_INFO("  Vendor: {0}", (const char*) glGetString(GL_VENDOR));
        HZPVR_CORE_INFO("  Renderer: {0}", (const char*) glGetString(GL_RENDERER));
        HZPVR_CORE_INFO("  Version: {0}", (const char*) glGetString(GL_VERSION));
    }

    void OpenGLContext::SwapBuffers()
    {
        glfwSwapBuffers(m_windowHandle);
    }
}
