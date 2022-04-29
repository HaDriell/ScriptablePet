#pragma once

#include "ScriptablePet/PetRule.h"

#include "UI/Editor.h"

class PetEditor : public Extends<Editor, PetEditor>
{
protected:
    void OnRender() override;
    void RenderPetRule(PetRule* rule);
    void RenderPetAction(PetAction* action);
    void RenderPetCondition(PetCondition* condition);
};