#pragma once

#include <vector>

#include "Core/Event/Event.h"

class EventListener;

class EventChannel
{
public:
    void Broadcast(const IEvent& event) const;
    bool AddListener(const EventListener* eventListener);
    bool RemoveListener(const EventListener* eventListener);

private:
    std::vector<const EventListener*> m_EventListeners;
};