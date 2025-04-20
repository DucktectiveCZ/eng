#ifndef ENG_UTIL_HPP
#define ENG_UTIL_HPP

#include "Result.hpp"
#include <cstdlib>
#include <string_view>

#define ENG_ASSERT(cond, msg)                                               \
    if (!cond) {                                                            \
        std::cout << "Assertion `" << #cond << "` failed: " << msg << "\n"; \
        engine::util::Panic("Assertion failed");                            \
    }

namespace engine {
namespace util {

    struct Version {
        Version();
        Version(const unsigned int major, const unsigned int minor, const unsigned int patch);

        static Result<Version> FromString(const std::string_view str);
        static Version Max();

        bool operator==(const Version& other) const
        {
            return Major == other.Major && Minor == other.Minor && Patch == other.Patch;
        }

        unsigned int Major;
        unsigned int Minor;
        unsigned int Patch;
    };

}
}

#endif // !ENG_UTIL_HPP
