#pragma once

#include "ScriptablePet/ScriptablePet.h"

#include "UI/Editor.h"

class PetEditor : public Extends<Editor, PetEditor>
{
public:

    void RenderPetRule(PetRule* rule);
    void RenderPetAction(PetAction* action);
    void RenderPetCondition(PetCondition* condition);

protected:
    void OnRender() override;
};