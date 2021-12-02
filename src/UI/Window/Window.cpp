#include "UI/Window/Window.h"

#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

void Window::Create(const WindowHints& hints)
{
    glfwDefaultWindowHints();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

    m_Handle = glfwCreateWindow(hints.Width, hints.Height, hints.Title.c_str(), nullptr,  nullptr);
    glfwMakeContextCurrent(m_Handle);
    glfwSwapInterval(GLFW_TRUE);

    //GLAD loads the driver functions once per runtime
    static bool loadOpenGL = true;
    if (loadOpenGL)
    {
        gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        loadOpenGL = false;
    }

    IMGUI_CHECKVERSION();
    m_ImGuiContext = ImGui::CreateContext();
    ImGui::SetCurrentContext(m_ImGuiContext);
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(m_Handle, true);
    ImGui_ImplOpenGL3_Init("#version 150");
}

void Window::BeginFrame()
{
    glfwMakeContextCurrent(m_Handle);
    ImGui::SetCurrentContext(m_ImGuiContext);

    //Synchronize Framebuffer & OpenGL
    {
        int width, height;
        glfwGetFramebufferSize(m_Handle, &width, &height);
        glViewport(0, 0, width, height);
        glClearColor(0, 0, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    //Render ImGui Context
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }
}


void Window::EndFrame()
{
    //Finish ImGui Frame
    {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
    glfwSwapBuffers(m_Handle);
}

void Window::Destroy()
{
    ImGui::DestroyContext(m_ImGuiContext);
    glfwDestroyWindow(m_Handle);
    m_Handle = nullptr;
    m_ImGuiContext = nullptr;
}
