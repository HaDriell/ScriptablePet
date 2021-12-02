#pragma once

#include <vector>

#include "Core/Application/Subsystem.h"

class SubsystemContainer
{
public:
    bool Register(Subsystem* subsystem);
    bool Unregister(Subsystem* subsystem);

    const std::vector<Subsystem*>& GetSubsystems() const { return m_Subsystems; }

    template<class SUBSYSTEM>
    SUBSYSTEM* GetSubsystem() const;

private:
    std::vector<Subsystem*> m_Subsystems;
};


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
