#include "Window/WindowChannel.h"

EventChannel& WindowChannel::GetChannel()
{
    static EventChannel channel;
    return channel;
}