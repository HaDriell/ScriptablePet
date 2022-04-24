#pragma once

#include "ScriptablePet/PetElement.h"

class PetAction : public PetElement
{
public:
    inline const ClassDescriptor* GetClassDescriptor() const override { return ClassDescriptor::Get<PetAction>(); }

    virtual void Execute() = 0;
};