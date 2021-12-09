#include "Window/WindowSubsystem.h"

#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Core/Application/ApplicationChannel.h"

void WindowSubsystem::Initialize()
{
    glfwInit();

    m_ApplicationUpdatedCallback.Init(this, &WindowSubsystem::HandleApplicationUpdatedEvent);

    m_EventListener.ConnectHandler(&m_ApplicationUpdatedCallback);

    m_EventListener.JoinChannel(ApplicationChannel::GetChannel());
}

void WindowSubsystem::Shutdown()
{
    m_EventListener.LeaveChannel(ApplicationChannel::GetChannel());

    m_EventListener.DisconnectHandler(&m_ApplicationUpdatedCallback);

    m_ApplicationUpdatedCallback.Reset();

    glfwTerminate();
}

Window* WindowSubsystem::CreateWindow(const WindowHints& hints)
{
    Window* window = new Window();

    glfwDefaultWindowHints();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

    GLFWwindow* handle = glfwCreateWindow(hints.Width, hints.Height, hints.Title.c_str(), nullptr,  nullptr);
    glfwSetWindowUserPointer(handle, window);
    window->SetHandle(handle);

    glfwMakeContextCurrent(handle);
    glfwSwapInterval(GLFW_TRUE);

    //GLAD loads the driver functions once per runtime
    static bool loadOpenGL = true;
    if (loadOpenGL)
    {
        gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        loadOpenGL = false;
    }

    IMGUI_CHECKVERSION();
    window->SetImGuiContext(ImGui::CreateContext());
    ImGui::SetCurrentContext(window->GetImGuiContext());
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(handle, true);
    ImGui_ImplOpenGL3_Init("#version 150");
    m_Windows.push_back(window);

    return window;
}

void WindowSubsystem::DestroyWindow(Window* window)
{
    glfwDestroyWindow(window->GetHandle());
    ImGui::DestroyContext(window->GetImGuiContext());
}

void WindowSubsystem::HandleApplicationUpdatedEvent(const ApplicationUpdatedEvent& event)
{
    RenderWindows();
}

void WindowSubsystem::RenderWindows()
{
    
    for (Window* window : m_Windows)
    {
        glfwMakeContextCurrent(window->GetHandle());
        ImGui::SetCurrentContext(window->GetImGuiContext());
        glfwPollEvents();

        UpdateWindowVisiblity(window);
        RenderWindow(window);

        if (window->ShouldClose())
        {
             // For now, I don't know how to handle a Window that wants to close itself. I hide it instead.
            window->SetVisible(false);
            continue;
        }
    }
}

void WindowSubsystem::UpdateWindowVisiblity(Window* window)
{
    //Delayed Visibility Update
    bool currentVisibility = (glfwGetWindowAttrib(window->GetHandle(), GLFW_VISIBLE) == GLFW_TRUE);
    if (window->IsVisible() != currentVisibility)
    {
        if (window->IsVisible())
        {
            glfwShowWindow(window->GetHandle());
        }
        else
        {
            glfwHideWindow(window->GetHandle());
        }

        WindowVisibilityChangedEvent event;
        event.SetWindow(window);
        event.Broadcast();
    }
}

void WindowSubsystem::RenderWindow(Window* window)
{
    if (window->IsVisible())
    {
        // Update Window Viewport
        {
            int width, height;
            glfwGetFramebufferSize(window->GetHandle(), &width, &height);
            glViewport(0, 0, width, height);
            glClearColor(0, 0, 0, 1);
            glClear(GL_COLOR_BUFFER_BIT);
        }

        // Render Frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        {
            WindowRenderEvent event;
            event.SetWindow(window);
            event.Broadcast();
        }
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window->GetHandle());
    }
}

