#include "Core/Application/ApplicationChannel.h"


EventChannel& ApplicationChannel::GetChannel()
{
    static EventChannel channel;
    return channel;
}