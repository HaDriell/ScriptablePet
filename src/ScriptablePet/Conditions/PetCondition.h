#pragma once


#include "ScriptablePet/PetElement.h"

class PetCondition : public PetElement
{

public:
    inline const ClassDescriptor* GetClassDescriptor() const override { return ClassDescriptor::Get<PetCondition>(); }
    virtual bool IsVerified() const = 0;
};