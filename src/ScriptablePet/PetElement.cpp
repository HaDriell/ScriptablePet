#include "ScriptablePet/PetElement.h"


static auto g_PetElement_Decl = ClassDecl<PetElement>()
    .Super<Object>()
    .Constructible()
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