#include "hzpvrpch.hpp"

#include "Platform/OpenGL/OpenGLContext.hpp"

#include <glad/glad.h>

namespace HazelPVR
{
    OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
        : m_windowHandle(windowHandle)
    {
        HZPVR_CORE_ASSERT(windowHandle, "Window handle is null!");
    }

    void OpenGLContext::Init()
    {
        HZPVR_PROFILE_FUNCTION();

        glfwMakeContextCurrent(m_windowHandle);

        int success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        HZPVR_CORE_ASSERT(success, "Failed to initialize Glad!");

        HZPVR_CORE_INFO("OpenGL Info:");
        HZPVR_CORE_INFO("  Vendor: {0}", (const char*)glGetString(GL_VENDOR));
        HZPVR_CORE_INFO("  Renderer: {0}", (const char*)glGetString(GL_RENDERER));
        HZPVR_CORE_INFO("  Version: {0}", (const char*)glGetString(GL_VERSION));
    }

    void OpenGLContext::SwapBuffers()
    {
        HZPVR_PROFILE_FUNCTION();

        glfwSwapBuffers(m_windowHandle);
    }
} // namespace HazelPVR
