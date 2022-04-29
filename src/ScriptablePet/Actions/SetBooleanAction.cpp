#include "ScriptablePet/Actions/SetBooleanAction.h"
#include "ScriptablePet/ScriptablePet.h"

auto g_SetBooleanAction_Decl = ClassDecl<SetBooleanAction>()
    .Super<PetAction>()
    .Constructible()
    .Destructible();

void SetBooleanAction::Execute()
{
    GetOwner()->GetBlackboard().SetBoolean(m_Variable, m_Value);
}

void SetBooleanAction::Load(const json& data)
{
    if (auto it = data.find("variable"); it != data.end() && it->is_string())
    {
        m_Variable = it->get<std::string>();
    }

    if (auto it = data.find("variable"); it != data.end() && it->is_boolean())
    {
        m_Value = it->get<bool>();
    }
}

void SetBooleanAction::Save(json& data) const
{
    data["variable"] = m_Variable;
    data["value"] = m_Value;
}

