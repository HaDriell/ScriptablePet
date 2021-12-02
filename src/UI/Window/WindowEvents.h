#pragma once

#include <memory>

#include "Core/Event/Event.h"
#include "UI/Window/Window.h"
#include "UI/Window/WindowChannel.h"


class WindowEvent : public IEvent
{
public:
    const std::shared_ptr<Window>& GetWindow() const { return m_Window; }
    void SetWindow(const std::shared_ptr<Window>& window) { m_Window = window; }

    void Broadcast() { IEvent::Broadcast(WindowChannel::GetChannel()); }

private:
    std::shared_ptr<Window> m_Window;
};

class OpenWindowRequest : public WindowEvent
{
public:
    const WindowHints& GetWindowHints() const { return m_WindowHints; }
    void SetWindowHints(const WindowHints& windowHints) { m_WindowHints = windowHints; }

private:
    WindowHints m_WindowHints;
};

class CloseWindowRequest : public WindowEvent
{
};

class WindowRenderEvent : public WindowEvent
{
};