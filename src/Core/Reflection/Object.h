#pragma once

#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include "Core/Reflection/ClassDescriptor.h"


class Object
{
public:
    virtual ~Object() = default;
    inline virtual const ClassDescriptor* GetClassDescriptor() const { return ClassDescriptor::Get<Object>(); }

    virtual void Load(const json& data) {}
    virtual void Save(json& data) const {}

    template<class ToType>
    ToType* Cast()
    {
        return GetClassDescriptor()->IsTypeOf<ToType>() ? static_cast<ToType*>(this) : nullptr;
    }

    template<class ToType>
    const ToType* Cast() const
    {
        return IsTypeOf<ToType>(GetClassDescriptor()) ? static_cast<const ToType*>(this) : nullptr;
    }

    static Object* Deserialize(const json& container);

    static void Deserialize(const json& container, Object* instance);
    static void Serialize(const Object* object, json& container);
};