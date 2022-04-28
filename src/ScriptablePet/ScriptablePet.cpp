#include "ScriptablePet/ScriptablePet.h"

#include <algorithm>

ScriptablePet::~ScriptablePet()
{
    for (auto element : m_Rules)
    {
        delete element;
    }
    m_Rules.clear();
} 

void ScriptablePet::AddRule(PetRule* rule)
{
    auto it = std::find(m_Rules.begin(), m_Rules.end(), rule);
    if (it == m_Rules.end())
    {
        rule->SetOwner(this);
        m_Rules.push_back(rule);
    }
}

void ScriptablePet::RemoveRule(PetRule* rule)
{
    auto it = std::find(m_Rules.begin(), m_Rules.end(), rule);
    if (it != m_Rules.end())
    {
        m_Rules.erase(it);
        rule->SetOwner(nullptr);
        delete rule;
    }
}

void ScriptablePet::Update()
{
    for (auto rule : m_Rules)
    {
        rule->Evaluate();
    }
}

void ScriptablePet::Load(const json& container)
{
    if (auto it = container.find("blackboard"); it != container.end() && it->is_object())
    {
        Object::Deserialize(it.value(), &m_Blackboard);
    }

    if (auto it = container.find("rules"); it != container.end())
    {
        if (it->is_array())
        {
            for (const json& serializedRule : *it)
            {
                if (Object* object = Object::Deserialize(serializedRule))
                {
                    if (PetRule* rule = object->Cast<PetRule>())
                    {
                        AddRule(rule);
                    }
                    else
                    {
                        delete object; // Error : WTF did we deserialize ?
                    }
                }
            }
        }
    }
}

void ScriptablePet::Save(json& container) const
{
    //Save Blackboard
    json blackboard;
    Object::Serialize(&m_Blackboard, blackboard);
    container["blackboard"] = blackboard;

    //Save PetRules
    json rules = json::array();
    for (auto rule : m_Rules)
    {
        json& container = rules.emplace_back();
        Object::Serialize(rule, container);
    }
    container["rules"] = rules;
}