#pragma once

#include <cstdint>
#include <map>

#include "Core/Reflection/ClassDescriptor.h"

struct ClassManager
{
public:
    static ClassManager* GetInstance();

    bool AddClass(const ClassDescriptor* descriptor);
    bool RemoveClass(const ClassDescriptor* descriptor);

    const ClassDescriptor* GetClassDescriptor(uint32_t typeID) const;

    template<class Predicate>
    void GetClassDescriptorsIf(std::vector<const ClassDescriptor*>& descriptors, Predicate&& predicate)
    {
        for (const auto& [typeID, descriptor] : m_Classes)
        {
            if ((*predicate)(descriptor))
            {
                descriptors.push_back(descriptor);
            }
        }
    }

    const std::map<uint32_t, const ClassDescriptor*>& GetClasses() const { return m_Classes; }
private:
    std::map<uint32_t, const ClassDescriptor*> m_Classes;
};
