#pragma once

#include "ScriptablePet/Actions/PetAction.h"
#include "ScriptablePet/Blackboard.h"


class SetIntegerAction : public Extends<PetAction, SetIntegerAction>
{
public:
    void Execute() override;

    void Load(const json& data) override;
    void Save(json& data) const override;
    
    const std::string& GetVariable() const { return m_Variable; }
    std::string& GetVariable() { return m_Variable; }
    void SetVariable(const std::string& value) { m_Variable = value; }

    int32_t GetValue() const { return m_Value; }
    void SetValue(int32_t value) { m_Value = value; }
private:
    std::string m_Variable;
    int32_t m_Value{ 0 };
};