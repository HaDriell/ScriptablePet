#pragma once

#include <cstdint>
#include <string>
#include <memory>

class Widget
{
public:
    Widget(const std::string& name);
    virtual ~Widget() {}

    bool Register();
    bool Unregister();

    void Open();
    void Render();
    void Close();


    const std::string& GetName() const { return m_Name; }
    bool IsRegistered() const { return m_Registered; }
    bool IsOpen() const { return m_Open; }

protected:
    virtual void OnOpen() {}
    virtual void OnRender() {}
    virtual void OnClose() {}

private:
    std::string m_Name;
    bool m_Registered;
    bool m_Open;
};