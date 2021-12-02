#pragma once

class Application;

class Subsystem
{
public:
    virtual ~Subsystem();

    virtual void Initialize() = 0;
    virtual void Shutdown() = 0;

    void SetApplication(Application* application) { m_Application = application; }
    Application* GetApplication() const { return m_Application; }

private:
    Application* m_Application;
};