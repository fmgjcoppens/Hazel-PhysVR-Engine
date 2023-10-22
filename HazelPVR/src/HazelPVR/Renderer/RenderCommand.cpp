#include "hzpvrpch.hpp"

#include "HazelPVR/Renderer/RenderCommand.hpp"

#include "Platform/OpenGL/OpenGLRendererAPI.hpp"

namespace HazelPVR
{
    Ref<RendererAPI> RenderCommand::s_RendererAPI = std::make_shared<OpenGLRendererAPI>();
}