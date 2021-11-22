#include "UI/MenuItem.h"

#include <imgui.h>

#include "UI/MenuManager.h"


MenuItem::MenuItem(const std::string& name)
    : m_Name(name)
{
    //TODO self register to Manager
}

MenuItem::~MenuItem()
{
    //TODO self unregister to Manager
}

void MenuItem::Render()
{
    if (ImGui::MenuItem(m_Name.c_str()))
    {
        OnClick();
    }
}

MenuItemScopedRegistration::MenuItemScopedRegistration(const std::filesystem::path& path, MenuItem* item)
    : m_Path(path)
    , m_MenuItem(item)
{
    MenuManager::GetInstance().Register(m_Path, m_MenuItem);
}

MenuItemScopedRegistration::~MenuItemScopedRegistration()
{
    MenuManager::GetInstance().Unregister(m_Path, m_MenuItem);
}