#ifndef ENG_ENGINE_HPP
#define ENG_ENGINE_HPP

#include "Game.hpp"
#include "Result.hpp"
#include "SDL_video.h"
#include "ScriptEngine.hpp"
#include <filesystem>
#include <memory>
#include <spdlog/logger.h>
#include <toml++/toml.hpp>

namespace engine {
struct Config final {
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

    Config() = delete;

    static inline Config Default() {
        return Config {
            .Window = {
                .X = SDL_WINDOWPOS_UNDEFINED,
                .Y = SDL_WINDOWPOS_UNDEFINED,
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

enum class GameFormat {
    FOLDER,
};

class Engine final {
public:
    ~Engine();

    static Result<Engine> New(const int argc, const char* argv[]);

    Result<game::Game> LoadGame(const std::filesystem::path& path, const GameFormat gameFormat) const;
    Result<> StartGame(const game::Game& game) const;

private:
    Config m_Cfg;
    const std::shared_ptr<spdlog::logger> m_Logger;
    ScriptEngine m_Script;

    Engine(const Config cfg, std::shared_ptr<spdlog::logger> logger, ScriptEngine script);
};
}

#endif // !ENG_ENGINE_HPP
