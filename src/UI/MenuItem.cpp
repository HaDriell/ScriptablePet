#include "UI/MenuItem.h"

#include <imgui.h>

MenuItem::MenuItem(const std::string& name)
    : m_Name(name)
{
}

void MenuItem::Render()
{
    if (ImGui::MenuItem(m_Name.c_str()))
    {
        OnClick();
    }
}