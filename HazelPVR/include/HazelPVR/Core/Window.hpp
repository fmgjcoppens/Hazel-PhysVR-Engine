#pragma once

#include <utility>

#include "HazelPVR/Core/Core.hpp"
#include "HazelPVR/Events/Event.hpp"

namespace HazelPVR
{
    struct WindowProperties
    {
            std::string Title;
            unsigned int Width;
            unsigned int Height;

            explicit WindowProperties(std::string title = "HazelPVR Engine", unsigned int width = 1720, unsigned int height = 720) // AR = 2.3888889
                : Title(std::move(title))
                , Width(std::move(width))
                , Height(std::move(height))
            {}
    };

    // Interface representing a desktop system based Window
    class HAZELPVR_API Window
    {
        public:
            using EventCallbackFn = std::function<void(Event&)>;

            virtual ~Window() = default;

            virtual void OnUpdate() = 0;

            virtual unsigned int GetWidth() const = 0;
            virtual unsigned int GetHeight() const = 0;

            // Window attributes
            virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
            virtual void SetVSync(bool enabled) = 0;
            virtual bool IsVSync() const = 0;

            virtual void* GetNativeWindow() const = 0; // In this case retruns a pointer to a GLFWwindow object

            static Scope<Window> Create(const WindowProperties& properties = WindowProperties());
    };
} // namespace HazelPVR