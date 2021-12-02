#pragma once

#include <cassert>
#include <type_traits>

#include "Core/Event/Event.h"

class IEventHandler
{
public:
    virtual ~IEventHandler() = default;
    virtual void Call(const IEvent& event) = 0;
};

template<class TARGET, class EVENT>
class EventCallback : public IEventHandler
{
    static_assert(std::is_base_of_v<IEvent, EVENT>);

    using TargetPtr = TARGET*;
    using MethodPtr = void(TARGET::*)(const EVENT&);
public:
    void Init(TargetPtr target, MethodPtr callback)
    {
        m_Target = target;
        m_Callback = callback;
    }

    void Reset()
    {
        m_Target = nullptr;
        m_Callback = nullptr;
    }

    void Call(const IEvent& event) override
    {
        assert(m_Target);
        if (const EVENT* castEvent = dynamic_cast<const EVENT*>(&event))
        {
            (m_Target->*m_Callback)(*castEvent);
        }
    }

private:
    TargetPtr m_Target;
    MethodPtr m_Callback;
};