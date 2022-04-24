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
    if (auto it = container.find("blackboard"); it != container.end())
    {
        m_Blackboard.Load(it.value());
    }

    if (auto it = container.find("rules"); it != container.end())
    {
        if (it->is_array())
        {
            for (const json& data : *it)
            {
                if (Object* object = Object::Deserialize(data))
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
    json blackboard = json::object();
    m_Blackboard.Save(blackboard);
    
    //Save Elements (Yes, they all share the same container, dirty isolation from Blackboard I know)
    json rules = json::array();
    for (auto rule : m_Rules)
    {
        json& container = rules.emplace_back();
        Object::Serialize(rule, container);
    }

    container["blackboard"] = blackboard;
    container["rules"] = rules;
}