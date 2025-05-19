#ifndef ENG_SYNCHRONIZED_HPP
#define ENG_SYNCHRONIZED_HPP

#include <mutex>
#include <utility>

namespace engine {

template <typename T>
class Synchronized {
private:
    mutable std::mutex m_Mutex;
    T m_Value;

public:
    virtual ~Synchronized() = default;

    Synchronized()
        : T()
    {
    }

    Synchronized(T&& val)
        : T(std::move(val))
    {
    }

    Synchronized(const T& val)
        : T(val)
    {
    }

    std::pair<T&, std::unique_lock<std::mutex>> Unlock() {
        return {m_Value, std::move(std::unique_lock<std::mutex>(m_Mutex))};
    }

    std::pair<const T&, std::unique_lock<std::mutex>> Unlock() const {
        return {m_Value, std::unique_lock<std::mutex>(m_Mutex)};
    }

    T Copy() const {
        std::lock_guard<std::mutex> lock(m_Mutex);

        return m_Value;
    }

    T&& Move() {
        return std::move(m_Value);
    }
};

} // namespace engine

#endif // !ENG_SYNCHRONIZED_HPP
