#pragma once

#include "Core/Application/Application.h"

namespace Engine
{
    void SetApplication(Application* application);
    Application* GetApplication();

    void Start();
    void Stop();
}