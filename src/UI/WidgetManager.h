#pragma once

#include <map>
#include <string>
#include <memory>

#include "UI/Widget.h"

class WidgetManager
{
public:

    bool Register(Widget* widget);
    bool Unregister(Widget* widget);
    Widget* GetWidget(const std::string& name) const;
    void Render();

private:
    std::map<std::string, Widget*> m_Widgets;

// Singleton Declaration
public:
    static WidgetManager& GetInstance() { return s_Instance; }
private:
    static WidgetManager s_Instance;
};