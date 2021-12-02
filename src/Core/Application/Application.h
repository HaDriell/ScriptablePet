#pragma once

#include <vector>

#include "Core/Application/SubsystemContainer.h"


class Application
{
public:
    virtual ~Application();

    void Start();
    void Update(float deltaTime);
    void Stop();

    const std::vector<Subsystem*>& GetSubSystems() const { return m_SubsystemContainer.GetSubsystems(); }

    template<class SUBSYSTEM>
    SUBSYSTEM* GetSubsystem() const
    {
        return m_SubsystemContainer.GetSubSystem<SUBSYSTEM>();
    }

protected:
    virtual void InitializeSubSystems(SubsystemContainer& registry) = 0;

private:
    SubsystemContainer m_SubsystemContainer;
};