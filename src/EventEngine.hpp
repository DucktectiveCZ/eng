#ifndef ENG_EVENT_ENGINE_HPP
#define ENG_EVENT_ENGINE_HPP

#include <array>
#include <atomic>
#include <cstddef>
#include <memory>
#include <optional>

#include <spdlog/logger.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
#include <sol/sol.hpp>
#include <sol/forward.hpp>
#include <type_traits>

#include "LuaInterop.hpp"
#include "RenderingEngine.hpp"
#include "Result.hpp"
#include "State.hpp"
#include "Policies.hpp"

namespace engine {

enum class LuaEvent : size_t {
    Quitting,
    LowMemory,
    EnteringBackground,
    EnteredBackground,
    EnteringForeground,
    EnteredForeground,
    Resized,
    Minimized,
    Maximized,
    Restored,
    MouseEntered,
    MouseLeft,
    FocusGained,
    FocusLost,
    KeyDown,
    KeyUp,
    MouseDown,
    MouseUp,
    MouseMove,
    MouseScroll,
    TextInput,
    TextEditing,
    _EnumeratorCount,
};

class EventEngine {
public:
    EventEngine(
        std::shared_ptr<spdlog::logger> logger,
        std::shared_ptr<std::atomic<bool>> runningFlag,
        std::shared_ptr<std::atomic<State>> state,
        std::shared_ptr<RenderingEngine> rendering
    );

    virtual ~EventEngine();

    static Result<std::shared_ptr<EventEngine>> New(
        std::shared_ptr<spdlog::logger> logger,
        std::shared_ptr<std::atomic<bool>> runningFlag,
        std::shared_ptr<std::atomic<State>> state,
        std::shared_ptr<RenderingEngine> rendering
    );

    Result<> Update();

    inline void EnableTextInput() { return SDL_StartTextInput(); }

    inline void DisableTextInput() { return SDL_StopTextInput(); }

    void SetLuaEventHandler(const LuaEvent event, std::shared_ptr<sol::function> handler);

private:
    SDL_Event m_Event;
    std::shared_ptr<spdlog::logger> m_Logger;
    std::shared_ptr<std::atomic<bool>> m_RunningFlag;
    std::shared_ptr<std::atomic<State>> m_State;
    std::shared_ptr<RenderingEngine> m_Rendering;
    std::array<std::optional<std::shared_ptr<sol::function>>, static_cast<size_t>(LuaEvent::_EnumeratorCount)> m_LuaHandlers;

    template <
        typename TEvent,
        typename = std::enable_if_t<std::is_base_of<luaInterop::Event, TEvent>::value>
    >
    Result<> RaiseLuaEvent(const LuaEvent type, const TEvent& args)
    {
        auto handler = m_LuaHandlers[static_cast<size_t>(type)];

        // No handler for this event
        if (!handler)
            return Result();

        auto result = (**handler)(args);
        if (!result.valid()) [[unlikely]] {
            sol::error err = result;
            m_Logger->error("Lua quit handler failed: {}", err.what());

            if constexpr (policies::script::CrashOnError)
                return Error(Error::Lua, err.what());
        }

        return Result();
    }
};

} // namespace engine

#endif // !ENG_EVENT_ENGINE_HPP
