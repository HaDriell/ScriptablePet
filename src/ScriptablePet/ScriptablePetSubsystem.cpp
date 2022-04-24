#include "ScriptablePet/ScriptablePetSubsystem.h"

#include <fstream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;


void ScriptablePetSubsystem::Initialize()
{
    std::ifstream file("pet.json");
    if (file.is_open())
    {
        json data;
        file >> data;
        m_Pet.Load(data);
    }

    //TODO : Clean-up that silly test
    if (m_Pet.GetBlackboard().IsDefined("Answer"))
    {
        int32_t ans = m_Pet.GetBlackboard().GetInteger("Answer");
        m_Pet.GetBlackboard().SetInteger("Answer", ans + 1);
    }
    else
    {
        m_Pet.GetBlackboard().SetInteger("Answer", 42);
    }
}

void ScriptablePetSubsystem::Shutdown()
{
    std::ofstream file("pet.json");
    if (file.is_open())
    {
        json data;
        m_Pet.Save(data);
        file << data;
    }
}