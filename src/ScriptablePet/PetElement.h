#pragma once

#include <nlohmann/json.hpp>
using json = nlohmann::json;

class ScriptablePet;

class PetElement
{
public:
    ~PetElement() { }

    void SetOwner(ScriptablePet* owner);
    ScriptablePet* GetOwner() const;

    virtual void Update() { }
    virtual void Load(const json& container) { }
    virtual void Save(json& container) { }

private:
    ScriptablePet* m_Owner{ nullptr };
};