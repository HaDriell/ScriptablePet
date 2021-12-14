#include "Core/Event/Event.h"

#include "Core/Event/EventChannel.h"


void IEvent::Broadcast(const EventChannel& channel) const
{
    channel.Broadcast(*this);
}