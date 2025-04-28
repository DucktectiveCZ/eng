#ifndef ENG_PLATFORM_HPP
#define ENG_PLATFORM_HPP

namespace engine {
enum class Platform {
    Unknown = 0,
    Linux,
    Darwin,
    Windows,
};

inline Platform GetPlatform()
{
#if defined(_WIN32) || defined(_WIN64)
    return Platform::Windows;
#elif defined(__linux__)
    return Platform::Linux;
#elif defined(__APPLE__) || defined(__MACH__)
    return Platform::Darwin;
#else
    return Platform::Unknown;
#endif
}
}

#endif // !ENG_PLATFORM_HPP
