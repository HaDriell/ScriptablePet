#include "Core/Reflection/ClassDescriptor.h"

#include <algorithm>

static std::vector<const ClassDescriptor*> g_ClassDescriptors;

const ClassDescriptor* ClassDescriptor::GetClassByName(std::string_view className)
{
    auto it = std::find_if(g_ClassDescriptors.begin(), g_ClassDescriptors.end(), [className](const ClassDescriptor* classDescriptor)
    {
        return classDescriptor->ClassName == className;
    });

    return it != g_ClassDescriptors.end() ? *it : nullptr;
}

void ClassDescriptor::GetDerivedClasses(const ClassDescriptor* baseClass, std::vector<const ClassDescriptor*>& derivedClasses)
{
    for (const ClassDescriptor* classDescriptor : g_ClassDescriptors)
    {
        if (::IsTypeOf(classDescriptor, baseClass))
        {
            derivedClasses.emplace_back(classDescriptor);
        }
    }
}

ClassDescriptor::ClassDescriptor(std::string_view className, uint64_t typeID, size_t size)
    : ClassName(className)
    , TypeID(typeID)
    , Size(size)
{
    auto it = std::find(g_ClassDescriptors.begin(), g_ClassDescriptors.end(), this);
    if (it == g_ClassDescriptors.end())
    {
        g_ClassDescriptors.emplace_back(this);
    }
}

ClassDescriptor::~ClassDescriptor()
{
    auto it = std::find(g_ClassDescriptors.begin(), g_ClassDescriptors.end(), this);
    if (it != g_ClassDescriptors.end())
    {
        g_ClassDescriptors.erase(it);
    }
}

bool IsSameAs(const ClassDescriptor* self, const ClassDescriptor* other)
{
    return self == other;
}

bool IsTypeOf(const ClassDescriptor* self, const ClassDescriptor* other)
{
    const ClassDescriptor* current = self;

    while (current != nullptr)
    {
        if (IsSameAs(current, other))
        {
            return true;
        }
        current = current->SuperClass;
    }

    return false;
}