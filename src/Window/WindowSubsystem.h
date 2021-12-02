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

class WindowSubsystem : public Subsystem
{
public:
    using Subsystem::Subsystem;
    
    void Initialize() final;
    void Shutdown() final;

    Window* CreateWindow(const WindowHints& hints);
    void DestroyWindow(Window* window);


private:
    void HandleApplicationUpdatedEvent(const ApplicationUpdatedEvent& event);

private:
    EventCallback<WindowSubsystem, ApplicationUpdatedEvent> m_ApplicationUpdatedCallback;
    EventListener m_EventListener;

    std::vector<Window*> m_Windows;
};