#include "Core/Reflection/ClassManager.h"

bool ClassManager::AddClass(const ClassDescriptor* descriptor)
{
    auto it = m_Classes.find(descriptor->TypeID);

    if (it == m_Classes.end())
    {
        m_Classes.emplace(descriptor->TypeID, descriptor);
        return true;
    }

    return false;
}

bool ClassManager::RemoveClass(const ClassDescriptor* descriptor)
{
    auto it = m_Classes.find(descriptor->TypeID);

    if (it != m_Classes.end() && it->second == descriptor)
    {
        m_Classes.erase(it);
        return true;
    }

    return false;
}

const ClassDescriptor* ClassManager::GetClassDescriptor(uint32_t typeID) const
{
    auto it = m_Classes.find(typeID);
    return it != m_Classes.end() ? it->second : nullptr;
}

ClassManager* ClassManager::GetInstance()
{
    static ClassManager instance;
    return &instance;
}