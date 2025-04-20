#ifndef ENG_GAME_HPP
#define ENG_GAME_HPP

#include "Platform.hpp"
#include "Util.hpp"
#include <optional>
#include <string>
#include <vector>

namespace engine {
namespace game {
    enum class Platform {
        Linux = 0,
        Darwin = 1,
        Windows = 2,
    };
    inline Result<Platform> FromPlatformPlatform(const ::engine::Platform& platf) {
        switch (platf) {
        case ::engine::Platform::Linux:
            return Result(Platform::Linux);
        case ::engine::Platform::Darwin:
            return Result(Platform::Darwin);
        case ::engine::Platform::Windows:
            return Result(Platform::Windows);
        default:
            return Error(Error::UnknownEnumVariant, "Unknown or unconvertable platform enum variant");
        };
    }

    enum class LuaTarget {
        Lua51,
        Lua54,
        LuaJit,
    };

    struct Resolution {
        unsigned int Width;
        unsigned int Height;

        Resolution() = default;
        Resolution(unsigned int w, unsigned int h);

        static Resolution FromTomlArray(const std::vector<unsigned int>& vec);
    };

    struct TargetMetadata {
        std::vector<Platform> Platforms;
        LuaTarget Lua;
    };

    struct GraphicsMetadata {
        Resolution WindowResolution = Resolution();
        bool WindowFullscreen = false;
        bool WindowResizing = false;
    };

    struct AudioMetadata {
        float Volume = -1.0f;
    };

    struct GameMetadata {
        std::string EntryScene = "<not set>";
    };

    struct Metadata {
        std::string Name = "<not set>";
        std::string Title = "<not set>";
        std::string Author = "<not set>";
        std::string License = "<not set>";
        std::optional<std::string> Description = std::nullopt;
        util::Version Version = util::Version::Max();

        GameMetadata Game;
        GraphicsMetadata Graphics;
        AudioMetadata Audio;
        TargetMetadata Target;
    };

    enum class ResourceType {
        Text,
        Sprite,
        Music,
        SoundEffect,
        Font,
        Animation,
    };

    struct ResourceDef {
        ResourceType Type;
        std::string Key;
        std::string Source;
        bool Lazy;
    };

    struct ResourceTable {
        std::vector<ResourceDef> Entries;
    };

    struct Game {
        Metadata Meta;
        ResourceTable Resources;
    };

} // namespace game
} // namespace engine

#endif // !ENG_GAME_HPP
