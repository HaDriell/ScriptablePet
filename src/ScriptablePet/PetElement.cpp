#include "ScriptablePet/PetElement.h"
#include "ScriptablePet/ScriptablePet.h"

#include "Core/Reflection/Object.h"

static auto g_PetElement_Decl = ClassDecl<PetElement>()
    .Super<Object>()
    .Destructible()
    .Declare();

void PetElement::SetOwner(ScriptablePet* owner)
{
    m_Owner = owner;
}

ScriptablePet* PetElement::GetOwner() const
{
    return m_Owner;
}