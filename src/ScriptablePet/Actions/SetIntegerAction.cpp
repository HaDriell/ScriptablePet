#include "ScriptablePet/Actions/SetIntegerAction.h"
#include "ScriptablePet/ScriptablePet.h"

auto g_SetIntegerAction_Decl = ClassDecl<SetIntegerAction>()
    .Super<PetAction>()
    .Constructible()
    .Destructible();

void SetIntegerAction::Execute()
{
    GetOwner()->GetBlackboard().SetInteger(m_Variable, m_Value);
}

void SetIntegerAction::Load(const json& data)
{
    if (auto it = data.find("variable"); it != data.end() && it->is_string())
    {
        m_Variable = it->get<std::string>();
    }

    if (auto it = data.find("variable"); it != data.end() && it->is_number_integer())
    {
        m_Value = it->get<int32_t>();
    }
}

void SetIntegerAction::Save(json& data) const
{
    data["variable"] = m_Variable;
    data["value"] = m_Value;
}

