#include "ScriptablePet/Actions/SetStringAction.h"
#include "ScriptablePet/ScriptablePet.h"

auto g_SetStringAction_Decl = ClassDecl<SetStringAction>()
    .Super<PetAction>()
    .Constructible()
    .Destructible();

void SetStringAction::Execute()
{
    GetOwner()->GetBlackboard().SetString(m_Variable, m_Value);
}

void SetStringAction::Load(const json& data)
{
    if (auto it = data.find("variable"); it != data.end() && it->is_string())
    {
        m_Variable = it->get<std::string>();
    }

    if (auto it = data.find("variable"); it != data.end() && it->is_string())
    {
        m_Value = it->get<std::string>();
    }
}

void SetStringAction::Save(json& data) const
{
    data["variable"] = m_Variable;
    data["value"] = m_Value;
}

