#include "Result.hpp"
#include <fmt/format.h>
#include <string>
#include <string_view>

namespace engine {
Error::Error(const ErrorType& et)
{
    Type = et;
    Message = "";
}
Error::Error(const ErrorType& et, std::string_view msg)
{
    Type = et;
    Message = msg;
}
std::string Error::ToString() const
{
    return fmt::format("{}: {}", (int)Type, Message);
}
}
