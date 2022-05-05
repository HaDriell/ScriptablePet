#pragma once

#include "ScriptablePet/Conditions/PetCondition.h"

class IsBooleanEqualCondition : public Extends<PetCondition, IsBooleanEqualCondition>
{
public:
    bool IsVerified() const override;

private:
    std::string m_Variable;
    bool m_Value;
};