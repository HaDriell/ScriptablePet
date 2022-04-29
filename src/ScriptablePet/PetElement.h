#pragma once


#include "Core/Reflection/Reflection.h"

class ScriptablePet;

class PetElement : public Extends<Object, PetElement>
{
public:
    void SetOwner(ScriptablePet* owner);
    ScriptablePet* GetOwner() const;
    
private:
    ScriptablePet* m_Owner{ nullptr };
};