#include "UI/UIChannel.h"

EventChannel& UIChannel::GetChannel()
{
    static EventChannel channel;
    return channel;
}