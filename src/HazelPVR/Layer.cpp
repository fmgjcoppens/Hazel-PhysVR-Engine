#include "Layer.h"

namespace HazelPVR
{

	Layer::Layer(const std::string& debugName) : m_DebugName(debugName)
	{
		std::cout << m_DebugName << " Layer created!" << std::endl;
	}

	Layer::~Layer()
	{
        HZPVR_INFO("Destroying instance of Layer");
	}

}