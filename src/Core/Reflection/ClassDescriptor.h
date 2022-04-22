#pragma once

#include "Core/TypeInfo.h"

#include <cstdint>
#include <functional>
#include <string_view>
#include <vector>

class Object;

struct ClassDescriptor
{
    using Constructor = std::function<Object*()>;
    using Destructor = std::function<void(Object*)>;

    const ClassDescriptor*  SuperClass{ nullptr };
    std::string_view        ClassName;
    uint64_t                TypeID;
    size_t                  Size;

    Constructor             ConstructorFunction;
    Destructor              DestructorFunction;

private:
    ClassDescriptor(std::string_view className, uint64_t typeID, size_t size);
public:
    template<class Class>
    [[nodiscard]] static ClassDescriptor* Get()
    {
        static ClassDescriptor classDescriptor(TypeInfo<Class>::Name, TypeInfo<Class>::Hash, TypeInfo<Class>::Size);
        return &classDescriptor;
    }
};

inline bool IsSameAs(const ClassDescriptor* self, const ClassDescriptor* other)
{
    return self == other;
}

template<class Other>
bool IsSameAs(const ClassDescriptor* self)
{
    return IsSameAs(self, ClassDescriptor::Get<Other>());
}

template<class Self, class Other>
bool IsSameAs()
{
    return IsSameAs(ClassDescriptor::Get<Self>(), ClassDescriptor::Get<Other>());   
}

inline bool IsTypeOf(const ClassDescriptor* self, const ClassDescriptor* other)
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

template<class Other>
bool IsTypeOf(const ClassDescriptor* self)
{
    return IsTypeOf(self, ClassDescriptor::Get<Other>());
}

template<class Self, class Other>
bool IsTypeOf()
{
    return IsTypeOf(ClassDescriptor::Get<Self>(), ClassDescriptor::Get<Other>());   
}