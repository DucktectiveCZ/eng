#ifndef ENG_CONFIG_HPP
#define ENG_CONFIG_HPP

#include "SDL_video.h"

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

#endif // !ENG_CONFIG_HPP
