#include "ScriptablePet/ScriptablePet.h"

#include <algorithm>

const std::string JSON_SECTION_BLACKBOARD   = "blackboard";
const std::string JSON_SECTION_ELEMENTS     = "elements";

ScriptablePet::~ScriptablePet()
{
    for (auto element : m_Elements)
    {
        delete element;
    }
    m_Elements.clear();
} 

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

    if (auto it = container.find(JSON_SECTION_ELEMENTS); it != container.end())
    {
        if (it->is_array())
        {
            for (const json& data : *it)
            {
                if (Object* object = Object::Deserialize(data))
                {
                    if (PetElement* petElement = object->Cast<PetElement>())
                    {
                        AddElement(petElement);
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
    json& blackboard = container[JSON_SECTION_BLACKBOARD];
    m_Blackboard.Save(blackboard);
    
    //Save Elements (Yes, they all share the same container, dirty isolation from Blackboard I know)
    json& containers = container[JSON_SECTION_ELEMENTS];
    for (auto element : m_Elements)
    {
        json& container = containers.emplace_back();
        Object::Serialize(element, container);
    }
}