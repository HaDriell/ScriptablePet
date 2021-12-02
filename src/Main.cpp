#include "Core/Application/Application.h"

#include "Core/Engine.h"

#include "Window/WindowSubsystem.h"

class ExampleApplication : public Application
{
protected:
    void InitializeSubSystems(SubsystemContainer& container) override
    {
        container.RegisterManaged<WindowSubsystem>();
    }
};

int main()
{
    ExampleApplication application;
    Engine::Run(&application);
}