#pragma once

#include "ScriptablePet/PetElement.h"

#include <string>

class PetMessage : public PetElement
{
public:
    inline const ClassDescriptor* GetClassDescriptor() const override { return ClassDescriptor::Get<PetMessage>(); }

    void Update() override;
protected:
    void Load(const json& data) override;
    void Save(json& data) const override;

private:
    bool m_Executed{ false };
    std::string m_Message;
};