#include "Core/Application/Application.h"

#include "Core/Engine.h"

#include "ScriptablePet/ScriptablePetSubsystem.h"
#include "Window/WindowSubsystem.h"
#include "Window/WindowChannel.h"

#include <iostream>

class MainSubsystem : public Subsystem
{
    using Subsystem::Subsystem;

public:
    void Initialize() final
    {
        m_WindowVisibilityChangedCallback.Init(this, &MainSubsystem::HandleWindowVisibilityChangedEvent);
        m_EventListener.ConnectHandler(&m_WindowVisibilityChangedCallback);
        m_EventListener.JoinChannel(WindowChannel::GetChannel());

        m_WindowSubsystem = GetApplication()->GetSubsystem<WindowSubsystem>();

        WindowHints hints;
        m_Window = m_WindowSubsystem->CreateWindow(hints);
        m_Window->SetVisible(true);
    }

    void Shutdown() final
    {
        m_WindowSubsystem->DestroyWindow(m_Window);

        m_EventListener.LeaveChannel(WindowChannel::GetChannel());
        m_EventListener.DisconnectHandler(&m_WindowVisibilityChangedCallback);
        m_WindowVisibilityChangedCallback.Reset();
    }

private:
    void HandleWindowVisibilityChangedEvent(const WindowVisibilityChangedEvent& event)
    {
        if (!m_Window->IsVisible())
        {
            Engine::Exit();
        }
    }


private:
    EventListener m_EventListener;
    EventCallback<MainSubsystem, WindowVisibilityChangedEvent> m_WindowVisibilityChangedCallback;

    WindowSubsystem* m_WindowSubsystem{ nullptr };
    Window* m_Window;
};

class MainApplication : public Application
{
protected:
    void InitializeSubSystems(SubsystemContainer& container) override
    {
        container.RegisterManaged<WindowSubsystem>();
        container.RegisterManaged<ScriptablePetSubsystem>();
        container.RegisterManaged<MainSubsystem>();
    }
};

template<class T>
void ShowTypeInfo()
{
    std::cout << "Type (0x" << std::hex << TypeInfo<T>::Hash << std::dec << ") ";
    std::cout << "Name : " << TypeInfo<T>::Name;
    std::cout << "\n";
}

int main()
{
    ShowTypeInfo<uint32_t>();
    ShowTypeInfo<Application>();
    ShowTypeInfo<void(Application::*)()>();
    ShowTypeInfo<void(*)()>();
    ShowTypeInfo<void()>();
    
    MainApplication application;
    return Engine::Run(&application);
}