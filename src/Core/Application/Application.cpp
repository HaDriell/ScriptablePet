#include "Core/Application/Application.h"

#include "Core/Application/ApplicationEvents.h"
#include "Core/Application/ApplicationChannel.h"

#include "Core/Engine.h"

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

void Application::Update()
{
    ApplicationUpdatedEvent event;
    event.SetApplication(this);
    event.Broadcast();
}

void Application::Stop()
{
    ApplicationStoppedEvent event;
    event.SetApplication(this);
    event.Broadcast();

    for (Subsystem* subsystem : m_SubsystemContainer.GetSubsystems())
    {
        subsystem->Shutdown();
    }
    
    m_SubsystemContainer.UnregisterManagedSubsystems();
}