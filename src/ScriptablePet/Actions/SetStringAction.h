#pragma once

#include "ScriptablePet/Actions/PetAction.h"
#include "ScriptablePet/Blackboard.h"


class SetStringAction : public Extends<PetAction, SetStringAction>
{
public:
    void Execute() override;

    void Load(const json& data) override;
    void Save(json& data) const override;
    
    const std::string& GetVariable() const { return m_Variable; }
    std::string& GetVariable() { return m_Variable; }
    void SetVariable(const std::string& value) { m_Variable = value; }

    const std::string& GetValue() const { return m_Value; }
    std::string& GetValue() { return m_Value; }
    void SetValue(const std::string& value) { m_Value = value; }

private:
    std::string m_Variable;
    std::string m_Value;
};