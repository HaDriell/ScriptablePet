#pragma once

#include <filesystem>
#include <map>
#include <string>
#include <vector>

#include "Core/Application/Subsystem.h"
#include "Core/Engine.h"
#include "Core/Event/EventHandler.h"
#include "Core/Event/EventListener.h"
#include "Core/Proxy.h"

#include "UI/Editor.h"
#include "UI/Menu.h"
#include "UI/Widget.h"

#include "Window/WindowChannel.h"
#include "Window/WindowEvents.h"

class UISubsystem : public Subsystem
{
public:
    void Initialize() override;
    void Shutdown() override;

    void RenderMainMenuBar();
    void RenderWidgets();

    bool AddMenuItem(const std::filesystem::path& path, MenuItem* item);
    bool RemoveMenuItem(const std::filesystem::path& path, MenuItem* item);

    void AddWidget(Widget* widget);
    void RemoveWidget(Widget* widget);

private:
    void HandleWindowRenderEvent(const WindowRenderEvent& event);

private:
    Menu m_MainMenuBar;
    std::vector<EditorMenuItem*> m_ManagedEditors;

    std::map<std::string, Widget*> m_Widgets;
    std::vector<Widget*> m_WidgetsToAdd;
    std::vector<Widget*> m_WidgetsToRemove;

    EventCallback<UISubsystem, WindowRenderEvent> m_WindowRenderCallback;
    EventListener m_EventListener;
};