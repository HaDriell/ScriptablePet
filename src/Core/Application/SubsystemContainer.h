#pragma once

#include <cassert>
#include <vector>

#include "Core/Application/Subsystem.h"

class SubsystemContainer
{
public:
    bool Register(Subsystem* subsystem);
    bool Unregister(Subsystem* subsystem);

    template<class SUBSYSTEM, class... Args>
    bool RegisterManaged(Args&&... args);

    void UnregisterManagedSubsystems();

    const std::vector<Subsystem*>& GetSubsystems() const { return m_Subsystems; }

    template<class SUBSYSTEM>
    SUBSYSTEM* GetSubsystem() const;

private:
    std::vector<Subsystem*> m_Subsystems;
    std::vector<Subsystem*> m_ManagedSubsystems;
};

template<class SUBSYSTEM, class... Args>
bool SubsystemContainer::RegisterManaged(Args&&... args)
{
    assert(GetSubsystem<SUBSYSTEM>() == nullptr);
    Subsystem* subsystem = new SUBSYSTEM(std::forward(args)...);
    if (Register(subsystem))
    {
        m_ManagedSubsystems.push_back(subsystem);
        return true;
    }
    else
    {
        delete subsystem;
        return false;
    }
}

template<class SUBSYSTEM>
SUBSYSTEM* SubsystemContainer::GetSubsystem() const
{
    for (auto* subsystem : m_Subsystems)
    {
        if (SUBSYSTEM* candidate = dynamic_cast<SUBSYSTEM*>(subsystem))
        {
            return candidate;
        }
    }
    return nullptr;
}
