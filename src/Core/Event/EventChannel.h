#pragma once

#include <vector>

#include "Core/Event/Event.h"

class EventListener;

class EventChannel
{
public:
    void Broadcast(const IEvent& event);
    bool AddListener(EventListener* eventListener);
    bool RemoveListener(EventListener* eventListener);

private:
    std::vector<EventListener*> m_EventListeners;
    bool m_Distaptching = false;
};