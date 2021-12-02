#pragma once

#include <vector>
#include <memory>

#include "Core/Application/Subsystem.h"
#include "Core/Application/ApplicationEvents.h"
#include "Core/Application/ApplicationChannel.h"

#include "Core/Event/EventHandler.h"
#include "Core/Event/EventListener.h"

#include "Window/Window.h"
#include "Window/WindowEvents.h"

struct GLFWwindow;

class WindowSubsystem : public Subsystem
{
public:
    using Subsystem::Subsystem;
    
    void Initialize() final;
    void Shutdown() final;
    void Update();


private:
    void HandleOpenWindowRequest(const OpenWindowRequest& event);
    void HandleCloseWindowRequest(const CloseWindowRequest& event);
    void HandleApplicationUpdatedEvent(const ApplicationUpdatedEvent& event);

private:
    EventCallback<WindowSubsystem, OpenWindowRequest> m_OpenWindowCallback;
    EventCallback<WindowSubsystem, CloseWindowRequest> m_CloseWindowCallback;
    EventCallback<WindowSubsystem, ApplicationUpdatedEvent> m_ApplicationUpdatedCallback;
    EventListener m_EventListener;

    std::vector<GLFWwindow*> m_Windows;
};