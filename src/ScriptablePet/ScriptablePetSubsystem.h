#pragma once

#include "Core/Application/Subsystem.h"
#include "ScriptablePet/ScriptablePet.h"

class ScriptablePetSubsystem : public Subsystem
{
public:
    void Initialize() override;
    void Shutdown() override;

    ScriptablePet& GetPet() { return m_Pet; }

private:
    ScriptablePet m_Pet;
};