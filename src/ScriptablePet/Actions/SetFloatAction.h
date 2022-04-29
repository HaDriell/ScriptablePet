#pragma once

#include "ScriptablePet/Actions/PetAction.h"
#include "ScriptablePet/Blackboard.h"


class SetFloatAction : public Extends<PetAction, SetFloatAction>
{
public:
    using Super = PetAction;
    inline const ClassDescriptor* GetClassDescriptor() const override { return ClassDescriptor::Get<SetFloatAction>(); }

    void Execute() override;

    void Load(const json& data) override;
    void Save(json& data) const override;
    
    const std::string& GetVariable() const { return m_Variable; }
    std::string& GetVariable() { return m_Variable; }
    void SetVariable(const std::string& value) { m_Variable = value; }

    float GetValue() const { return m_Value; }
    void SetValue(float value) { m_Value = value; }
private:
    std::string m_Variable;
    float m_Value{ 0 };
};