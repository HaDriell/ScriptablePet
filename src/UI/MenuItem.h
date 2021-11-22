#pragma once

#include <string>
#include <filesystem>

class MenuItem
{
public:
    MenuItem(const std::string& name);
    virtual ~MenuItem();

    void Render();

    const std::string& GetName() const { return m_Name; }

protected:
    virtual void OnClick() {}

private:
    std::string m_Name;
};

class MenuItemScopedRegistration
{
public:
    MenuItemScopedRegistration(const std::filesystem::path& path, MenuItem* item);
    ~MenuItemScopedRegistration();

    MenuItemScopedRegistration(const MenuItemScopedRegistration&) = delete;
    MenuItemScopedRegistration(const MenuItemScopedRegistration&&) = delete;

private:
    std::filesystem::path m_Path;
    MenuItem* m_MenuItem;
};

#define CONCATENATE(x, y) x ## y
#define CONCATENATE2(x, y) CONCATENATE(x, y)
#define RegisterMenuItem(path, type, ...) static MenuItemScopedRegistration CONCATENATE2(g_MenuItem_, __LINE__) (path, new type(__VA_ARGS__));
