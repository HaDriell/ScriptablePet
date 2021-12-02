#include "Core/Application/Application.h"

#include "Core/Engine.h"

class ExampleApplication : public Application
{
protected:
    void InitializeSubSystems(SubsystemContainer& registry) override
    {
        //Nothing here yet
    }
};


int main()
{
    ExampleApplication application;
    Engine::Run(&application);
}