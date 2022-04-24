#pragma once

#include "Core/Event/EventListener.h"

#include "ScriptablePet/PetElement.h"
#include "ScriptablePet/Actions/PetAction.h"
#include "ScriptablePet/Conditions/PetCondition.h"

class PetRule : public PetElement
{
public:
    ~PetRule();

    void Load(const json& data) override;
    void Save(json& data) const override;
    void Evaluate();

private:
    std::vector<PetCondition*> m_Conditions;
    std::vector<PetAction*> m_Actions;
};