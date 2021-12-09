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
    void SetHandle(GLFWwindow* window) { m_Handle = window; }
    GLFWwindow* GetHandle() const { return m_Handle; }

    void SetImGuiContext(ImGuiContext* context) { m_ImGuiContext = context; }
    ImGuiContext* GetImGuiContext() const { return m_ImGuiContext; }

    bool IsVisible() const;
    bool ShouldClose() const;

    void SetTitle(const std::string& title);
    void SetPosition(int32_t x, int32_t y);
    void SetSize(uint32_t width, uint32_t height);
    void SetVisible(bool visible);
    void Iconify();
    void Maximize();

private:
    GLFWwindow* m_Handle{ nullptr };
    ImGuiContext* m_ImGuiContext{ nullptr };
    bool m_Visible{ false };
};