#include "Core/Event/EventChannel.h"

#include <cassert>
#include <algorithm>

#include "Core/Event/EventListener.h"

void EventChannel::Broadcast(const IEvent& event) const
{
    for (const EventListener* eventListener : m_EventListeners)
    {
        eventListener->Call(event);
    }
}

bool EventChannel::AddListener(const EventListener* eventListener)
{
    auto it = std::find(m_EventListeners.begin(), m_EventListeners.end(), eventListener);
    if (it == m_EventListeners.end())
    {
        m_EventListeners.push_back(eventListener);
        return true;
    }
    return false;
}

bool EventChannel::RemoveListener(const EventListener* eventListener)
{
    auto it = std::find(m_EventListeners.begin(), m_EventListeners.end(), eventListener);
    if (it != m_EventListeners.end())
    {
        m_EventListeners.erase(it);
        return true;
    }
    return false;
}