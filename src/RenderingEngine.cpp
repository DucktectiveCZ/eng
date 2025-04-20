#include "RenderingEngine.hpp"
#include "Engine.hpp"
#include "Result.hpp"
#include "SDL_render.h"
#include "SDL_stdinc.h"
#include "SDL_video.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include <memory>
#include <spdlog/logger.h>
#include <spdlog/spdlog.h>

namespace engine {

RenderingEngine::RenderingEngine(const std::shared_ptr<spdlog::logger> logger, SDL_Window* window, SDL_Renderer* renderer)
    : m_Window(window)
    , m_Renderer(renderer)
    , m_Logger(logger)
{
}

RenderingEngine::~RenderingEngine()
{
    TTF_Quit();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
    spdlog::shutdown();
}

Result<RenderingEngine>
RenderingEngine::New(const std::shared_ptr<spdlog::logger> logger, const Config& cfg)
{
    // TODO: Check if SDL was already initialized

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        logger->critical("SDL init failed");
        return Error::Sdl;
    }
    if (!IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG)) {
        logger->critical("SDL Image init failed");
        return Error::Sdl;
    }
    if (!Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG)) {
        logger->critical("SDL Mixer init failed");
        return Error::Sdl;
    }
    if (TTF_Init() != 0) {
        logger->critical("SDL TTF init failed");
        return Error::Sdl;
    }

    auto window = SDL_CreateWindow(
        "Engine window",
        cfg.Window.X,
        cfg.Window.Y,
        cfg.Window.Width,
        cfg.Window.Height,
        SDL_WINDOW_HIDDEN);
    if (window == nullptr) {
        logger->error("Couldn't create window");
        return Error(Error::Sdl, SDL_GetError());
    }

    Uint32 rendererFlags = 0;
    if (cfg.Render.Accelerated) {
        rendererFlags |= SDL_RENDERER_ACCELERATED;
    }
    if (cfg.Render.VSync) {
        rendererFlags |= SDL_RENDERER_PRESENTVSYNC;
    }
    auto renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (window == nullptr) {
        logger->error("Couldn't create renderer from window");
        return Error(Error::Sdl, SDL_GetError());
    }

    return Result(RenderingEngine(logger, window, renderer));
}

}
