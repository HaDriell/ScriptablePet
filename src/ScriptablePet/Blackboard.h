#pragma once

#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include <istream>
#include <ostream>

#include <map>
#include <string>
#include <variant>

#include "Core/Reflection/Reflection.h"

using TValue = std::variant<bool, int32_t, float, std::string>;
const TValue InvalidValue;

class Blackboard : public Extends<Object, Blackboard>
{
public:
    bool IsDefined(const std::string& variable) const;
    bool Undefine(const std::string& variable);

    void SetBoolean(const std::string& variable, bool value) { m_Data[variable] = value; }
    void SetInteger(const std::string& variable, int32_t value) { m_Data[variable] = value; }
    void SetFloat(const std::string& variable, float value) { m_Data[variable] = value; }
    void SetString(const std::string& variable, const std::string& value) { m_Data[variable] = value; }

    bool GetBoolean(const std::string& variable) const;
    int32_t GetInteger(const std::string& variable) const;
    float GetFloat(const std::string& variable) const;
    std::string GetString(const std::string& variable) const;

    void Load(const json& data) override;
    void Save(json& data) const override;

    void Clear();

private:
    std::map<std::string, TValue> m_Data;
};