#pragma once


class EventChannel;

class IEvent
{
public:
    virtual ~IEvent() = default;

    void Broadcast(const EventChannel& channel) const;
};