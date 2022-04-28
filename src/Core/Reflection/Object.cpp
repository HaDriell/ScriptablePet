#include "Core/Reflection/Object.h"

#include "Core/Reflection/ClassDecl.h"

const auto g_Object_Decl = ClassDecl<Object>()
    .Destructible();

Object* Object::Deserialize(const json& container)
{
    auto className = container.find("className"); 
    if (className == container.end() || !className->is_string())
    {
        //Error : missing or invalid className
        return nullptr;
    }
    
    const ClassDescriptor* classDescriptor = ClassDescriptor::GetClassByName(className->get<std::string>());
    if (classDescriptor == nullptr)
    {
        //Error : unknown ClassDescriptor
        return nullptr;
    }

    if (!classDescriptor->ConstructorFunction)
    {
        //Error : this Class has no registered constructor
        return nullptr;
    }

    Object* instance = classDescriptor->ConstructorFunction();

    //data can be optional if the object doesn't need it
    auto data = container.find("data");
    if (data != container.end())
    {
        instance->Load(*data);
    }

    return instance;
}

void Object::Deserialize(const json& container, Object* instance)
{
    auto className = container.find("className");
    if (className == container.end() || !className->is_string())
    {
        //Error : missing or invalid className
        return;
    }
    
    const ClassDescriptor* classDescriptor = ClassDescriptor::GetClassByName(className->get<std::string>());
    if (classDescriptor == nullptr)
    {
        //Error : unknown ClassDescriptor
        return;
    }

    if (!IsTypeOf(instance->GetClassDescriptor(), classDescriptor))
    {
        //Error : Serialized type is not compatible with provided instance
        return;
    }

    auto data = container.find("data");
    if (data != container.end())
    {
        instance->Load(*data);
    }
}

void Object::Serialize(const Object* object, json& container)
{
    json data;
    object->Save(data);

    container["className"] = object->GetClassDescriptor()->ClassName;
    container["data"] = data;
}