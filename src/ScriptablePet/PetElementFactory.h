#pragma once

#include <type_traits>

#include "Core/Factory.h"
#include "Core/TypeInfo.h"

#include "ScriptablePet/PetElement.h"

class PetElementFactory : public Factory<std::string, PetElement>
{
public:
    static PetElementFactory& GetInstance();
};

template<class TPetElementClass>
class PetElementType
{
    static_assert(std::is_base_of_v<PetElement, TPetElementClass>);


public:
    PetElementType()
    {
        std::string typeName(GetTypeName<TPetElementClass>());
        PetElementFactory::GetInstance().Register(typeName, &Constructor);
    }

    ~PetElementType()
    {
        std::string typeName(GetTypeName<TPetElementClass>());
        PetElementFactory::GetInstance().Unregister(typeName);
    }

private:
    static PetElement* Constructor() { return new TPetElementClass(); }
};