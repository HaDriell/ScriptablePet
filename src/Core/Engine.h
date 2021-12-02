#pragma once

#include "Core/Application/Application.h"

namespace Engine
{
    void Run(Application* application);
    void Exit(int exitCode = 0);
    float GetDeltaTime();
    Application* GetApplication();
}