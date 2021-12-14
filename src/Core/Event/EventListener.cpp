#include "Core/Event/EventListener.h"

#include <cassert>

void EventListener::Call(const IEvent& event) const
{
    for (IEventHandler* eventHandler : m_EventHandlers)
    {
        eventHandler->Call(event);
    }
}

bool EventListener::ConnectHandler(IEventHandler* eventHandler)
{
    auto it = std::find(m_EventHandlers.begin(), m_EventHandlers.end(), eventHandler);
    if (it == m_EventHandlers.end())
    {
        m_EventHandlers.push_back(eventHandler);
        return true;
    }
    return false;
}

bool EventListener::DisconnectHandler(IEventHandler* eventHandler)
{
    auto it = std::find(m_EventHandlers.begin(), m_EventHandlers.end(), eventHandler);
    if (it != m_EventHandlers.end())
    {
        m_EventHandlers.erase(it);
        return true;
    }
    return false;
}


bool EventListener::JoinChannel(EventChannel& channel)
{
    return channel.AddListener(this);
}

bool EventListener::LeaveChannel(EventChannel& channel)
{
    return channel.RemoveListener(this);
}
