#include "hzpvrpch.h"
#include "ImGui/ImGuiLayer.h"
#include "Core.h"

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include "Application.h"

// TEMPORARY
#include <GLFW/glfw3.h>
//#include <glad/glad.h>


namespace HazelPVR
{
	ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer") { HZPVR_CORE_INFO("Creating new ImGuiLayer instance"); }

	ImGuiLayer::~ImGuiLayer() { HZPVR_CORE_INFO("Destroying ImGuiLayer instance"); }

    void ImGuiLayer::OnAttach()
    {
        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // This does not behave properly in i3wm!

        // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            ImGuiStyle& style = ImGui::GetStyle();
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        Application& app = Application::Get();
        auto* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());

        // Setup Platform/Renderer backends
        const char* glsl_version = "#version 130";
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init(glsl_version);

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();

        // Load Fonts
        float fontSize = 22.0f;// *2.0f;
        ImFont* notosans_regular = io.Fonts->AddFontFromFileTTF("assets/fonts/notosans/NotoSans-Regular.ttf", fontSize);
        IM_ASSERT(notosans_regular != nullptr);
        ImFont* notosans_bold = io.Fonts->AddFontFromFileTTF("assets/fonts/notosans/NotoSans-Bold.ttf", fontSize);
        IM_ASSERT(notosans_bold != nullptr);
        io.FontDefault = notosans_regular;
    }

	void ImGuiLayer::OnDetach()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void ImGuiLayer::Begin()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
	}

    void ImGuiLayer::End()
    {
        // Rendering
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        ImGuiIO& io = ImGui::GetIO();
        Application& app = Application::Get();
        io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }
    }

    void ImGuiLayer::OnImGuiRender()
    {
        ImGui::ShowDemoWindow();
    }
}
