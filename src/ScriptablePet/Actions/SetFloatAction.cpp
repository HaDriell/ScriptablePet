#include "ScriptablePet/Actions/SetFloatAction.h"
#include "ScriptablePet/ScriptablePet.h"

auto g_SetFloatAction_Decl = ClassDecl<SetFloatAction>()
    .Super<PetAction>()
    .Constructible()
    .Destructible();

void SetFloatAction::Execute()
{
    GetOwner()->GetBlackboard().SetFloat(m_Variable, m_Value);
}

void SetFloatAction::Load(const json& data)
{
    if (auto it = data.find("variable"); it != data.end() && it->is_string())
    {
        m_Variable = it->get<std::string>();
    }

    if (auto it = data.find("value"); it != data.end() && it->is_number())
    {
        m_Value = it->get<float>();
    }
}

void SetFloatAction::Save(json& data) const
{
    data["variable"] = m_Variable;
    data["value"] = m_Value;
}

