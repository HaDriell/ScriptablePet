#include "Core/Reflection/ClassDescriptor.h"


ClassDescriptor::ClassDescriptor(std::string_view className, uint64_t typeID, size_t size)
    : ClassName(className)
    , TypeID(typeID)
    , Size(size)
{
}