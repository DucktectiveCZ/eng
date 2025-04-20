#ifndef ENG_PANIC_HPP
#define ENG_PANIC_HPP

#include <string_view>

#ifdef _MSC_VER
#include <intrin.h>
#else
#include <csignal>
#endif

namespace engine {

inline void DebugBreak()
{
#ifndef NDEBUG
#ifdef _MSC_VER
    __debugbreak();
#else
    raise(SIGTRAP);
#endif
#endif
}

[[noreturn]]
void Panic(const std::string_view message, const bool critical = false);

} // namespace engine

#endif // ENG_PANIC_HPP
