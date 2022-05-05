#include "ScriptablePet/Conditions/IsBooleanEqualCondition.h"
#include "ScriptablePet/ScriptablePet.h"

auto g_IsBooleanEqualCondition_Decl = ClassDecl<IsBooleanEqualCondition>()
    .Super<PetCondition>()
    .Constructible()
    .Destructible();

bool IsBooleanEqualCondition::IsVerified() const
{
    return GetOwner()->GetBlackboard().GetBoolean(m_Variable) == m_Value;
}
