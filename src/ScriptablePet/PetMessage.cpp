#include "ScriptablePet/PetMessage.h"

#include <iostream>

#include "Core/Reflection/ClassDecl.h"

static auto g_PetMessage_Class = ClassDecl<PetMessage>()
    .Super<PetElement>()
    .Constructible()
    .Destructible()
    .Declare();

void PetMessage::Update()
{
    if (!m_Executed)
    {
        std::cout << "Pet says " << m_Message << "\n";
        m_Executed = true;
    }
}

void PetMessage::Load(const json& data)
{
    m_Message = data["message"].get<std::string>();
}

void PetMessage::Save(json& data) const
{
    data["message"] = m_Message;
}