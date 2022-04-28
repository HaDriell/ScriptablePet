#pragma once

#include <cassert>

template<class T>
class UniqueProxy
{
public:
    static bool IsValid()
    {
        return ms_Instance != nullptr;
    }

    static T& Get()
    {
        assert(IsValid());
        return *ms_Instance;
    }

    static void Open(T* instance)
    {
        assert(!IsValid());
        ms_Instance = instance;
    }

    static void Close(T* instance)
    {
        assert(ms_Instance == instance);
        ms_Instance = nullptr;
    }

private:
    static inline T* ms_Instance = nullptr;
};