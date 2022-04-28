#include "ScriptablePet/PetRule.h"


auto g_PetRule_Decl = ClassDecl<PetRule>()
    .Super<PetElement>()
    .Constructible()
    .Destructible();

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
    if (auto it = data.find("name"); it != data.end() && it->is_string())
    {
        m_Name = it->get<std::string>();
    }

    if (auto it = data.find("conditions"); it != data.end() && it->is_array())
    {
        for (const json& serializedCondition : *it)
        {
            if (Object* object = Object::Deserialize(serializedCondition))
            {
                if (PetCondition* condition = object->Cast<PetCondition>())
                {
                    AddCondition(condition);
                }
                else
                {
                    delete object; // Error : WTF did we deserialize ?
                }
            }
        }
    }

    if (auto it = data.find("actions"); it != data.end() && it->is_array())
    {
        for (const json& serializedAction : *it)
        {
            if (Object* object = Object::Deserialize(serializedAction))
            {
                if (PetAction* action = object->Cast<PetAction>())
                {
                    AddAction(action);
                }
                else
                {
                    delete object; // Error : WTF did we deserialize ?
                }
            }
        }

    }
}

void PetRule::Save(json& data) const
{
    json conditions = json::array();
    for (const PetCondition* condition : m_Conditions)
    {
        json& container = conditions.emplace_back();
        Object::Serialize(condition, container);
    }

    json actions = json::array();
    for (const PetAction* action : m_Actions)
    {
        json& container = actions.emplace_back();
        Object::Serialize(action, container);
    }
 
    data["name"] = GetName();
    data["conditions"] = conditions;
    data["actions"] = actions;
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

void PetRule::AddCondition(PetCondition* condition)
{
    auto it = std::find(m_Conditions.begin(), m_Conditions.end(), condition);
    if (it == m_Conditions.end())
    {
        m_Conditions.emplace_back(condition);
    }
}

void PetRule::RemoveCondition(PetCondition* condition)
{
    auto it = std::find(m_Conditions.begin(), m_Conditions.end(), condition);
    if (it != m_Conditions.end())
    {
        m_Conditions.erase(it);
    }
}

void PetRule::AddAction(PetAction* action)
{
    auto it = std::find(m_Actions.begin(), m_Actions.end(), action);
    if (it == m_Actions.end())
    {
        m_Actions.emplace_back(action);
    }
}

void PetRule::RemoveAction(PetAction* action)
{
    auto it = std::find(m_Actions.begin(), m_Actions.end(), action);
    if (it != m_Actions.end())
    {
        m_Actions.erase(it);
    }
}
