#pragma once

#include <cstdint>
#include <string>
#include <memory>

#include "Core/Reflection/Reflection.h"

class Widget : public Extends<Object, Widget>
{
public:
    enum class State : uint8_t
    {
        Closed,
        Opening,
        Open,
        Closing
    };


    Widget(const std::string& name);
    virtual ~Widget() {}

    void Open();
    void Close();

    void Update();
    void Render();

    const std::string& GetName() const { return m_Name; }
    Widget::State GetState() const { return m_State; }

    bool IsClosed() const { return m_State == Widget::State::Closed; }
    bool IsOpen() const { return m_State == Widget::State::Open; }

protected:
    virtual void OnOpen();
    virtual void OnRender();
    virtual void OnClose();

private:
    std::string m_Name;
    Widget::State m_State;
};