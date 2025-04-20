#include "Game.hpp"
#include "Result.hpp"

namespace engine {
namespace game {
    Resolution::Resolution(unsigned int w, unsigned int h)
    {
        Width = w;
        Height = h;
    }

    Result<Resolution> FromVector(const std::vector<unsigned int>& vec)
    {
        if (vec.size() != 2)
            return Error::InvalidFormat;

        return Result(Resolution(vec[0], vec[1]));
    }

} // namespace game
} // namespace engine
