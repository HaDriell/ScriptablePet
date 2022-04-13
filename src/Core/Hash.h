#pragma once

#include <cstdint>
#include <string_view>

namespace FNV
{
    static constexpr uint32_t FnvPrime  = 16777619u;
    static constexpr uint32_t FnvBase   = 2166136261u;

    constexpr uint32_t Hash(std::string_view str)
    {
        uint32_t hash = FnvBase;

        for (char c : str)
        {
            hash ^= c;
            hash *= FnvPrime;
        }
        
        return hash;
    }
}