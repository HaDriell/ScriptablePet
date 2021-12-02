#include "Core/Application/Application.h"

#include "Core/Engine.h"

#include "Window/WindowSubsystem.h"

class MainSubsystem : public Subsystem
{
    using Subsystem::Subsystem;

public:
    void Initialize() final
    {
        m_WindowSubsystem = GetApplication()->GetSubsystem<WindowSubsystem>();

        WindowHints hints;
        m_Window = m_WindowSubsystem->CreateWindow(hints);
        m_Window->Show();
    }

    void Shutdown() final
    {
        m_WindowSubsystem->DestroyWindow(m_Window);
    }

private:
    WindowSubsystem* m_WindowSubsystem{ nullptr };
    Window* m_Window;
};

class ExampleApplication : public Application
{
protected:
    void InitializeSubSystems(SubsystemContainer& container) override
    {
        container.RegisterManaged<WindowSubsystem>();
        container.RegisterManaged<MainSubsystem>();
    }
};

int main()
{
    ExampleApplication application;
    Engine::Run(&application);
}