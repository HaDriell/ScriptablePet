#include "Window/Window.h"

#include "Window/WindowEvents.h"

#include <GLFW/glfw3.h>

bool Window::IsVisible() const
{
    return m_Visible;
}

bool Window::ShouldClose() const
{
    return glfwWindowShouldClose(m_Handle);
}

void Window::SetTitle(const std::string& title)
{
    glfwSetWindowTitle(m_Handle, title.c_str());
}

void Window::SetPosition(int32_t x, int32_t y)
{
    glfwSetWindowPos(m_Handle, x, y);
}

void Window::SetSize(uint32_t width, uint32_t height)
{
    glfwSetWindowSize(m_Handle, width, height);
}

void Window::SetVisible(bool visible)
{
    m_Visible = visible;
}

void Window::Iconify()
{
    glfwIconifyWindow(m_Handle);
}

void Window::Maximize()
{
    glfwMaximizeWindow(m_Handle);
}
