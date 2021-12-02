#include "Window/WindowSubsystem.h"

#include <GLFW/glfw3.h>

#include "Window/WindowChannel.h"

void WindowSubsystem::Initialize()
{
    glfwInit();

    m_OpenWindowCallback.Init(this, &WindowSubsystem::HandleOpenWindowRequest);
    m_CloseWindowCallback.Init(this, &WindowSubsystem::HandleCloseWindowRequest);
    m_ApplicationUpdatedCallback.Init(this, &WindowSubsystem::HandleApplicationUpdatedEvent);

    m_EventListener.ConnectHandler(&m_OpenWindowCallback);
    m_EventListener.ConnectHandler(&m_CloseWindowCallback);
    m_EventListener.ConnectHandler(&m_ApplicationUpdatedCallback);

    m_EventListener.JoinChannel(WindowChannel::GetChannel());
}

void WindowSubsystem::Shutdown()
{
    m_EventListener.LeaveChannel(WindowChannel::GetChannel());

    m_EventListener.DisconnectHandler(&m_OpenWindowCallback);
    m_EventListener.DisconnectHandler(&m_CloseWindowCallback);
    m_EventListener.DisconnectHandler(&m_ApplicationUpdatedCallback);

    m_OpenWindowCallback.Reset();
    m_CloseWindowCallback.Reset();
    m_ApplicationUpdatedCallback.Reset();

    glfwTerminate();
}

void WindowSubsystem::Update()
{
    glfwPollEvents();
    
    for (GLFWwindow* handle : m_Windows)
    {
        Window* window = (Window*) glfwGetWindowUserPointer(handle);
        window->BeginFrame();

        WindowRenderEvent event;
        event.SetWindow(window);
        event.Broadcast();

        window->EndFrame();
    }
}

void WindowSubsystem::HandleOpenWindowRequest(const OpenWindowRequest& event)
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

void WindowSubsystem::HandleCloseWindowRequest(const CloseWindowRequest& event)
{

}

void WindowSubsystem::HandleApplicationUpdatedEvent(const ApplicationUpdatedEvent& event)
{
    
}