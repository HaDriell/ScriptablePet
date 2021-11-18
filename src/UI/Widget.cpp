#include "UI/Widget.h"

#include <string>
#include <imgui.h>
#include "UI/WidgetManager.h"



Widget::Widget(const std::string& name)
    : m_Name(name)
    , m_Registered(false)
    , m_Open(false)
{
}

bool Widget::Register()
{
    if (!m_Registered)
    {
        m_Registered = WidgetManager::GetInstance().Register(this);
        return m_Registered;
    }
    return false;
}

bool Widget::Unregister()
{
    if (m_Registered)
    {
        m_Registered = WidgetManager::GetInstance().Unregister(this);
        return m_Registered;
    }
    return false;
}

void Widget::Open()
{
    if (m_Registered)
    {
        if (!m_Open)
        {
            m_Open = true;
            OnOpen();
        }
    }
}

void Widget::Render()
{
    if (m_Registered)
    {
        if (m_Open)
        {
            if (ImGui::Begin(m_Name.c_str(), &m_Open))
            {
                OnRender();
            }
            ImGui::End();
        }
    }
}

void Widget::Close()
{
    if (m_Registered)
    {
        if (m_Open)
        {
            m_Open = false;
            OnClose();
        }
    }
}