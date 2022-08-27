#include "Layer.h"

namespace HazelPVR {

	Layer::Layer(const std::string& debugName)
		: m_DebugName(debugName) {
	}

	Layer::~Layer()	{
        HZPVR_INFO("Destroying instance of Layer");
	}

}