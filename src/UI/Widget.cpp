#include "UI/Widget.h"

#include <string>
#include <imgui.h>
#include "UI/UIEvents.h"

auto g_Widget_Decl = ClassDecl<Widget>()
    .Super<Object>()
    .Destructible();

Widget::Widget(const std::string& name)
    : m_Name(name)
    , m_State(Widget::State::Closed)
{
}

void Widget::Open()
{
    if (m_State == Widget::State::Closed)
    {
        m_State = Widget::State::Opening;
    }
}

void Widget::Render()
{
    if (ImGui::Begin(m_Name.c_str()))
    {
        OnRender();
    }
    ImGui::End();
}

void Widget::Close()
{
    if (m_State == Widget::State::Open)
    {
        m_State = Widget::State::Closing;
    }
}

void Widget::Update()
{
    switch (m_State)
    {
    case Widget::State::Opening:
    {
        OnOpen();

        WidgetOpenedEvent event;
        event.SetWidget(this);
        event.Broadcast();

        m_State = Widget::State::Open;
        break;
    }
    case Widget::State::Open:
    {
        Render();
        break;
    }
    case Widget::State::Closing:
    {
        WidgetClosedEvent event;
        event.SetWidget(this);
        event.Broadcast();

        OnClose();

        m_State = Widget::State::Closed;
        break;
    }    
    default:
        break;
    }
}

void Widget::OnOpen()
{

}

void Widget::OnRender()
{

}

void Widget::OnClose()
{
    
}