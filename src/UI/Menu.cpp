#include "UI/Menu.h"

#include <imgui.h>

Menu::Menu(const std::string& name)
    : m_Name(name)
{
}

bool Menu::AddItem(MenuItem* item)
{
    auto it = m_Items.find(item->GetName());
    if (it == m_Items.end())
    {
        m_Items.emplace(item->GetName(), item);
        return true;
    }
    return false;
}

bool Menu::RemoveItem(MenuItem* item)
{
    auto it = m_Items.find(item->GetName());
    if (it != m_Items.end())
    {
        m_Items.erase(it);
        return true;
    }
    return false;
}

Menu* Menu::GetSubMenu(const std::string& name, bool createIfNecessary)
{
    auto it = m_SubMenus.find(name);

    if (it != m_SubMenus.end())
    {
        return &it->second;
    }
    else if (createIfNecessary)
    {
        m_SubMenus.emplace(name, name);
        return &m_SubMenus.find(name)->second;
    }

    return nullptr;
}

void Menu::RenderItems()
{
    for (auto[name, menu] : m_SubMenus)
    {
        if (ImGui::BeginMenu(name.c_str()))
        {
            menu.RenderItems();
            ImGui::EndMenu();
        }
    }

    for (auto[_, item] : m_Items)
    {
        item->Render();
    }
}
