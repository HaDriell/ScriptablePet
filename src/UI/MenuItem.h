#pragma once

#include <string>
#include <filesystem>

class MenuItem
{
public:
    MenuItem(const std::string& name);

    void Render();

    const std::string& GetName() const { return m_Name; }

protected:
    virtual void OnClick() {}

private:
    std::string m_Name;
};