#pragma once

#include "ScriptablePet/Actions/PetAction.h"
#include "ScriptablePet/Blackboard.h"


class SetBooleanAction : public Extends<PetAction, SetBooleanAction>
{
public:
    void Execute() override;

    void Load(const json& data) override;
    void Save(json& data) const override;
    
    const std::string& GetVariable() const { return m_Variable; }
    std::string& GetVariable() { return m_Variable; }
    void SetVariable(const std::string& value) { m_Variable = value; }

    bool GetValue() const { return m_Value; }
    void SetValue(bool value) { m_Value = value; }
private:
    std::string m_Variable;
    bool m_Value{ false };
};