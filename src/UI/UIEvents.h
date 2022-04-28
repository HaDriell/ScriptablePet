#pragma once

#include <memory>

#include "UI/Widget.h"
#include "UI/UIChannel.h"
#include "Core/Event/Event.h"

class WidgetEvent : public IEvent
{
public:
    Widget* GetWidget() const { return m_Widget; }
    void SetWidget(Widget* widget) { m_Widget = widget; }

    inline void Broadcast() const { IEvent::Broadcast(UIChannel::GetChannel()); }
private:
    Widget* m_Widget;
};

class WidgetOpenedEvent : public WidgetEvent
{
};

class WidgetClosedEvent : public WidgetEvent
{
};