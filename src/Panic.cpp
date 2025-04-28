#include "Panic.hpp"

#include <iostream>

[[noreturn]]
void engine::Panic(const std::string_view message, const bool critical)
{
    std::cerr << "\033[41m\033[30mProgram panicked:\033[0m \033[33m" << message << "\033[0m" << std::endl;

    DebugBreak();

    if (!critical) [[unlikely]] {
        exit(101);
    }
    abort();
}
