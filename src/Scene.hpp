#ifndef ENG_SCENE_HPP
#define ENG_SCENE_HPP

#include <optional>
#include <string>
#include <vector>

#include "SDL_render.h"
#include "Vector2.hpp"

namespace engine {

enum class CollissionType {
    Rectangular,
    Circular,
};

struct RectangularCollission {
    unsigned int Width;
    unsigned int Height;
};

struct CircularCollission {
    unsigned int Radius;
};

struct Collission {
    Vector2 RelativePosition;

    CollissionType Type;
    union {
        RectangularCollission Rectangular;
        CircularCollission Circular;
    } Data;
};

struct Sprite {
    SDL_Texture *Texture;
};

struct Entity {
    unsigned int Id;
    std::optional<std::string> Class;

    Vector2 Position;

    std::optional<Collission> CollisionComp;
    std::optional<Sprite> SpriteComp;
};

struct Scene {
    std::optional<std::string> Class;

    std::vector<Entity> Entities;
};

}

#endif // !ENG_SCENE_HPP
