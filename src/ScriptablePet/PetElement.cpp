#include "ScriptablePet/PetElement.h"

void PetElement::SetOwner(ScriptablePet* owner)
{
    m_Owner = owner;
}

ScriptablePet* PetElement::GetOwner() const
{
    return m_Owner;
}
