#ifndef ENG_ENGINE_HPP
#define ENG_ENGINE_HPP

#include <atomic>
#include <filesystem>
#include <memory>
#include <optional>

#include <spdlog/logger.h>
#include <string_view>
#include <toml++/toml.hpp>

#include "Config.hpp"
#include "Game.hpp"
#include "RenderingEngine.hpp"
#include "Result.hpp"
#include "ScriptEngine.hpp"
#include "State.hpp"

namespace engine {

enum class GameFormat {
    FOLDER,
};

class Engine final {
public:
    Engine(const Config& cfg, std::shared_ptr<spdlog::logger> logger, std::shared_ptr<ScriptEngine> script, std::shared_ptr<RenderingEngine> rendering, std::shared_ptr<std::atomic<bool>> runningFlag);
    ~Engine();

    static Result<std::shared_ptr<Engine>> New(const int argc, const char* argv[]);

    Result<> LoadGame(const std::filesystem::path& path, const GameFormat gameFormat);
    Result<> Start();

    void Shutdown();

private:
    Config m_Cfg;
    std::optional<game::Game> m_Game;
    const std::shared_ptr<spdlog::logger> m_Logger;
    std::shared_ptr<ScriptEngine> m_Script;
    std::shared_ptr<RenderingEngine> m_RenderingEngine;
    std::shared_ptr<std::atomic<bool>> m_RunningFlag;
    std::shared_ptr<std::atomic<State>> m_State;
};
}

#endif // !ENG_ENGINE_HPP
