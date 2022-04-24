#pragma once

#include <istream>
#include <ostream>
#include <vector>

#include "Core/Event/EventChannel.h"
#include "ScriptablePet/Blackboard.h"
#include "ScriptablePet/PetRule.h"

class ScriptablePet
{
public:
    ~ScriptablePet();
    
    Blackboard& GetBlackboard() { return m_Blackboard; }
    const Blackboard& GetBlackboard() const { return m_Blackboard; }

    void AddRule(PetRule* rule);
    void RemoveRule(PetRule* rule);

    void Update();
    void Load(const json& container);
    void Save(json& container) const;

    EventChannel& GetChannel() { return m_EventChannel; }

private:
    Blackboard m_Blackboard;
    std::vector<PetRule*> m_Rules;
    EventChannel m_EventChannel;
};