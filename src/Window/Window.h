#pragma once

#include <string>
#include <imgui.h>

// Forward declaration from GLFW (to avoid including it everywhere)
struct GLFWwindow;

struct WindowHints
{
    std::string     Title;
    uint32_t        X;
    uint32_t        Y;
    uint32_t        Width;
    uint32_t        Height;
};


class Window
{
public:
    GLFWwindow* GetHandle() const { return m_Handle; }

    void Create(const WindowHints& hints);
    void Destroy();

    void BeginFrame();
    void EndFrame();

private:
    GLFWwindow* m_Handle{ nullptr };
    ImGuiContext* m_ImGuiContext{ nullptr };
};