#include <HazelPVR.h>
#include <imgui.h>

class ExampleLayer : public HazelPVR::Layer
{
    public:
        ExampleLayer() : Layer("Example") {}

        void OnUpdate() override
        {
            if (HazelPVR::Input::IsKeyPressed(HZPVR_KEY_TAB))
                HZPVR_TRACE("Tab key is pressed (poll)!");
        }

        void OnImGuiRender() override
        {
            static bool opt_fullscreen = true;
            static bool opt_padding = false;
            static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

            ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
            if (opt_fullscreen)
            {
                const ImGuiViewport* viewport = ImGui::GetMainViewport();
                ImGui::SetNextWindowPos(viewport->WorkPos);
                ImGui::SetNextWindowSize(viewport->WorkSize);
                ImGui::SetNextWindowViewport(viewport->ID);
                ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
                ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
                window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
                window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
            }
            else
            {
                dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
            }

            if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
                window_flags |= ImGuiWindowFlags_NoBackground;

            if (!opt_padding) ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

            ImGui::Begin("DockSpace", nullptr, window_flags);

            if (!opt_padding) ImGui::PopStyleVar();

            if (opt_fullscreen) ImGui::PopStyleVar(2);

            // Submit the DockSpace
            ImGuiIO& io = ImGui::GetIO();
            if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
            {
                ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
                ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
            }

            if (ImGui::BeginMenuBar())
            {
                if (ImGui::BeginMenu("Options"))
                {
                    ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen);
                    ImGui::MenuItem("Padding", NULL, &opt_padding);
                    ImGui::EndMenu();
                }
                ImGui::EndMenuBar();
            }

            // A small window just to quit the application
            ImGui::Begin("Exit application");
            HazelPVR::Application& app = HazelPVR::Application::Get();
            if (ImGui::Button("Quit")) app.SetState(false);
            ImGui::End();

            // A viewport window
            ImGui::Begin("Viewport");
            ImGui::End();

            ImGui::End();
        }

        void OnEvent(HazelPVR::Event& event) override
        {

            if (event.GetEventType() == HazelPVR::EventType::KeyPressed) {
                auto& e = (HazelPVR::KeyPressedEvent&)event;
                if (e.GetKeyCode() == HZPVR_KEY_TAB)
                    HZPVR_TRACE("Tab key is pressed (event)!");
                HZPVR_TRACE("{0}", (char)e.GetKeyCode());
            }
        }
};

class Sandbox : public HazelPVR::Application
{
    public:
        Sandbox()
        {
            HZPVR_INFO("Creating new instance of Sandbox");
            // PushOverlay(new HazelPVR::ImGuiLayer());     // I chose to do this in the constructor of HazelPVR::Application because without this overlay we can't really do anything. So since it always needs to be created (not optional) we might as well do it in the contructor.
            PushLayer(new ExampleLayer());
        }

        ~Sandbox() override
        {
            HZPVR_INFO("Destroying instance of Sandbox");
        }
};

HazelPVR::Application* HazelPVR::CreateApplication()
{
    HZPVR_INFO("Creating HazelPVR application");
    return new Sandbox();
}
