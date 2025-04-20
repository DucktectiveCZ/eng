#include "Panic.hpp"

#include <iostream>

[[noreturn]]
void engine::Panic(const std::string_view message, const bool critical)
{
    std::cerr << "Program panicked: " << message << std::endl;

    DebugBreak();

    if (!critical) [[unlikely]] {
        exit(101);
    }
    abort();
}
