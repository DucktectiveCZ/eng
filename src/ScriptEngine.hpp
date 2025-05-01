#ifndef ENG_SCRIPT_ENGINE_HPP
#define ENG_SCRIPT_ENGINE_HPP

#include <atomic>
#include <memory>
#include <string_view>

#include <sol/sol.hpp>
#include <spdlog/logger.h>
#include <sol/state.hpp>

#include "Result.hpp"

namespace engine {

class ScriptEngine final {
private:
    std::shared_ptr<spdlog::logger> m_Logger;
    std::shared_ptr<std::atomic<bool>> m_EngineRunning;
    sol::state m_Lua;

    Result<> InitGlobals();
    Result<> LoadLibs();

public:
    ScriptEngine(sol::state&& lua, std::shared_ptr<spdlog::logger> logger, std::shared_ptr<std::atomic<bool>> engineRunningRef);
    ~ScriptEngine() = default;

    static Result<std::shared_ptr<ScriptEngine>> New(std::shared_ptr<spdlog::logger> logger, std::shared_ptr<std::atomic<bool>> engineRunningFlagRef);

    Result<> Execute(const std::string_view source);
    Result<> ExecuteFile(const std::string_view path);
};

}
#endif // !ENG_SCRIPT_ENGINE_HPP

