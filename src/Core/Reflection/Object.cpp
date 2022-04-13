#include "Core/Reflection/Object.h"

#include "Core/Reflection/ClassDecl.h"
#include "Core/Reflection/ClassManager.h"

const auto g_Object_Decl = ClassDecl<Object>()
    .Destructible()
    .Declare();

Object* Object::Deserialize(const json& container)
{
    auto typeID = container.find("typeID"); 
    if (typeID == container.end() || !typeID->is_number_unsigned())
    {
        //Error : missing or invalid typeID
        return nullptr;
    }
    
    const ClassDescriptor* classDescriptor = ClassManager::GetInstance()->GetClassDescriptor(typeID->get<uint32_t>());
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

void Object::Serialize(const Object* object, json& container)
{
    container["typeID"] = object->GetClassDescriptor()->TypeID;
    object->Save(container["data"]);
}