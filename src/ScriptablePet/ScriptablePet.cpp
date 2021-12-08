#include "ScriptablePet/ScriptablePet.h"

#include <algorithm>

const std::string JSON_SECTION_BLACKBOARD   = "blackboard";
const std::string JSON_SECTION_DATA         = "data";


void ScriptablePet::AddElement(PetElement* element)
{
    auto it = std::find(m_Elements.begin(), m_Elements.end(), element);
    if (it == m_Elements.end())
    {
        element->SetOwner(this);
        m_Elements.push_back(element);
    }
}

void ScriptablePet::RemoveElement(PetElement* element)
{
    auto it = std::find(m_Elements.begin(), m_Elements.end(), element);
    if (it != m_Elements.end())
    {
        m_Elements.erase(it);
        element->SetOwner(nullptr);
        delete element;
    }
}

void ScriptablePet::Update()
{
    for (auto element : m_Elements)
    {
        element->Update();
    }
}

void ScriptablePet::Load(const json& container)
{
    if (auto it = container.find(JSON_SECTION_BLACKBOARD); it != container.end())
    {
        m_Blackboard.Load(it.value());
    }

    if (auto it = container.find(JSON_SECTION_DATA); it != container.end())
    {
        for (auto element : m_Elements)
        {
            element->Load(it.value());
        }
    }
}

void ScriptablePet::Save(json& container) const
{
    //Save Blackboard
    json& blackboard = container[JSON_SECTION_BLACKBOARD];
    m_Blackboard.Save(blackboard);

    //Save Elements (Yes, they all share the same container, dirty isolation from Blackboard I know)
    json& elements = container[JSON_SECTION_DATA];
    for (auto element : m_Elements)
    {
        element->Save(elements);
    }
}