#pragma once


#include "ScriptablePet/PetElement.h"

class PetCondition : public Extends<PetElement, PetCondition>
{
public:
    virtual bool IsVerified() const = 0;
};