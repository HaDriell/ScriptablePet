#include "ScriptablePet/PetRule.h"


auto g_PetRule_Decl = ClassDecl<PetRule>()
    .Super<PetElement>()
    .Constructible()
    .Destructible()
    .Declare();

PetRule::~PetRule()
{
    for (PetAction* action : m_Actions)
    {
        delete action;
    }

    for (PetCondition* condition : m_Conditions)
    {
        delete condition;
    }
}


void PetRule::Load(const json& data)
{
    //TODO : load actions & conditions
}

void PetRule::Save(json& data) const
{
    json conditions = json::array();
    //TODO : save actions & conditions
}

void PetRule::Evaluate()
{
    for (PetCondition* condition : m_Conditions)
    {
        if (!condition->IsVerified())
        {
            return; // Quick exit on all
        }
    }

    for (PetAction* action : m_Actions)
    {
        action->Execute();
    }
}