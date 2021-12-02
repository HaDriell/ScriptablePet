#include "Core/Event/EventChannel.h"

#include <cassert>
#include <algorithm>

#include "Core/Event/EventListener.h"

void EventChannel::Broadcast(const IEvent& event)
{
    m_Distaptching = true;
    for (EventListener* eventListener : m_EventListeners)
    {
        eventListener->Call(event);
    }
    m_Distaptching = false;
}

bool EventChannel::AddListener(EventListener* eventListener)
{
    assert(!m_Distaptching);
    auto it = std::find(m_EventListeners.begin(), m_EventListeners.end(), eventListener);
    if (it == m_EventListeners.end())
    {
        m_EventListeners.push_back(eventListener);
        return true;
    }
    return false;
}

bool EventChannel::RemoveListener(EventListener* eventListener)
{
    assert(!m_Distaptching);
    auto it = std::find(m_EventListeners.begin(), m_EventListeners.end(), eventListener);
    if (it != m_EventListeners.end())
    {
        m_EventListeners.erase(it);
        return true;
    }
    return false;
}