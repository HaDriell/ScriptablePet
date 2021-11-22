#pragma once

#include "UI/Menu.h"

#include <filesystem>
#include <string>
#include <map>

class MenuManager
{
public:
    void RenderMainMenuBar();

    bool Register(const std::filesystem::path& path, MenuItem* item);
    bool Unregister(const std::filesystem::path& path, MenuItem* item);

private:
    Menu m_MainMenuBar;

// Singleton Declaration
public:
    static MenuManager& GetInstance();
};