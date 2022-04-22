#pragma once

#include <cstdint>
#include <array>
#include <vector>
#include <string_view>

namespace FNV
{
    static constexpr uint64_t FnvPrime  = 1099511628211UL;
    static constexpr uint64_t FnvBase   = 14695981039346656037UL;

    constexpr uint64_t Hash_uint64_t(uint64_t value, uint64_t hash = FnvBase)
    {
        hash ^= value; 
        hash *= FnvPrime;
        return hash;
    }

    template<class T>
    constexpr uint64_t Hash(const T& value, uint64_t hash = FnvBase);

    // 8 bit
    template<> constexpr uint64_t Hash(const uint8_t& value, uint64_t hash)    { return Hash_uint64_t(value, hash); }
    template<> constexpr uint64_t Hash(const int8_t& value, uint64_t hash)      { return Hash_uint64_t(value, hash); }
    template<> constexpr uint64_t Hash(const char& value, uint64_t hash)          { return Hash_uint64_t(value, hash); }
    // 16 bit
    template<> constexpr uint64_t Hash(const uint16_t& value, uint64_t hash)  { return Hash_uint64_t(value, hash); }
    template<> constexpr uint64_t Hash(const int16_t& value, uint64_t hash)    { return Hash_uint64_t(value, hash); }
    // 32 bit
    template<> constexpr uint64_t Hash(const uint32_t& value, uint64_t hash)  { return Hash_uint64_t(value, hash); }
    template<> constexpr uint64_t Hash(const int32_t& value, uint64_t hash)    { return Hash_uint64_t(value, hash); }
    // 64 bit
    template<> constexpr uint64_t Hash(const uint64_t& value, uint64_t hash)  { return Hash_uint64_t(value, hash); }
    template<> constexpr uint64_t Hash(const int64_t& value, uint64_t hash)    { return Hash_uint64_t(value, hash); }

    //Hash via Iterators
    template<class Iterator>
    constexpr uint64_t HashForEach(Iterator first, Iterator last, uint64_t hash = FnvBase)
    {
        for(; first != last; ++first)
        {
            hash = Hash(*first, hash);
        }
        return hash;
    }

    //std::string_view
    template<>
    constexpr uint64_t Hash(const std::string_view& str, uint64_t hash)
    {
        return HashForEach(str.begin(), str.end());
    }
}


