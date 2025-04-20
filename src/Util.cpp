#include "Util.hpp"
#include "Result.hpp"
#include <cstdio>
#include <cstdlib>
#include <limits>
#include <string_view>

namespace engine {
namespace util {
    Version::Version()
        : Version(0, 0, 0)
    {
    }

    Version::Version(
        const unsigned int major,
        const unsigned int minor,
        const unsigned int patch)
    {
        Major = major;
        Minor = minor;
        Patch = patch;
    }

    Result<Version> Version::FromString(const std::string_view str)
    {
        Version v;
        if (std::sscanf(str.data(), "%d.%d.%d", &v.Major, &v.Minor, &v.Patch) != 3) {
            return Error::InvalidFormat;
        }
        return Result(v);
    }

    Version Version::Max()
    {
        return Version(std::numeric_limits<unsigned int>::max(),
            std::numeric_limits<unsigned int>::max(),
            std::numeric_limits<unsigned int>::max());
    }

} // namespace util
} // namespace engine
