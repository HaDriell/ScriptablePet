#pragma once


class EventChannel;

class IEvent
{
public:
    virtual ~IEvent() = default;

    void Broadcast(EventChannel& channel) const;
};