#ifndef ENG_CONFIG_HPP
#define ENG_CONFIG_HPP

#include <SDL2/SDL_video.h>

namespace engine {

enum class DefaultKeybind {
    // Movement
    MoveForward,
    MoveBackward,
    MoveLeft,
    MoveRight,
    Jump,
    Duck,
    Sprint,
    Dash,

    // Combat
    UseItem,
    AttackPrimary,
    AttackSecondary,
    Reload,
    Aim,
    Block,

    // Interaction
    Interact,
    OpenInventory,
    OpenMap,
    OpenQuests,

    // System
    Exit,
    Confirm,
    Cancel,
    QuickSave,
    QuickLoad,
    Screenshot,

    // UI Navigation
    NavigateUp,
    NavigateDown,
    NavigateLeft,
    NavigateRight,
    Select,
    Back,

    // Meta
    DebugToggle,
    ToggleFullscreen,

    // Contextual / Game-specific
    Ability1,
    Ability2,
    Ability3,
    Ability4,
    Ability5,

    // Enumerator Count
    _EnumeratorCount
};

struct Config {
    struct {
        int X;
        int Y;
        int Width;
        int Height;
    } Window;

    struct {
        bool Accelerated;
        bool VSync;
    } Render;

    struct {
        ;
    } Controlling;

    static inline Config Default()
    {
        return Config {
            .Window = {
                .X = SDL_WINDOWPOS_CENTERED,
                .Y = SDL_WINDOWPOS_CENTERED,
                .Width = 800,
                .Height = 600,
            },
            .Render = {
                .Accelerated = true,
                .VSync = false,
            },
        };
    }
};

} // namespace engine

#endif // !ENG_CONFIG_HPP
