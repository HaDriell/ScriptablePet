#pragma once

#include <memory>

#include "UI/Widget.h"
#include "Core/Event/Event.h"

class WidgetEvent : public IEvent
{
public:
    const std::shared_ptr<Widget>& GetWidget() const { return m_Widget; }
    void SetWidget(const std::shared_ptr<Widget> widget) { m_Widget = widget; }

private:
    std::shared_ptr<Widget> m_Widget;
};

class WidgetOpenedEvent : public WidgetEvent
{
};

class WidgetClosedEvent : public WidgetEvent
{
};