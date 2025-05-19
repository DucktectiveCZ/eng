#ifndef ENG_STATE_HPP
#define ENG_STATE_HPP

#include "Vector2.hpp"

namespace engine {

struct State {
    State() = default;
    State(const State&) = default;
    State(State&&) = default;
    State& operator=(const State&) = default;
    ~State() = default;

    struct {
        Vector2 Position = {0, 0};
        bool LeftButtonDown = false;
        bool RightButtonDown = false;
        bool MiddleButtonDown = false;
    } Mouse;
};

}

#endif // !ENG_STATE_HPP
