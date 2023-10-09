#pragma once

#include "HazelPVR/Input.hpp"

#include <utility>

namespace HazelPVR {

	class WindowsInput : public Input {
    protected:
        bool IsKeyPressedImpl(int keycode) override;

        bool IsMouseButtonPressedImpl(int button) override;
        virtual std::pair<float, float> GetMousePositionImpl() override;
        float GetMouseXImpl() override;
        float GetMouseYImpl() override;
    };

}
