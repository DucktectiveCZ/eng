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
    std::string typeString;
    switch (Type) {
    case engine::Error::ErrorType::Io:
        typeString = "Io";
        break;
    case engine::Error::ErrorType::Lua:
        typeString = "Lua";
        break;
    case engine::Error::ErrorType::Sdl:
        typeString = "Sdl";
        break;
    case engine::Error::ErrorType::LuaInit:
        typeString = "Lua initialization";
        break;
    case engine::Error::ErrorType::Unknown:
        typeString = "Unknown";
        break;
    case engine::Error::ErrorType::InvalidGame:
        typeString = "Invalid game";
        break;
    case engine::Error::ErrorType::InvalidState:
        typeString = "Invalid state";
        break;
    case engine::Error::ErrorType::LuaWrongType:
        typeString = "Wrong Lua type";
        break;
    case engine::Error::ErrorType::InvalidFormat:
        typeString = "Invalid format";
        break;
    case engine::Error::ErrorType::NotImplemented:
        typeString = "Not implemented";
        break;
    case engine::Error::ErrorType::LuaUnexpectedNil:
        typeString = "Unexpected `nil` Lua value";
        break;
    case engine::Error::ErrorType::UnknownEnumVariant:
        typeString = "Unknown enum variant";
        break;
    case engine::Error::ErrorType::UnsupportedPlatform:
        typeString = "Unsupported platform";
        break;
    }

    return fmt::format("{}: {}", typeString, Message);
}
}
