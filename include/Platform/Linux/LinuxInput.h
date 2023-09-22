#pragma once

#include "Input.h"
#include <utility>

namespace HazelPVR {

	class LinuxInput : public Input {
    protected:
        bool IsKeyPressedImpl(int keycode) override;

        bool IsMouseButtonPressedImpl(int button) override;
        virtual std::pair<float, float> GetMousePositionImpl() override;
        float GetMouseXImpl() override;
        float GetMouseYImpl() override;
    };

}
