#include "LuaInterop.hpp"

#include <exception>

#include <sol/forward.hpp>
#include <sol/inheritance.hpp>

#include "Result.hpp"

namespace engine {
namespace luaInterop {

Result<> Register(sol::state_view lua)
{
    try {
        lua.new_enum(
            "Key",
            "Unknown", Key::Unknown,
            "Return", Key::Return,
            "Escape", Key::Escape,
            "Backspace", Key::Backspace,
            "Tab", Key::Tab,
            "Space", Key::Space,
            "Exclamation", Key::Exclamation,
            "Quotation", Key::Quotation,
            "Hash", Key::Hash,
            "Percent", Key::Percent,
            "Dollar", Key::Dollar,
            "Ampersand", Key::Ampersand,
            "Quote", Key::Quote,
            "LeftParenthesis", Key::LeftParenthesis,
            "RightParenthesis", Key::RightParenthesis,
            "Asterisk", Key::Asterisk,
            "Plus", Key::Plus,
            "Comma", Key::Comma,
            "Minus", Key::Minus,
            "Period", Key::Period,
            "Slash", Key::Slash,
            "Zero", Key::Zero,
            "One", Key::One,
            "Two", Key::Two,
            "Three", Key::Three,
            "Four", Key::Four,
            "Five", Key::Five,
            "Six", Key::Six,
            "Seven", Key::Seven,
            "Eight", Key::Eight,
            "Nine", Key::Nine,
            "Colon", Key::Colon,
            "Semicolon", Key::Semicolon,
            "LessThan", Key::LessThan,
            "Equals", Key::Equals,
            "GreaterThan", Key::GreaterThan,
            "Question", Key::Question,
            "At", Key::At,
            "LeftBracket", Key::LeftBracket,
            "Backslash", Key::Backslash,
            "RightBracket", Key::RightBracket,
            "Caret", Key::Caret,
            "Underscore", Key::Underscore,
            "A", Key::A,
            "B", Key::B,
            "C", Key::C,
            "D", Key::D,
            "E", Key::E,
            "F", Key::F,
            "G", Key::G,
            "H", Key::H,
            "I", Key::I,
            "J", Key::J,
            "K", Key::K,
            "L", Key::L,
            "M", Key::M,
            "N", Key::N,
            "O", Key::O,
            "P", Key::P,
            "Q", Key::Q,
            "R", Key::R,
            "S", Key::S,
            "T", Key::T,
            "U", Key::U,
            "V", Key::V,
            "W", Key::W,
            "X", Key::X,
            "Y", Key::Y,
            "Z", Key::Z,
            "CapsLock", Key::CapsLock,
            "F1", Key::F1,
            "F2", Key::F2,
            "F3", Key::F3,
            "F4", Key::F4,
            "F5", Key::F5,
            "F6", Key::F6,
            "F7", Key::F7,
            "F8", Key::F8,
            "F9", Key::F9,
            "F10", Key::F10,
            "F11", Key::F11,
            "F12", Key::F12,
            "PrintScreen", Key::PrintScreen,
            "ScrollLock", Key::ScrollLock,
            "Pause", Key::Pause,
            "Insert", Key::Insert,
            "Home", Key::Home,
            "PageUp", Key::PageUp,
            "Delete", Key::Delete,
            "End", Key::End,
            "PageDown", Key::PageDown,
            "Right", Key::Right,
            "Left", Key::Left,
            "Down", Key::Down,
            "Up", Key::Up,
            "NumLockClear", Key::NumLockClear,
            "KeypadDivide", Key::KeypadDivide,
            "KeypadMultiply", Key::KeypadMultiply,
            "KeypadMinus", Key::KeypadMinus,
            "KeypadPlus", Key::KeypadPlus,
            "KeypadEnter", Key::KeypadEnter,
            "Keypad1", Key::Keypad1,
            "Keypad2", Key::Keypad2,
            "Keypad3", Key::Keypad3,
            "Keypad4", Key::Keypad4,
            "Keypad5", Key::Keypad5,
            "Keypad6", Key::Keypad6,
            "Keypad7", Key::Keypad7,
            "Keypad8", Key::Keypad8,
            "Keypad9", Key::Keypad9,
            "Keypad0", Key::Keypad0,
            "KeypadPeriod", Key::KeypadPeriod,
            "Application", Key::Application,
            "Power", Key::Power,
            "KeypadEquals", Key::KeypadEquals,
            "F13", Key::F13,
            "F14", Key::F14,
            "F15", Key::F15,
            "F16", Key::F16,
            "F17", Key::F17,
            "F18", Key::F18,
            "F19", Key::F19,
            "F20", Key::F20,
            "F21", Key::F21,
            "F22", Key::F22,
            "F23", Key::F23,
            "F24", Key::F24,
            "Execute", Key::Execute,
            "Help", Key::Help,
            "Menu", Key::Menu,
            "Select", Key::Select,
            "Stop", Key::Stop,
            "Again", Key::Again,
            "Undo", Key::Undo,
            "Cut", Key::Cut,
            "Copy", Key::Copy,
            "Paste", Key::Paste,
            "Find", Key::Find,
            "Mute", Key::Mute,
            "VolumeUp", Key::VolumeUp,
            "VolumeDown", Key::VolumeDown,
            "LAlt", Key::LAlt,
            "RAlt", Key::RAlt,
            "LControl", Key::LControl,
            "RControl", Key::RControl,
            "LShift", Key::LShift,
            "RShift", Key::RShift
        );

        lua.new_enum(
            "MouseButton",
            "Left", MouseButton::Left,
            "Right", MouseButton::Right,
            "Middle", MouseButton::Middle
        );

        lua.new_usertype<Event>(
            "Event"
        );

        lua.new_usertype<QuittingEvent>(
            "QuittingEvent",
            sol::base_classes, sol::bases<Event>()
        );
        lua.new_usertype<LowMemoryEvent>(
            "LowMemoryEvent",
            sol::base_classes, sol::bases<Event>()
        );
        lua.new_usertype<EnteringBackgroundEvent>(
            "EnteringBackgroundEvent",
            sol::base_classes, sol::bases<Event>()
        );
        lua.new_usertype<EnteredBackgroundEvent>(
            "EnteredBackgroundEvent",
            sol::base_classes, sol::bases<Event>()
        );
        lua.new_usertype<EnteringForegroundEvent>(
            "EnteringForegroundEvent",
            sol::base_classes, sol::bases<Event>()
        );
        lua.new_usertype<EnteredForegroundEvent>(
            "EnteredForegroundEvent",
            sol::base_classes, sol::bases<Event>()
        );
        lua.new_usertype<ResizedEvent>(
            "ResizedEvent",
            sol::base_classes, sol::bases<Event>(),
            "width", &ResizedEvent::Width,
            "height", &ResizedEvent::Height
        );
        lua.new_usertype<MinimizedEvent>(
            "MinimizedEvent",
            sol::base_classes, sol::bases<Event>()
        );
        lua.new_usertype<MaximizedEvent>(
            "MaximizedEvent",
            sol::base_classes, sol::bases<Event>()
        );
        lua.new_usertype<RestoredEvent>(
            "RestoredEvent",
            sol::base_classes, sol::bases<Event>()
        );
        lua.new_usertype<PositionedEvent>(
            "MouseEvent",
            sol::base_classes, sol::bases<Event>(),
            "x", &PositionedEvent::X,
            "y", &PositionedEvent::Y
        );
        lua.new_usertype<MouseEnteredEvent>(
            "MouseEnteredEvent",
            sol::base_classes, sol::bases<Event, PositionedEvent>()
        );
        lua.new_usertype<MouseLeftEvent>(
            "MouseEnteredEvent",
            sol::base_classes, sol::bases<Event, PositionedEvent>()
        );
        lua.new_usertype<FocusGainedEvent>(
            "FocusGainedEvent",
            sol::base_classes, sol::bases<Event>()
        );
        lua.new_usertype<FocusLostEvent>(
            "FocusLostEvent",
            sol::base_classes, sol::bases<Event>()
        );
        lua.new_usertype<KeyEvent>(
            "KeyEvent",
            "key", &KeyEvent::Key_,
            "shift", &KeyEvent::Shift,
            "control", &KeyEvent::Control,
            "alt", &KeyEvent::Alt,
            sol::base_classes, sol::bases<Event>()
        );
        lua.new_usertype<KeyDownEvent>(
            "KeyDownEvent",
            sol::base_classes, sol::bases<Event, KeyEvent>()
        );
        lua.new_usertype<KeyUpEvent>(
            "KeyUpEvent",
            sol::base_classes, sol::bases<Event, KeyEvent>()
        );
        lua.new_usertype<MouseClickEvent>(
            "MouseClickEvent",
            sol::base_classes, sol::bases<Event, PositionedEvent>()
        );
        lua.new_usertype<MouseDownEvent>(
            "MouseDownEvent",
            sol::base_classes, sol::bases<Event, MouseClickEvent>()
        );
        lua.new_usertype<MouseUpEvent>(
            "MouseUpEvent",
            sol::base_classes, sol::bases<Event, MouseClickEvent>()
        );
        lua.new_usertype<MouseMoveEvent>(
            "MouseMoveEvent",
            sol::base_classes, sol::bases<Event, PositionedEvent>()
        );
        lua.new_usertype<MouseScrollEvent>(
            "MouseScrollEvent",
            sol::base_classes, sol::bases<Event>()
        );
        lua.new_usertype<CollissionEvent>(
            "CollissionEvent",
            sol::base_classes, sol::bases<Event, PositionedEvent>()
        );
    } catch (const std::exception& ex) {
        return Error(Error::LuaInit, ex.what());
    }

    return Result();
}

} // namespace luaInterop
} // namespace engine

