#include "Core/Application/SubsystemContainer.h"

#include <algorithm>


bool SubsystemContainer::Register(Subsystem* subsystem)
{
    auto it = std::find(m_Subsystems.begin(), m_Subsystems.end(), subsystem);
    if (it == m_Subsystems.end())
    {
        m_Subsystems.push_back(subsystem);
        return true;
    }
    return false;
}

bool SubsystemContainer::Unregister(Subsystem* subsystem)
{
    auto it = std::find(m_Subsystems.begin(), m_Subsystems.end(), subsystem);
    if (it != m_Subsystems.end())
    {
        m_Subsystems.erase(it);
        return true;
    }
    return false;
}

void SubsystemContainer::UnregisterManagedSubsystems()
{
    for (Subsystem* subsystem : m_ManagedSubsystems)
    {
        if (Unregister(subsystem))
        {
            delete subsystem;
        }
    }
    m_Subsystems.clear();
}
