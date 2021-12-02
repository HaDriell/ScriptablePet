#include "Core/Engine.h"

#include <cassert>
#include <chrono>
#include <thread>

namespace Engine
{
    Application* s_Application = nullptr;
    int s_ExitCode = 0;
    bool s_Running = false;
    float s_DeltaTime = 0.0f;

    constexpr int FrameRate = 60;

    int Run(Application* application)
    {
        assert(s_Application == nullptr);
        assert(application != nullptr);
        s_Application = application;

        s_Application->Start();

        auto previousTimePoint = std::chrono::steady_clock::now();

        s_Running = true;
        while (s_Running)
        {
            //Update the deltaTime
            auto currentTimePoint = std::chrono::steady_clock::now();
            s_DeltaTime = (currentTimePoint - previousTimePoint).count() / 1e9f;
            previousTimePoint = currentTimePoint;

            //Update the application
            s_Application->Update();

            std::this_thread::sleep_until(currentTimePoint + std::chrono::duration<std::chrono::steady_clock::rep, std::ratio<1, FrameRate>>(1));
        }

        s_Application->Stop();
        s_Application = nullptr;
        
        return s_ExitCode;
    }

    void Exit(int exitCode)
    {
        s_ExitCode = exitCode;
    }

    float GetDeltaTime()
    {
        return s_DeltaTime;
    }

    Application* GetApplication()
    {
        return s_Application;
    }
}