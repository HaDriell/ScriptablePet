#pragma once

#include <string_view>
#include "Core/Hash.h"

#pragma region TypeInfo Helpers

// Credits to the header library EnTT
namespace Private {
    template<class T>
    constexpr std::string_view GetTypeName()
    {
        constexpr auto function = std::string_view{__PRETTY_FUNCTION__};

        constexpr auto prefix = std::string_view{"T = "};
        constexpr auto suffix = std::string_view{"]"};

        constexpr auto start = function.find(prefix) + prefix.size();
        constexpr auto end = function.rfind(suffix);

        static_assert(start < end);

        return function.substr(start, (end - start));
    }
}

#pragma endregion

template<class T>
struct TypeInfo
{
    static_assert(std::is_const_v<T> == false);
public:
    static constexpr std::string_view   Name = Private::GetTypeName<T>();
    static constexpr uint32_t           Hash = FNV::Hash(Name);
    static constexpr size_t             Size = sizeof(T);
};
