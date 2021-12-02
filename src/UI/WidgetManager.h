#pragma once

#include <map>
#include <string>
#include <memory>

#include "Core/Event/EventHandler.h"
#include "Core/Event/EventListener.h"

#include "UI/UIEvents.h"
#include "UI/Widget.h"

class WidgetManager
{
public:
    void Initialize();
    void Shutdown();

    bool Register(Widget* widget);
    bool Unregister(Widget* widget);
    Widget* GetWidget(const std::string& name) const;
    void Render();

private:
    void HandleWidgetOpenedEvent(const WidgetOpenedEvent& event);
    void HandleWidgetClosedEvent(const WidgetClosedEvent& event);

private:
    EventCallback<WidgetManager, WidgetOpenedEvent> m_WidgetOpenedCallback;
    EventCallback<WidgetManager, WidgetClosedEvent> m_WidgetClosedCallback;
    EventListener m_EventListener;

    std::map<std::string, Widget*> m_Widgets;

// Singleton Declaration
public:
    static WidgetManager& GetInstance();
};