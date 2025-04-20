#ifndef ENG_RENDERING_ENGINE_HPP
#define ENG_RENDERING_ENGINE_HPP

#include "Engine.hpp"
#include "Result.hpp"
#include "SDL_render.h"
#include "SDL_video.h"

#include <SDL2/SDL.h>
#include <spdlog/logger.h>

#include <memory>

namespace engine {
class RenderingEngine final {
public:
    ~RenderingEngine();
    static Result<RenderingEngine> New(const std::shared_ptr<spdlog::logger> logger, const Config& cfg);

private:
    RenderingEngine(const std::shared_ptr<spdlog::logger> logger, SDL_Window* window, SDL_Renderer* renderer);

    SDL_Window* m_Window;
    SDL_Renderer* m_Renderer;

protected:
    const std::shared_ptr<spdlog::logger> m_Logger;
};
}

#endif // !ENG_RENDERING_ENGINE_HPP
