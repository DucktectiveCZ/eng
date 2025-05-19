#ifndef ENG_LUA_INTEROP_HPP
#define ENG_LUA_INTEROP_HPP

#include <cstdint>

#include <sol/state_view.hpp>
#include <SDL2/SDL_keycode.h>

#include "Result.hpp"
#include "SDL_mouse.h"

namespace engine {
namespace luaInterop {

enum class Key {
    Unknown = SDLK_UNKNOWN,
    Return = SDLK_RETURN,
    Escape = SDLK_ESCAPE,
    Backspace = SDLK_BACKSPACE,
    Tab = SDLK_TAB,
    Space = SDLK_SPACE,
    Exclamation = SDLK_EXCLAIM,
    Quotation = SDLK_QUOTEDBL,
    Hash = SDLK_HASH,
    Percent = SDLK_PERCENT,
    Dollar = SDLK_DOLLAR,
    Ampersand = SDLK_AMPERSAND,
    Quote = SDLK_QUOTE,
    LeftParenthesis = SDLK_LEFTPAREN,
    RightParenthesis = SDLK_RIGHTPAREN,
    Asterisk = SDLK_ASTERISK,
    Plus = SDLK_PLUS,
    Comma = SDLK_COMMA,
    Minus = SDLK_MINUS,
    Period = SDLK_PERIOD,
    Slash = SDLK_SLASH,
    Zero = SDLK_0,
    One = SDLK_1,
    Two = SDLK_2,
    Three = SDLK_3,
    Four = SDLK_4,
    Five = SDLK_5,
    Six = SDLK_6,
    Seven = SDLK_7,
    Eight = SDLK_8,
    Nine = SDLK_9,
    Colon = SDLK_COLON,
    Semicolon = SDLK_SEMICOLON,
    LessThan = SDLK_LESS,
    Equals = SDLK_EQUALS,
    GreaterThan = SDLK_GREATER,
    Question = SDLK_QUESTION,
    At = SDLK_AT,
    LeftBracket = SDLK_LEFTBRACKET,
    Backslash = SDLK_BACKSLASH,
    RightBracket = SDLK_RIGHTBRACKET,
    Caret = SDLK_CARET,
    Underscore = SDLK_UNDERSCORE,
    // Grave = SDLK_GRAVE,
    A = SDLK_a,
    B = SDLK_b,
    C = SDLK_c,
    D = SDLK_d,
    E = SDLK_e,
    F = SDLK_f,
    G = SDLK_g,
    H = SDLK_h,
    I = SDLK_i,
    J = SDLK_j,
    K = SDLK_k,
    L = SDLK_l,
    M = SDLK_m,
    N = SDLK_n,
    O = SDLK_o,
    P = SDLK_p,
    Q = SDLK_q,
    R = SDLK_r,
    S = SDLK_s,
    T = SDLK_t,
    U = SDLK_u,
    V = SDLK_v,
    W = SDLK_w,
    X = SDLK_x,
    Y = SDLK_y,
    Z = SDLK_z,
    CapsLock = SDLK_CAPSLOCK,
    F1 = SDLK_F1,
    F2 = SDLK_F2,
    F3 = SDLK_F3,
    F4 = SDLK_F4,
    F5 = SDLK_F5,
    F6 = SDLK_F6,
    F7 = SDLK_F7,
    F8 = SDLK_F8,
    F9 = SDLK_F9,
    F10 = SDLK_F10,
    F11 = SDLK_F11,
    F12 = SDLK_F12,
    PrintScreen = SDLK_PRINTSCREEN,
    ScrollLock = SDLK_SCROLLLOCK,
    Pause = SDLK_PAUSE,
    Insert = SDLK_INSERT,
    Home = SDLK_HOME,
    PageUp = SDLK_PAGEUP,
    Delete = SDLK_DELETE,
    End = SDLK_END,
    PageDown = SDLK_PAGEDOWN,
    Right = SDLK_RIGHT,
    Left = SDLK_LEFT,
    Down = SDLK_DOWN,
    Up = SDLK_UP,
    NumLockClear = SDLK_NUMLOCKCLEAR,
    KeypadDivide = SDLK_KP_DIVIDE,
    KeypadMultiply = SDLK_KP_MULTIPLY,
    KeypadMinus = SDLK_KP_MINUS,
    KeypadPlus = SDLK_KP_PLUS,
    KeypadEnter = SDLK_KP_ENTER,
    Keypad1 = SDLK_KP_1,
    Keypad2 = SDLK_KP_2,
    Keypad3 = SDLK_KP_3,
    Keypad4 = SDLK_KP_4,
    Keypad5 = SDLK_KP_5,
    Keypad6 = SDLK_KP_6,
    Keypad7 = SDLK_KP_7,
    Keypad8 = SDLK_KP_8,
    Keypad9 = SDLK_KP_9,
    Keypad0 = SDLK_KP_0,
    KeypadPeriod = SDLK_KP_PERIOD,
    Application = SDLK_APPLICATION,
    Power = SDLK_POWER,
    KeypadEquals = SDLK_KP_EQUALS,
    F13 = SDLK_F13,
    F14 = SDLK_F14,
    F15 = SDLK_F15,
    F16 = SDLK_F16,
    F17 = SDLK_F17,
    F18 = SDLK_F18,
    F19 = SDLK_F19,
    F20 = SDLK_F20,
    F21 = SDLK_F21,
    F22 = SDLK_F22,
    F23 = SDLK_F23,
    F24 = SDLK_F24,
    Execute = SDLK_EXECUTE,
    Help = SDLK_HELP,
    Menu = SDLK_MENU,
    Select = SDLK_SELECT,
    Stop = SDLK_STOP,
    Again = SDLK_AGAIN,
    Undo = SDLK_UNDO,
    Cut = SDLK_CUT,
    Copy = SDLK_COPY,
    Paste = SDLK_PASTE,
    Find = SDLK_FIND,
    Mute = SDLK_MUTE,
    VolumeUp = SDLK_VOLUMEUP,
    VolumeDown = SDLK_VOLUMEDOWN,
    LAlt = SDLK_LALT,
    RAlt = SDLK_RALT,
    LControl = SDLK_LCTRL,
    RControl = SDLK_RCTRL,
    LShift = SDLK_LSHIFT,
    RShift = SDLK_RSHIFT,
};

enum class MouseButton {
    Left = SDL_BUTTON_LEFT,
    Right = SDL_BUTTON_RIGHT,
    Middle = SDL_BUTTON_MIDDLE,
    Extra1 = SDL_BUTTON_X1,
    Extra2 = SDL_BUTTON_X2,
};

struct Event { };

// SceneEvents
struct QuittingEvent : Event { };
struct LowMemoryEvent : Event { };
struct EnteringBackgroundEvent : Event { };
struct EnteredBackgroundEvent : Event { };
struct EnteringForegroundEvent : Event { };
struct EnteredForegroundEvent : Event { };
struct ResizedEvent : Event {
    unsigned int Width;
    unsigned int Height;
};
struct MinimizedEvent : Event { };
struct MaximizedEvent : Event { };
struct RestoredEvent : Event { };
struct PositionedEvent : Event {
    unsigned int X;
    unsigned int Y;

    inline PositionedEvent(unsigned int x, unsigned int y)
        : X(x)
        , Y(y)
    {
    }
};
struct MouseEnteredEvent : PositionedEvent { };
struct MouseLeftEvent : PositionedEvent { };
struct FocusGainedEvent : Event { };
struct FocusLostEvent : Event { };
struct KeyEvent : Event {
    Key Key_;
    bool Control;
    bool Shift;
    bool Alt;
};
struct KeyDownEvent : KeyEvent { };
struct KeyUpEvent : KeyEvent { };
struct MouseClickEvent : PositionedEvent {
    inline MouseClickEvent(unsigned int x, unsigned int y, MouseButton button)
        : PositionedEvent(x, y)
        , Button(button)
    {
    }

    MouseButton Button;
};
struct MouseDownEvent : MouseClickEvent {
    inline MouseDownEvent(unsigned int x, unsigned int y, MouseButton button)
        : MouseClickEvent(x, y, button)
    {
    }
};
struct MouseUpEvent : MouseClickEvent {
    inline MouseUpEvent(unsigned int x, unsigned int y, MouseButton button)
        : MouseClickEvent(x, y, button)
    {
    }
};
struct MouseMoveEvent : PositionedEvent {
    inline MouseMoveEvent(unsigned int x, unsigned int y)
        : PositionedEvent(x, y)
    {
    }
};
struct MouseScrollEvent : Event {
    int32_t X;
    int32_t Y;
};

// Collider events
struct CollissionEvent : PositionedEvent {
    // Entity Other;
};

Result<> Register(sol::state_view lua);

} // namespace luaInterop
} // namespac engine

#endif // !ENG_LUA_INTEROP_HPP
