#include "sol/error.hpp"
#include <string>
#define SOL_NO_EXCEPTIONS 1

#include "ScriptEngine.hpp"

#include <atomic>
#include <memory>

#include <sol/state.hpp>

#include "Result.hpp"

namespace engine {

ScriptEngine::ScriptEngine(std::shared_ptr<sol::state> lua, std::shared_ptr<spdlog::logger> logger, std::shared_ptr<std::atomic<bool>> engineRunningRef)
    : m_Logger(logger)
    , m_EngineRunning(engineRunningRef)
    , m_Lua(lua)
{
}

Result<> engine::ScriptEngine::InitGlobals()
{
    m_Lua->set_function("debug", [this](std::string msg){
        this->m_Logger->info("[lua-dbg]  {}");
    });
    m_Lua->set_function("info", [this](std::string msg){
        this->m_Logger->info("[lua-info] {}");
    });
    m_Lua->set_function("warn", [this](std::string msg){
        this->m_Logger->info("[lua-warn] {}");
    });
    m_Lua->set_function("error", [this](std::string msg){
        this->m_Logger->info("[lua-err]  {}");
    });
    m_Lua->set_function("quit", [this](){
        this->m_EngineRunning->store(false);
    });
    return Result();
}

Result<std::shared_ptr<ScriptEngine>> ScriptEngine::New(std::shared_ptr<spdlog::logger> logger, std::shared_ptr<std::atomic<bool>> engineRunningFlagRef)
{
    sol::state lua;

    auto self = std::make_shared<ScriptEngine>(lua, logger, engineRunningFlagRef);

    auto res = self->InitGlobals();
    if (res.IsErr())
        return Error(res.UnwrapErr());

    logger->info("Using script runtime {} by {}", LUA_RELEASE, LUA_AUTHORS);

    return Result(self);
}


Result<> ScriptEngine::Execute(const std::string_view source)
{
    auto result = m_Lua->script(source);
    if (result.valid())
        return Result();

    sol::error err = result;
    m_Logger->error("Lua coude execution error: {}", err.what());
    return Error(Error::Lua, err.what());
}

}

