#pragma once

#include <memory>

#include "Core/Event/Event.h"
#include "Window/Window.h"
#include "Window/WindowChannel.h"


class WindowEvent : public IEvent
{
public:
    const Window* GetWindow() const { return m_Window; }
    void SetWindow(Window* window) { m_Window = window; }

    void Broadcast() { IEvent::Broadcast(WindowChannel::GetChannel()); }

private:
    Window* m_Window;
};

class WindowRenderEvent : public WindowEvent
{
};

class WindowVisibilityChangedEvent : public WindowEvent
{
};