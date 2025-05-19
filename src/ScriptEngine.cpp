#include "ScriptEngine.hpp"

#include <string_view>
#include <string>
#include <utility>
#include <atomic>
#include <memory>
#include <filesystem>

#include <sol/state.hpp>
#include <sol/error.hpp>

#include "Panic.hpp"
#include "Result.hpp"
#include "Constants.hpp"

namespace engine {

ScriptEngine::ScriptEngine(sol::state&& lua, std::shared_ptr<spdlog::logger> logger, std::shared_ptr<std::atomic<bool>> engineRunningRef)
    : m_Logger(logger)
    , m_EngineRunning(engineRunningRef)
    , m_Lua(std::move(lua))
{
}

Result<> ScriptEngine::LoadLibs()
{
    namespace fs = std::filesystem;

    m_Logger->trace("Loading Lua libraries in {}", constants::RuntimeLibLuaDirPath);

    if (!std::filesystem::exists(constants::RuntimeLibLuaDirPath)) {
        m_Logger->warn("No Lua library path. This could cause some games not to work! In that case, try reinstalling the engine");
        return Result();
    }

    std::error_code errCode;
    for (const auto& entry : fs::recursive_directory_iterator(constants::RuntimeLibLuaDirPath, errCode)) {
        if (errCode) {
            m_Logger->error("{}", errCode.message());
            return Error(Error::Io, errCode.message());
        }

        auto path = entry.path();


        if (!entry.is_regular_file()) {
            m_Logger->warn("{} isn't a regular file, ignoring", path.string());
            continue;
        }

        m_Logger->trace("Loading {}", path.string());

        auto res = ExecuteFile(path.string());
        if (!res)
            return res;
    }

    m_Logger->debug("Lua libraries loaded");
    return Result();
}

Result<> ScriptEngine::InitGlobals()
{
    m_Lua.set_function("debug", [this](std::string msg){
        m_Logger->info("[lua-dbg]  {}", msg);
    });
    m_Lua.set_function("info", [this](std::string msg){
        m_Logger->info("[lua-info] {}", msg);
    });
    m_Lua.set_function("warn", [this](std::string msg){
        m_Logger->info("[lua-warn] {}", msg);
    });
    m_Lua.set_function("error", [this](std::string msg){
        m_Logger->info("[lua-err]  {}", msg);
    });
    m_Lua.set_function("quit", [this](){
        m_Logger->info("[lua-sys]  Quitting");
        m_EngineRunning->store(false);
    });

    auto res = LoadLibs();
    if (!res)
        return res;

    return Result();
}

Result<std::shared_ptr<ScriptEngine>> ScriptEngine::New(
    std::shared_ptr<spdlog::logger> logger,
    std::shared_ptr<std::atomic<bool>> engineRunningFlagRef
)
{
    sol::state lua([](auto) -> int {
        Panic("The Lua runtime panicked.");
        return 1;
    });

    auto self = std::make_shared<ScriptEngine>(std::move(lua), logger, engineRunningFlagRef);

    auto res = self->InitGlobals();
    if (!res)
        return Error(res.UnwrapErr());

    logger->info("Using script runtime {} by {}", LUA_RELEASE, LUA_AUTHORS);

    return Result(self);
}


Result<> ScriptEngine::Execute(const std::string_view source)
{
    auto result = m_Lua.script(source);
    if (result.valid())
        return Result();

    sol::error err = result;
    m_Logger->error("Lua execution error: {}", err.what());
    return Error(Error::Lua, err.what());
}

Result<> ScriptEngine::ExecuteFile(const std::string_view path)
{
    auto result = m_Lua.script_file(path.data());
    if (result.valid())
        return Result();

    sol::error err = result;
    m_Logger->error("Lua file execution error: {}", err.what());
    return Error(Error::Lua, err.what());
}

} // namespace engine

