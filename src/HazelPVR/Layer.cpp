#include "Layer.hpp"

namespace HazelPVR
{

	Layer::Layer(const std::string& debugName) : m_DebugName(debugName)
	{
		HZPVR_CORE_INFO("Creating new instance of Layer '{0}'", debugName);
	}

	Layer::~Layer()
	{
        HZPVR_CORE_INFO("Destroying instance of Layer");
	}

}