#include "UI/WidgetManager.h"

#include <algorithm>

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
    for (auto [_, widget] : m_Widgets)
    {
        widget->Render();
    }
}

WidgetManager& WidgetManager::GetInstance()
{
    static WidgetManager s_Instance;
    return s_Instance;
}
