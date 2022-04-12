#pragma once

#include <string_view>

// Credits to the header library EnTT
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