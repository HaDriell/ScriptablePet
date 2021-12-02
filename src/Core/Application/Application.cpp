#include "Core/Application/Application.h"

#include "Core/Application/ApplicationEvents.h"
#include "Core/Application/ApplicationChannel.h"

Application::~Application()
{
}

void Application::Start()
{
    InitializeSubSystems(m_SubsystemContainer);

    for (Subsystem* subsystem : m_SubsystemContainer.GetSubsystems())
    {
        subsystem->Initialize();
    }

    ApplicationStartedEvent event;
    event.SetApplication(this);
    event.Broadcast();
}

    void Update(float deltaTime);

void Application::Stop()
{
    for (Subsystem* subsystem : m_SubsystemContainer.GetSubsystems())
    {
        subsystem->Shutdown();
    }

    ApplicationStoppedEvent event;
    event.SetApplication(this);
    event.Broadcast();
}