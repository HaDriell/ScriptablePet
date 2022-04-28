#include "ScriptablePet/Blackboard.h"

#include <nlohmann/json.hpp>
using json = nlohmann::json;

auto g_Blackboard_Decl = ClassDecl<Blackboard>()
    .Super<Object>()
    .Constructible()
    .Destructible();

bool Blackboard::IsDefined(const std::string& variable) const
{
    return m_Data.find(variable) != m_Data.end();
}

bool Blackboard::Undefine(const std::string& variable)
{
    auto it = m_Data.find(variable);
    if (it != m_Data.end())
    {
        m_Data.erase(it);
        return true;
    }
    return false;
}

bool Blackboard::GetBoolean(const std::string& variable) const
{
    auto it = m_Data.find(variable);
    
    if (it != m_Data.end())
    {
        return std::get<bool>(it->second);
    }

    return false;
}

int32_t Blackboard::GetInteger(const std::string& variable) const
{
    auto it = m_Data.find(variable);
    
    if (it != m_Data.end())
    {
        return std::get<int32_t>(it->second);
    }
    
    return 0;
}

float Blackboard::GetFloat(const std::string& variable) const
{
    auto it = m_Data.find(variable);
    
    if (it != m_Data.end())
    {
        return std::get<float>(it->second);
    }
    
    return 0;
}

std::string Blackboard::GetString(const std::string& variable) const
{
    auto it = m_Data.find(variable);
    
    if (it != m_Data.end())
    {
        return std::get<std::string>(it->second);
    }
    
    return "";
}

void Blackboard::Load(const json& data)
{
    Clear();
    for (auto it = data.begin(); it != data.end(); ++it)
    {
        if (it.value().is_boolean())                SetBoolean(it.key(), it.value());
        else if (it.value().is_number_integer())    SetInteger(it.key(), it.value());
        else if (it.value().is_number_float())      SetFloat(it.key(), it.value());
        else if (it.value().is_string())            SetString(it.key(), it.value());
    }
}

void Blackboard::Save(json& data) const
{
    for (const auto& [key, value] : m_Data)
    {
        if (std::holds_alternative<bool>(value))        data[key] = std::get<bool>(value);
        if (std::holds_alternative<int32_t>(value))     data[key] = std::get<int32_t>(value);
        if (std::holds_alternative<float>(value))       data[key] = std::get<float>(value);
        if (std::holds_alternative<std::string>(value)) data[key] = std::get<std::string>(value);
    }
}

void Blackboard::Clear()
{
    m_Data.clear();
}