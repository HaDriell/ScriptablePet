#include "ScriptablePet/Actions/UndefineAction.h"
#include "ScriptablePet/ScriptablePet.h"

auto g_UndefineAction_Decl = ClassDecl<UndefineAction>()
    .Super<PetAction>()
    .Constructible()
    .Destructible();

void UndefineAction::Execute()
{
    GetOwner()->GetBlackboard().Undefine(m_Variable);
}

void UndefineAction::Load(const json& data)
{
    if (auto it = data.find("variable"); it != data.end() && it->is_string())
    {
        m_Variable = it->get<std::string>();
    }
}

void UndefineAction::Save(json& data) const
{
    data["variable"] = m_Variable;
}