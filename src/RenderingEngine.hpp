#ifndef ENG_RENDERING_ENGINE_HPP
#define ENG_RENDERING_ENGINE_HPP

#include <memory>
#include <string_view>

#include <SDL2/SDL.h>
#include <spdlog/logger.h>

#include "Config.hpp"
#include "Result.hpp"

namespace engine {

class RenderingEngine final {
public:
    RenderingEngine(const std::shared_ptr<spdlog::logger> logger, SDL_Window* window, SDL_Renderer* renderer);
    ~RenderingEngine();
    static Result<std::shared_ptr<RenderingEngine>> New(const std::shared_ptr<spdlog::logger> logger, const Config& cfg);

    void SetWindowTitle(const std::string_view title);

    void Update();

private:
    SDL_Window *m_Window;
    SDL_Renderer *m_Renderer;

protected:
    const std::shared_ptr<spdlog::logger> m_Logger;
};
}

#endif // !ENG_RENDERING_ENGINE_HPP
