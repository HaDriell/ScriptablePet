#include "UI/UISubsystem.h"

#include <imgui.h>

#include "Core/Reflection/ClassDescriptor.h"

#include "UI/Editor.h"
#include "UI/WidgetMenuItem.h"

void UISubsystem::Initialize()
{
    m_WindowRenderCallback.Init(this, &UISubsystem::HandleWindowRenderEvent);
    m_EventListener.ConnectHandler(&m_WindowRenderCallback);
    m_EventListener.JoinChannel(WindowChannel::GetChannel());

    std::vector<const ClassDescriptor*> editorClasses;
    ClassDescriptor::GetDerivedClasses<Editor>(editorClasses);
    for (const ClassDescriptor* classDescriptor : editorClasses)
    {
        if (classDescriptor->IsConstructible())
        {
            Editor* editor = (Editor*) classDescriptor->NewInstance();
            EditorMenuItem* menuItem = new EditorMenuItem(editor);
            menuItem->AddToMenuBar();
            m_ManagedEditors.push_back(menuItem);
        }
    }
    
}

void UISubsystem::Shutdown()
{
    for (EditorMenuItem* menuItem : m_ManagedEditors)
    {
        menuItem->RemoveFromMenuBar();
        delete menuItem;
    }
    m_ManagedEditors.clear();

    m_EventListener.LeaveChannel(WindowChannel::GetChannel());
    m_EventListener.DisconnectHandler(&m_WindowRenderCallback);

}

void UISubsystem::RenderMainMenuBar()
{
    if (ImGui::BeginMainMenuBar())
    {
        m_MainMenuBar.RenderItems();
        ImGui::EndMainMenuBar();
    }
}

void UISubsystem::RenderWidgets()
{
    //Consume pending adds
    for (Widget* widget : m_WidgetsToAdd)
    {
        auto it = m_Widgets.find(widget->GetName());
        if (it == m_Widgets.end())
        {
            m_Widgets.emplace(widget->GetName(), widget);
        }
    }
    m_WidgetsToAdd.clear();

    //Update widgets
    for (auto[_, widget] : m_Widgets)
    {
        widget->Update();
    }

    //Consume pending removes
    for (Widget* widget : m_WidgetsToRemove)
    {
        auto it = m_Widgets.find(widget->GetName());
        if (it == m_Widgets.end())
        {
            m_Widgets.emplace(widget->GetName(), widget);
        }
    }
    m_WidgetsToRemove.clear();
}

bool UISubsystem::AddMenuItem(const std::filesystem::path& path, MenuItem* item)
{
    Menu* menu = &m_MainMenuBar;

    for (auto it = path.begin(); it != path.end(); ++it)
    {
        menu = menu->GetSubMenu(it->u8string(), true);        
    }

    return menu->AddItem(item);
}

bool UISubsystem::RemoveMenuItem(const std::filesystem::path& path, MenuItem* item)
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

void UISubsystem::AddWidget(Widget* widget)
{
    m_WidgetsToAdd.emplace_back(widget);
}

void UISubsystem::RemoveWidget(Widget* widget)
{
    m_WidgetsToRemove.emplace_back(widget);
}

void UISubsystem::HandleWindowRenderEvent(const WindowRenderEvent& event)
{
    RenderMainMenuBar();
    RenderWidgets();
}
