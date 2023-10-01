#include "hzpvrpch.h"
#include "Renderer/RenderCommand.h"

#include "OpenGL/OpenGLRendererAPI.h"

namespace HazelPVR
{
    RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}