#include "Core/Reflection/ClassDescriptor.h"


ClassDescriptor::ClassDescriptor(std::string_view className, uint64_t typeID, size_t size)
    : ClassName(className)
    , TypeID(typeID)
    , Size(size)
{
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