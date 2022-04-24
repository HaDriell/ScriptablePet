#include "UI/WidgetManager.h"

#include <algorithm>

#include "UI/UIChannel.h"


void WidgetManager::Initialize()
{
    m_WidgetOpenedCallback.Init(this, &WidgetManager::HandleWidgetOpenedEvent);
    m_WidgetClosedCallback.Init(this, &WidgetManager::HandleWidgetClosedEvent);

    m_EventListener.ConnectHandler(&m_WidgetOpenedCallback);
    m_EventListener.ConnectHandler(&m_WidgetClosedCallback);
    m_EventListener.JoinChannel(UIChannel::GetChannel());
}

void WidgetManager::Shutdown()
{
    m_EventListener.LeaveChannel(UIChannel::GetChannel());
    m_WidgetOpenedCallback.Reset();
    m_WidgetClosedCallback.Reset();
}

bool WidgetManager::Register(Widget* widget)
{
    auto it = m_Widgets.find(widget->GetName());
    if (it == m_Widgets.end())
    {
        m_Widgets.emplace(widget->GetName(), widget);
        return true;
    }
    return false;
}

bool WidgetManager::Unregister(Widget* widget)
{
    auto it = m_Widgets.find(widget->GetName());
    if (it != m_Widgets.end())
    {
        m_Widgets.erase(it);
        return true;
    }
    return false;
}

Widget* WidgetManager::GetWidget(const std::string& name) const
{
    auto it = m_Widgets.find(name);
    return it != m_Widgets.end() ? it->second : nullptr;
}

void WidgetManager::Render()
{
    for (const auto& [_, widget] : m_Widgets)
    {
        widget->Render();
    }
}

void WidgetManager::HandleWidgetOpenedEvent(const WidgetOpenedEvent& event)
{

}

void WidgetManager::HandleWidgetClosedEvent(const WidgetClosedEvent& event)
{

}

WidgetManager& WidgetManager::GetInstance()
{
    static WidgetManager instance;
    return instance;
}
