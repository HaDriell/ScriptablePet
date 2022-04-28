#pragma once

#include "UI/Editor.h"

class PetEditor : public Editor
{
public:
    const ClassDescriptor* GetClassDescriptor() const override { return ClassDescriptor::Get<PetEditor>(); }

protected:
    void OnRender() override;
};