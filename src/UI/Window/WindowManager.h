#pragma once

#include <vector>
#include <memory>

#include "Core/Event/EventHandler.h"
#include "Core/Event/EventListener.h"

#include "UI/Window/Window.h"
#include "UI/Window/WindowEvents.h"

class WindowManager
{
public:
    void Initialize();
    void Shutdown();
    void Update();


private:
    void HandleOpenWindowRequest(const OpenWindowRequest& event);
    void HandleCloseWindowRequest(const CloseWindowRequest& event);

private:
    EventCallback<WindowManager, OpenWindowRequest> m_OpenWindowCallback;
    EventCallback<WindowManager, CloseWindowRequest> m_CloseWindowCallback;
    EventListener m_EventListener;

    std::vector<std::shared_ptr<Window>> m_ManagedWindows;

public:
    static WindowManager& GetInstance();
};