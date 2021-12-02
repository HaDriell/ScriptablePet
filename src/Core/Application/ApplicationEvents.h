#pragma once

#include "Core/Event/Event.h"
#include "Core/Application/Application.h"
#include "Core/Application/ApplicationChannel.h"


class ApplicationEvent : public IEvent
{
public:
    void SetApplication(Application* application) { m_Application = application; }
    Application* GetApplication() const { return m_Application; }


    void Broadcast() { IEvent::Broadcast(ApplicationChannel::GetChannel()); }

private:
    Application* m_Application;
};

class ApplicationStartedEvent : public ApplicationEvent
{
};

class ApplicationStoppedEvent : public ApplicationEvent
{
};