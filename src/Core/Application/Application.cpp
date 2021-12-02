#include "Core/Application/Application.h"

#include "Core/Application/ApplicationEvents.h"
#include "Core/Application/ApplicationChannel.h"

#include <iostream>
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
    std::cout << "DeltaTime " << Engine::GetDeltaTime() << std::endl;
    ApplicationUpdatedEvent event;
    event.SetApplication(this);
    event.Broadcast();
}

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