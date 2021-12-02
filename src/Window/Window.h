#pragma once

#include <string>
#include <imgui.h>

// Forward declaration from GLFW (to avoid including it everywhere)
struct GLFWwindow;

struct WindowHints
{
    std::string     Title = "Window";
    int32_t         X = 0;
    int32_t         Y = 0;
    uint32_t        Width = 800;
    uint32_t        Height = 450;
};


class Window
{
public:
    GLFWwindow* GetHandle() const { return m_Handle; }
    ImGuiContext* GetImGuiContext() const { return m_ImGuiContext; }

    void SetTitle(const std::string& title);
    void Hide();
    void Show();
    void Iconify();
    void Maximize();

private:
    GLFWwindow* m_Handle{ nullptr };
    ImGuiContext* m_ImGuiContext{ nullptr };

    friend class WindowSubsystem;
};