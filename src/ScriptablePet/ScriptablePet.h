#pragma once

#include <istream>
#include <ostream>
#include <vector>

#include "ScriptablePet/Blackboard.h"
#include "ScriptablePet/PetElement.h"

class ScriptablePet
{
public:
    Blackboard& GetBlackboard() { return m_Blackboard; }
    const Blackboard& GetBlackboard() const { return m_Blackboard; }

    void AddElement(PetElement* element);
    void RemoveElement(PetElement* element);

    void Update();
    void Load(const json& container);
    void Save(json& container) const;

private:
    Blackboard m_Blackboard;
    std::vector<PetElement*> m_Elements;
};