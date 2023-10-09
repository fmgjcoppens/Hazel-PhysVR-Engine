#include "hzpvrpch.hpp"

#include "HazelPVR/Renderer/RenderCommand.hpp"

#include "Platform/OpenGL/OpenGLRendererAPI.hpp"

namespace HazelPVR
{
    RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}