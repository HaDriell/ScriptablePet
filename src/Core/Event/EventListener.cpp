#include "Core/Event/EventListener.h"

#include <cassert>

void EventListener::Call(const IEvent& event) 
{
    assert(!m_Dispatching);
    m_Dispatching = true;
    for (IEventHandler* eventHandler : m_EventHandlers)
    {
        eventHandler->Call(event);
    }
    m_Dispatching = false;
}

bool EventListener::ConnectHandler(IEventHandler* eventHandler)
{
    assert(!m_Dispatching);
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
    assert(!m_Dispatching);
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
    assert(!m_Dispatching);
    return channel.AddListener(this);
}

bool EventListener::LeaveChannel(EventChannel& channel)
{
    assert(!m_Dispatching);
    return channel.RemoveListener(this);
}
