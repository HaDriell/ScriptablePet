#include "Core/Engine.h"

#include <cassert>

namespace Engine
{
    Application* s_Application = nullptr;

    
    void SetApplication(Application* application)
    {
        s_Application = application;
    }

    Application* GetApplication()
    {
        assert(s_Application != nullptr);
        return s_Application;
    }
    
    void Start()
    {
        assert(s_Application != nullptr);
        s_Application->Start();
    }

    
    void Stop()
    {
        assert(s_Application != nullptr);
        s_Application->Stop();
        s_Application = nullptr;
    }
}