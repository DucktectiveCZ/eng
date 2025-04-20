#ifndef ENG_SCRIPT_ENGINE_HPP
#define ENG_SCRIPT_ENGINE_HPP

#include "Result.hpp"
#include <memory>
#include <spdlog/logger.h>
#include <string_view>
#include <vector>

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

namespace engine {

class ScriptEngine final {
private:
    std::shared_ptr<spdlog::logger> m_Logger;
    std::shared_ptr<lua_State> m_Lua;

    inline ScriptEngine(lua_State *lua, std::shared_ptr<spdlog::logger> logger)
        : m_Logger(logger)
        , m_Lua(lua)
    {
    }

public:
    ~ScriptEngine() = default;

    static inline Result<ScriptEngine> New(std::shared_ptr<spdlog::logger> logger) {
        lua_State *lua = luaL_newstate();
        luaL_openlibs(lua);
        std::shared_ptr<lua_State> lua_shared(lua, ScriptEngine::LuaStateDeleter);
        return Result(ScriptEngine(lua, logger));
    }

    inline Result<> Execute(const std::string_view source) {
        if (luaL_dostring(m_Lua.get(), source.data())) {
            auto error = lua_tostring(m_Lua.get(), -1);
            lua_pop(m_Lua.get(), 1);
            m_Logger->error("Source code couldn't be executed: {}", error);
            return Error(Error::Lua, error);
        }
        return Result();
    }

    inline Result<double> Call(const std::string_view key, const std::vector<int>& args) {
        lua_getglobal(m_Lua.get(), key.data());

        if (lua_isnil(m_Lua.get(), -1)) {
            m_Logger->error("Lua global {} not found", key);
            return Error::LuaUnexpectedNil;
        }

        if (!lua_isfunction(m_Lua.get(), -1)) {
            m_Logger->error("Lua global {} is not a function");
            return Error::LuaWrongType;
        }

        for (auto arg : args) {
            lua_pushnumber(m_Lua.get(), arg);
        }

        if (lua_pcall(m_Lua.get(), args.size(), 1, 0) != LUA_OK) {
            auto error = lua_tostring(m_Lua.get(), -1);
            m_Logger->error("Calling lua function {} failed: {}", key, error);
            return Error(Error::Lua, error);
        }
        double result = lua_tonumber(m_Lua.get(), -1);
        lua_pop(m_Lua.get(), 1);
        return Result(result);
    }

private:
    static inline void LuaStateDeleter(lua_State *state) {
        lua_close(state);
    }
};

}
#endif // !ENG_SCRIPT_ENGINE_HPP
