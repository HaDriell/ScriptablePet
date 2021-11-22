#pragma once

#include <type_traits>

#include "UI/MenuItem.h"
#include "UI/Widget.h"

template<class WIDGET>
class WidgetMenuItem : public MenuItem
{
    static_assert(std::is_base_of_v<Widget, WIDGET>);
public:
    WidgetMenuItem(const std::string& menuItemName, const std::string& widgetName)
        : MenuItem(menuItemName)
    {
        m_Widget = new WIDGET(widgetName);
        m_Widget->Register();
    }

    WidgetMenuItem(const std::string& name)
        : WidgetMenuItem(name, name)
    {}


    ~WidgetMenuItem()
    {
        m_Widget->Unregister();
        delete m_Widget;
    }

protected:
    void OnClick() override
    {
        if (m_Widget->IsOpen())
        {
            m_Widget->Close();
        }
        else
        {
            m_Widget->Open();
        }
    }

private:
    Widget* m_Widget;
};
