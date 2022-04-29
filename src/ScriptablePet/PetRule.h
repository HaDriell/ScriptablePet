#pragma once

#include <string>

#include "Core/Event/EventListener.h"

#include "ScriptablePet/PetElement.h"
#include "ScriptablePet/Actions/PetAction.h"
#include "ScriptablePet/Conditions/PetCondition.h"

class PetRule : public Extends<PetElement, PetRule>
{
public:
    ~PetRule();

    void Load(const json& data) override;
    void Save(json& data) const override;
    void Evaluate();

    void AddCondition(PetCondition* condition);
    void RemoveCondition(PetCondition* condition);
    void AddAction(PetAction* action);
    void RemoveAction(PetAction* action);

    const std::string& GetName() const { return m_Name; }
    std::string& GetName() { return m_Name; }
    void SetName(const std::string& name) { m_Name = name; }

    const std::vector<PetCondition*>& GetConditions() const { return m_Conditions; }
    const std::vector<PetAction*>& GetActions() const { return m_Actions; }
    

private:
    std::string m_Name;
    std::vector<PetCondition*> m_Conditions;
    std::vector<PetAction*> m_Actions;
};