#ifndef ENG_STATE_HPP
#define ENG_STATE_HPP

#include "Vector2.hpp"

namespace engine {

struct State {
    struct {
        Vector2 Position;
        bool LeftButtonDown;
        bool RightButtonDown;
        bool MiddleButtonDown;
    } Mouse;
};

}

#endif // !ENG_STATE_HPP
