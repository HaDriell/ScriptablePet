#include "Core/Event/Event.h"

#include "Core/Event/EventChannel.h"


void IEvent::Broadcast(EventChannel& channel) const
{
    channel.Broadcast(*this);
}