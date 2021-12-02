#pragma once

#include "Core/Event/EventChannel.h"


class ApplicationChannel
{
public:
    static EventChannel& GetChannel();
};