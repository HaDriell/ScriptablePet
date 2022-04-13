#pragma once


#include "Core/Reflection/Reflection.h"

class ScriptablePet;

class PetElement : public Object
{
public:
    inline const ClassDescriptor* GetClassDescriptor() const override { return ClassDescriptor::Get<PetElement>(); }

    void SetOwner(ScriptablePet* owner);
    ScriptablePet* GetOwner() const;

    virtual void Update() { }
private:
    ScriptablePet* m_Owner{ nullptr };
};