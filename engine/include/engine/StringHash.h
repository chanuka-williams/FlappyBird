#pragma once
#include <functional>
#include <string_view>

namespace engine
{

struct StringHash
{
    using is_transparent = void; // Enable heterogeneous lookup

    [[nodiscard]] size_t operator()(const std::string_view sv) const noexcept
    {
        return std::hash<std::string_view>{}(sv);
    }
};

struct StringEqual
{
    using is_transparent = void;

    [[nodiscard]] bool operator()(const std::string_view lhs, const std::string_view rhs) const noexcept
    {
        return lhs == rhs;
    }
};

} // namespace engine