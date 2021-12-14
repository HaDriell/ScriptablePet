#pragma once

#include <algorithm>
#include <vector>

#include "Core/Event/Event.h"
#include "Core/Event/EventHandler.h"
#include "Core/Event/EventChannel.h"

class EventListener
{
public:
    void Call(const IEvent& event) const;

    bool ConnectHandler(IEventHandler* eventHandler);
    bool DisconnectHandler(IEventHandler* eventHandler);

    bool JoinChannel(EventChannel& channel);
    bool LeaveChannel(EventChannel& channel);

private:
    std::vector<IEventHandler*> m_EventHandlers;
};