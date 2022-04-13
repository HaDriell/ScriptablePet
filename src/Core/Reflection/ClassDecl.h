#pragma once

#include "Core/Reflection/Object.h"
#include "Core/Reflection/ClassManager.h"

template<class Class>
class ClassDecl
{
    static_assert(std::is_base_of_v<Object, Class>);
public:
    [[nodiscard]] ClassDecl& Declare()
    {
        ClassManager::GetInstance()->AddClass(ClassDescriptor::Get<Class>());
        return *this;
    }

    template<class SuperClass>
    [[nodiscard]] ClassDecl& Super()
    {
        ClassDescriptor::Get<Class>()->SuperClass = ClassDescriptor::Get<SuperClass>();
        return *this;
    }

    [[nodiscard]] ClassDecl& Constructible()
    {
        ClassDescriptor::Get<Class>()->ConstructorFunction = []()
        {
            return new Class();
        };
        return *this;
    }
    
    [[nodiscard]] ClassDecl& Destructible()
    {
        ClassDescriptor::Get<Class>()->DestructorFunction = [](Object* instance)
        {
            delete static_cast<Class*>(instance);
        };
        return *this;
    }

};