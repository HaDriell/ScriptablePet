#include "UI/Window/WindowManager.h"

#include <GLFW/glfw3.h>

#include "UI/Window/WindowChannel.h"

void WindowManager::Initialize()
{
    glfwInit();

    m_OpenWindowCallback.Init(this, &WindowManager::HandleOpenWindowRequest);
    m_CloseWindowCallback.Init(this, &WindowManager::HandleCloseWindowRequest);
    m_EventListener.ConnectHandler(&m_OpenWindowCallback);
    m_EventListener.ConnectHandler(&m_CloseWindowCallback);
    m_EventListener.JoinChannel(WindowChannel::GetChannel());
}

void WindowManager::Shutdown()
{
    m_EventListener.LeaveChannel(WindowChannel::GetChannel());
    m_EventListener.DisconnectHandler(&m_OpenWindowCallback);
    m_EventListener.DisconnectHandler(&m_CloseWindowCallback);
    m_OpenWindowCallback.Reset();
    m_CloseWindowCallback.Reset();

    glfwTerminate();
}

void WindowManager::Update()
{
    glfwPollEvents();

    for (auto window : m_ManagedWindows)
    {
        window->BeginFrame();

        WindowRenderEvent event;
        event.SetWindow(window);
        event.Broadcast();

        window->EndFrame();
    }
}

void WindowManager::HandleOpenWindowRequest(const OpenWindowRequest& event)
{
    if (event.GetWindow()->GetHandle() != nullptr)
    {
        return;
    }

    glfwDefaultWindowHints();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

}

void WindowManager::HandleCloseWindowRequest(const CloseWindowRequest& event)
{

}


WindowManager& WindowManager::GetInstance()
{
    static WindowManager instance;
    return instance;
}