#pragma once

#include "UI/Editor.h"

class PetEditor : public Extends<Editor, PetEditor>
{
protected:
    void OnRender() override;
};