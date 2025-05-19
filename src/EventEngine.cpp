#include "EventEngine.hpp"

#include <memory>

#include <sol/error.hpp>
#include <sol/forward.hpp>
#include <SDL2/SDL_events.h>

#include "LuaInterop.hpp"

namespace engine {

EventEngine::EventEngine(
    std::shared_ptr<spdlog::logger> logger,
    std::shared_ptr<std::atomic<bool>> runningflag,
    std::shared_ptr<std::atomic<State>> state,
    std::shared_ptr<RenderingEngine> rendering
)
    : m_Event()
    , m_Logger(logger)
    , m_RunningFlag(runningflag)
    , m_State(state)
    , m_Rendering(rendering)
    , m_LuaHandlers()
{
}

EventEngine::~EventEngine()
{
    m_Logger->trace("Finalizing EventEngine");
}

Result<std::shared_ptr<EventEngine>> EventEngine::New(
    std::shared_ptr<spdlog::logger> logger,
    std::shared_ptr<std::atomic<bool>> runningFlag,
    std::shared_ptr<std::atomic<State>> state,
    std::shared_ptr<RenderingEngine> rendering
)
{
    return Result(std::make_shared<EventEngine>(logger, runningFlag, state, rendering));
}

Result<> EventEngine::Update()
{
    State state = m_State->load();

    while (SDL_PollEvent(&m_Event)) {
        const SDL_Event& e = m_Event;

        switch (e.type) {
        case SDL_QUIT: {
            [[unlikely]]

            m_Logger->trace("SDL_QUIT");

            if (auto res = RaiseLuaEvent(LuaEvent::Quitting, luaInterop::QuittingEvent()))
                return res;

            m_RunningFlag->store(false);
            break;
        }

        case SDL_MOUSEMOTION: {
            // m_Logger->trace("SDL_MOUSEMOTION x={} y={}", e.motion.x, e.motion.y);

            state.Mouse.Position.X = e.motion.x;
            state.Mouse.Position.Y = e.motion.y;

            luaInterop::MouseMoveEvent event(
                state.Mouse.Position.X,
                state.Mouse.Position.Y
            );

            if (auto res = RaiseLuaEvent(LuaEvent::MouseMove, event); !res)
                return res;

            m_State->store(state);
            break;
        }

        case SDL_MOUSEBUTTONDOWN: {
            m_Logger->trace("SDL_MOUSEBUTTONDOWN btn={}", e.button.button);

            switch (e.button.button) {
            case SDL_BUTTON_LEFT:
                state.Mouse.LeftButtonDown = true;
                break;
            case SDL_BUTTON_RIGHT:
                state.Mouse.RightButtonDown = true;
                break;
            case SDL_BUTTON_MIDDLE:
                state.Mouse.MiddleButtonDown = true;
                break;
            default:
                m_Logger->warn("Unknown SDL mouse button: {}", e.button.button);
                break;
            }

            luaInterop::MouseDownEvent event(
                state.Mouse.Position.X,
                state.Mouse.Position.Y,
                static_cast<luaInterop::MouseButton>(e.button.button)
            );

            if (auto res = RaiseLuaEvent(LuaEvent::MouseDown, event); !res)
                return res;

            break;
        }

        case SDL_MOUSEBUTTONUP: {
            m_Logger->trace("SDL_MOUSEBUTTONUP btn={}", e.button.button);
            switch (e.button.button) {
            case SDL_BUTTON_LEFT:
                state.Mouse.LeftButtonDown = false;
                break;
            case SDL_BUTTON_RIGHT:
                state.Mouse.RightButtonDown = false;
                break;
           case SDL_BUTTON_MIDDLE:
                state.Mouse.MiddleButtonDown = false;
                break;
            default:
                m_Logger->warn("Unknown SDL mouse button: {}", e.button.button);
                break;
            }

            luaInterop::MouseUpEvent event(
                state.Mouse.Position.X,
                state.Mouse.Position.Y,
                static_cast<luaInterop::MouseButton>(e.button.button)
            );

            if (auto res = RaiseLuaEvent(LuaEvent::MouseUp, event); !res)
                return res;

            break;
        }

        case SDL_APP_LOWMEMORY: {
            [[unlikely]]

            m_Logger->warn("Memory is low!");

            luaInterop::LowMemoryEvent event;

            if (auto res = RaiseLuaEvent(LuaEvent::LowMemory, event); !res)
                return res;

            break;
        }
        }
    }

    m_State->store(state);

    return Result();
}


void EventEngine::SetLuaEventHandler(const LuaEvent event, std::shared_ptr<sol::function> handler)
{
    auto& handlerToSet = m_LuaHandlers[static_cast<size_t>(event)];

    if (handlerToSet.has_value())
        m_Logger->warn("Overriding Lua event handler {}");

    handlerToSet = handler;
}

} // namespace engine

