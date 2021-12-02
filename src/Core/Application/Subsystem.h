#pragma once

class IApplication;

class Subsystem
{
public:
    Subsystem(IApplication* application);
    virtual ~Subsystem();

    virtual void Initialize() = 0;
    virtual void Shutdown() = 0;

    IApplication* GetApplication() const { return m_Application; }

private:
    IApplication* m_Application;
};