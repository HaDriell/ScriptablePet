#include "ScriptablePet/ScriptablePetSubsystem.h"

#include <fstream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;


void ScriptablePetSubsystem::Initialize()
{
    std::ifstream file("pet.json");
    json data;
    file >> data;
    m_Pet.Load(data);
}

void ScriptablePetSubsystem::Shutdown()
{
    std::ofstream file("pet.json");
    json data;
    m_Pet.Save(data);
    file << data;
}