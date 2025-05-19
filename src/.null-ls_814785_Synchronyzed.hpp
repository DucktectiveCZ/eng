#ifndef ENG_SYNCHRONIZED_HPP
#define ENG_SYNCHRONIZED_HPP

#include <utility>

namespace engine {

template <typename T>
class Synchronized {
public:
    Synchronized()
        : T()
    {
    }

    Synchronized(T&& val)
        : T(std::move(val))
    {
    }

    Synchronized(const T& val)
        : T(l)
    {
    }
};

} // namespace engine

#endif // !ENG_SYNCHRONIZED_HPP
