#include "Window/Window.h"

#include <GLFW/glfw3.h>


void Window::SetTitle(const std::string& title)
{
    glfwSetWindowTitle(m_Handle, title.c_str());
}

void Window::Hide()
{
    glfwHideWindow(m_Handle);
}

void Window::Show()
{
    glfwShowWindow(m_Handle);
}

void Window::Iconify()
{
    glfwIconifyWindow(m_Handle);
}

void Window::Maximize()
{
    glfwMaximizeWindow(m_Handle);
}
