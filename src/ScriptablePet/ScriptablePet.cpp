#include "ScriptablePet/ScriptablePet.h"

#include <algorithm>


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
    for (auto it = container.begin(); it != container.end(); ++it)
    {
        if (it.key() == "blackboard")
        {
            m_Blackboard.Load(it.value());
        }
        else if (it.key() == "elements")
        {
            for (auto element : m_Elements)
            {
                element->Load(it.value());
            }
        }
    }
}

void ScriptablePet::Save(json& container) const
{
    json& blackboard = container["blackboard"];
    json& elements = container["elements"];

    m_Blackboard.Save(blackboard);

    for (auto element : m_Elements)
    {
        element->Save(elements);
    }
}