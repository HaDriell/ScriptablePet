#include "ScriptablePet/Blackboard.h"

#include <nlohmann/json.hpp>

using json = nlohmann::json;

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

void Blackboard::Load(const json& container)
{
    Clear();
    for (auto it = container.begin(); it != container.end(); ++it)
    {
        if (it.value().is_boolean()) SetBoolean(it.key(), it.value());
        else if (it.value().is_number_integer()) SetInteger(it.key(), it.value());
        else if (it.value().is_number_float()) SetFloat(it.key(), it.value());
        else if (it.value().is_string()) SetString(it.key(), it.value());
    }
}

void Blackboard::Save(json& container) const
{
    struct TValueSerializer
    {
        TValueSerializer(json& container, const std::string& key)
            : m_Container(container)
            , m_Key(key)
        {}

        json& m_Container;
        const std::string& m_Key;

        void operator()(const bool& value) const { m_Container[m_Key] = value; }
        void operator()(const int32_t& value) const { m_Container[m_Key] = value; }
        void operator()(const float& value) const { m_Container[m_Key] = value; }
        void operator()(const std::string& value) const { m_Container[m_Key] = value; }        
    };

    for (const auto& [key, value] : m_Data)
    {
        std::visit(TValueSerializer(container, key), value);
    }
}

void Blackboard::Clear()
{
    m_Data.clear();
}