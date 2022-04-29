#pragma once

#include "ScriptablePet/Actions/PetAction.h"
#include "ScriptablePet/Blackboard.h"


class UndefineAction : public Extends<PetAction, UndefineAction>
{
public:
    void Execute() override;

    void Load(const json& data) override;
    void Save(json& data) const override;

    const std::string& GetVariable() const { return m_Variable; }
    std::string& GetVariable() { return m_Variable; }
    void SetVariable(const std::string& value) { m_Variable = value; }

private:
    std::string m_Variable;
};