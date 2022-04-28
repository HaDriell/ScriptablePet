#pragma once

#include <type_traits>

#include "UI/UISubsystem.h"
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
        UI::Get().AddWidget(m_Widget);
    }

    WidgetMenuItem(const std::string& name)
        : WidgetMenuItem(name, name)
    {}


    ~WidgetMenuItem()
    {
        UI::Get().RemoveWidget(m_Widget);
        //delete m_Widget; // TODO : since RemoveWidget is async now, we cannot delete like this anymore.
    }

protected:
    void OnClick() override
    {
        switch (m_Widget->GetState())
        {
        case Widget::State::Open:
            m_Widget->Close();
            break;

        case Widget::State::Closed:
            m_Widget->Open();
            break;
        default:
            break;
        }
    }

private:
    Widget* m_Widget;
};
