#ifndef ENG_CONSTANTS_HPP
#define ENG_CONSTANTS_HPP

#include <string_view>

namespace engine {
namespace constants {

#if defined(_WIN32) || defined(_WIN64)
constexpr std::string_view RuntimeDirPath = "C:\\Program Files\\DuckEngine";
#elif defined(__linux__)
constexpr std::string_view RuntimeDirPath = "/usr/local/share/DuckEngine/";
#elif defined(__APPLE__)
constexpr std::string_view RuntimeDirPath = "/usr/local/share/DuckEngine/";
#endif

#if defined(_WIN32) || defined(_WIN64)
constexpr std::string_view RuntimeLibLuaDirPath = "C:\\Program Files\\DuckEngine\\Lib\\Lua";
#elif defined(__linux__)
constexpr std::string_view RuntimeLibLuaDirPath = "/usr/local/share/DuckEngine/lib/lua";
#elif defined(__APPLE__)
constexpr std::string_view RuntimeLibLuaDirPath = "/usr/local/share/DuckEngine/lib/lua";
#endif

} // namespace constants
} // namespace engine

#endif // !ENG_CONSTANTS_HPP
