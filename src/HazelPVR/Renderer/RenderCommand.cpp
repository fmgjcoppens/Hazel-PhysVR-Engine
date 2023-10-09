#include "hzpvrpch.hpp"
#include "Renderer/RenderCommand.hpp"

#include "OpenGL/OpenGLRendererAPI.hpp"

namespace HazelPVR
{
    RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}