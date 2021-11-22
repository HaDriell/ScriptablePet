#pragma once

#include <string>
#include <map>

#include "UI/MenuItem.h"

class Menu
{
public:
    Menu(const std::string& name = "");
    ~Menu();
    
    bool AddItem(MenuItem* item);
    bool RemoveItem(MenuItem* item);

    bool IsEmpty() const { return m_SubMenus.empty() && m_Items.empty(); }

    Menu* GetSubMenu(const std::string& name, bool createIfNecessary);
    
    void RenderItems();

private:
    std::string m_Name;
    std::map<std::string, Menu> m_SubMenus;
    std::map<std::string, MenuItem*> m_Items;
};