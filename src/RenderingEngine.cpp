#include "RenderingEngine.hpp"
#include "EngineMetadata.hpp"
#include "Result.hpp"
#include "SDL_error.h"
#include "SDL_render.h"
#include "SDL_stdinc.h"
#include "SDL_version.h"
#include "SDL_video.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include <csignal>
#include <cstring>
#include <memory>
#include <spdlog/logger.h>
#include <spdlog/spdlog.h>
#include <string_view>

namespace engine {

RenderingEngine::RenderingEngine(const std::shared_ptr<spdlog::logger> logger, SDL_Window* window, SDL_Renderer* renderer)
    : m_Window(window)
    , m_Renderer(renderer)
    , m_Logger(logger)
{
}

RenderingEngine::~RenderingEngine()
{
    SDL_DestroyWindow(m_Window);
    SDL_DestroyRenderer(m_Renderer);

    TTF_Quit();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
    spdlog::shutdown();
}

Result<std::shared_ptr<RenderingEngine>>
RenderingEngine::New(const std::shared_ptr<spdlog::logger> logger, const Config& cfg)
{
    if (SDL_WasInit(0)) {
        return Error(Error::Sdl, "SDL was already initialized");
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        logger->critical("SDL init failed");
        return Error::Sdl;
    }
    constexpr Uint32 imgFlags = IMG_INIT_JPG | IMG_INIT_PNG;
    if ((IMG_Init(imgFlags) & imgFlags) != imgFlags) {
        logger->critical("SDL Image init failed");
        SDL_Quit();
        return Error::Sdl;
    }
    constexpr Uint32 mixFlags = MIX_INIT_MP3 | MIX_INIT_OGG;
    if ((Mix_Init(mixFlags) & mixFlags) != mixFlags) {
        logger->critical("SDL Mixer init failed");
        SDL_Quit();
        IMG_Quit();
        return Error::Sdl;
    }
    if (TTF_Init() != 0) {
        logger->critical("SDL TTF init failed");
        SDL_Quit();
        IMG_Quit();
        TTF_Quit();
        return Error::Sdl;
    }

    const char *videoDriver = SDL_GetCurrentVideoDriver();

    const Uint32 windowFlags = SDL_WINDOW_SHOWN;

    auto window = SDL_CreateWindow(
        Metadata.FullTitle,
        cfg.Window.X,
        cfg.Window.Y,
        cfg.Window.Width,
        cfg.Window.Height,
        windowFlags );

    if (!window) {
        auto error = SDL_GetError();
        logger->error("Couldn't create window: {}", error);
        SDL_Quit();
        IMG_Quit();
        TTF_Quit();
        return Error(Error::Sdl, error);
    }

    Uint32 rendererFlags = 0;
    if (cfg.Render.Accelerated) {
        rendererFlags |= SDL_RENDERER_ACCELERATED;
    }
    if (cfg.Render.VSync) {
        rendererFlags |= SDL_RENDERER_PRESENTVSYNC;
    }

    auto renderer = SDL_CreateRenderer(window, -1, rendererFlags);

    if (!renderer) {
        auto error = SDL_GetError();
        logger->error("Couldn't create renderer from window: {}", error);
        SDL_Quit();
        IMG_Quit();
        TTF_Quit();
        SDL_DestroyWindow(window);
        return Error(Error::Sdl, error);
    }

    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    SDL_RendererInfo rendererInfo;
    if (SDL_GetRendererInfo(renderer, &rendererInfo) != 0) {
        logger->error("Couldn't retrieve the renderer info");
        return Error(Error::Sdl, "Couldn't retrieve the renderer info");
    }

    logger->info("Using SDL v{}.{}.{} with {} as a rendering backend on {}", SDL_MAJOR_VERSION, SDL_MINOR_VERSION, SDL_PATCHLEVEL, rendererInfo.name, videoDriver);

    return Result(std::make_shared<RenderingEngine>(logger, window, renderer));
}

void RenderingEngine::SetWindowTitle(const std::string_view title)
{
    m_Logger->trace("Setting the window title");
    SDL_SetWindowTitle(m_Window, title.data());
}

} // namespace engine
