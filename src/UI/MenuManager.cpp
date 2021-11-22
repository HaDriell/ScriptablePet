#include "UI/MenuManager.h"

#include <imgui.h>



void MenuManager::RenderMainMenuBar()
{
    if (ImGui::BeginMainMenuBar())
    {
        m_MainMenuBar.RenderItems();
        ImGui::EndMainMenuBar();
    }
}

bool MenuManager::Register(const std::filesystem::path& path, MenuItem* item)
{
    Menu* menu = &m_MainMenuBar;

    for (auto it = path.begin(); it != path.end(); ++it)
    {
        menu = menu->GetSubMenu(it->u8string(), true);        
    }

    return menu->AddItem(item);
}

bool MenuManager::Unregister(const std::filesystem::path& path, MenuItem* item)
{
    Menu* menu = &m_MainMenuBar;

    for (auto it = path.begin(); it != path.end(); ++it)
    {
        menu = menu->GetSubMenu(it->u8string(), false);
        if (menu == nullptr)
        {
            return false;
        }
    }

    return menu->RemoveItem(item);
}

MenuManager& MenuManager::GetInstance()
{
    static MenuManager s_Instance;
    return s_Instance;
}