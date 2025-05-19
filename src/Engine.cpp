#include "Engine.hpp"

#include <algorithm>
#include <atomic>
#include <cerrno>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <memory>
#include <optional>
#include <string>
#include <string_view>

#include <spdlog/common.h>
#include <spdlog/logger.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>
#include <fmt/format.h>
#include <tinyxml2.h>
#include <toml++/impl/parser.hpp>
#include <toml++/impl/table.hpp>
#include <toml++/toml.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include "EngineMetadata.hpp"
#include "Game.hpp"
#include "Platform.hpp"
#include "Result.hpp"
#include "ScriptEngine.hpp"
#include "Util.hpp"

#define FORCE_TRACE

namespace engine {

Engine::Engine(
    Config&& cfg,
    std::shared_ptr<spdlog::logger> logger,
    std::shared_ptr<ScriptEngine> script, std::shared_ptr<RenderingEngine> rendering,
    std::shared_ptr<EventEngine> event,
    std::shared_ptr<std::atomic<bool>> runningFlag,
    std::shared_ptr<std::atomic<State>> state
)
    : m_Cfg(std::move(cfg))
    , m_Game(std::nullopt)
    , m_Logger(logger)
    , m_Script(script)
    , m_Rendering(rendering)
    , m_Event(event)
    , m_RunningFlag(runningFlag)
    , m_State(state)
{
}

Engine::~Engine()
{
    m_Logger->trace("Finalizing Engine");
}

Result<std::shared_ptr<Engine>> Engine::New(const int argc, const char** argv)
{
    // TODO: Load a config from a config file and console line args. Also, initialize all dependencies.

    auto logger = spdlog::stdout_color_mt("console");
    logger->set_pattern("\033[90m%Y-%m-%d %H:%M:%S t%t %^[%l]%$ %v");
    if (argc > 1) {
        if (!strcmp(argv[1], "trace")) {
            logger->set_level(spdlog::level::trace);
            logger->info("Trace log level");
            SDL_LogSetAllPriority(SDL_LOG_PRIORITY_VERBOSE);
        } else if (!strcmp(argv[1], "debug")) {
            logger->set_level(spdlog::level::debug);
            logger->info("Debug log level");
        }
    }
#ifdef FORCE_TRACE
    logger->set_level(spdlog::level::trace);
    SDL_LogSetAllPriority(SDL_LOG_PRIORITY_VERBOSE);
#endif
    logger->trace("Console logger created");

    Config cfg = Config::Default();

    auto runningFlag = std::make_shared<std::atomic<bool>>();
    runningFlag->store(true);

    auto state = std::shared_ptr<std::atomic<State>>(new std::atomic<State>{State()});

    auto rendering = RenderingEngine::New(logger, cfg);
    if (rendering.IsErr()) {
        logger->error("Creation of the rendering engine failed: {}", rendering.UnwrapErr().ToString());
        return rendering.UnwrapErr();
    }
    auto script = ScriptEngine::New(logger, runningFlag);
    if (script.IsErr()) {
        logger->error("Creation of the script engine failed: {}", script.UnwrapErr().ToString());
        return script.UnwrapErr();
    }
    auto event = EventEngine::New(
        logger,
        runningFlag,
        state,
        *rendering
    );

    return Result(std::make_shared<Engine>(
        std::move(cfg),
        logger,
        script.Unwrap(),
        rendering.Unwrap(),
        event.Unwrap(),
        runningFlag,
        state
    ));
}

Result<> Engine::LoadGame(const std::filesystem::path& path, const GameFormat format)
{
    if (m_Game.has_value()) {
        m_Logger->error("Can not load a new game as there already is one loaded.");
        return Error(Error::InvalidState, "Game is already loaded");
    }

    m_Logger->trace("Loading game {} with format {}", path.string(), (int)format);

    if (!std::filesystem::exists(path)) {
        m_Logger->error("File doesn't exist", path.string());
        return Error(Error::InvalidGame, fmt::format("File doesn't exist: {}", path.string()));
    }
    if (!std::filesystem::is_directory(path)) {
        m_Logger->error("A format {} game has to be a folder", (int)format);
        return Error::InvalidGame;
    }
    if (!std::filesystem::exists(path / "game.toml")) {
        m_Logger->error("Missing metadata file");
        return Error::InvalidGame;
    }
    if (!std::filesystem::exists(path / "resources.xml")) {
        m_Logger->error("Missing resource table");
        return Error::InvalidGame;
    }

    std::ifstream metadataFile(path / "game.toml");
    if (!metadataFile) {
        m_Logger->error("Couldn't open metadata file: errno {}: '{}'", errno, std::strerror(errno));
        return Error::Io;
    }

    auto metadataToml = toml::parse_file((path / "game.toml").string());

    if (!metadataToml["meta"]["name"].is_string()) {
        m_Logger->error("Required field `name` is missing");
        return Error::InvalidGame;
    }
    if (!metadataToml["meta"]["title"].is_string()) {
        m_Logger->error("Required field `title` is missing");
        return Error::InvalidGame;
    }
    if (!metadataToml["meta"]["description"].is_string()) {
        m_Logger->error("Required field `meta.description` is missing");
        return Error::InvalidGame;
    }
    if (!metadataToml["meta"]["author"].is_string()) {
        m_Logger->error("Required field `meta.author` is missing");
        return Error::InvalidGame;
    }
    if (!metadataToml["meta"]["license"].is_string()) {
        m_Logger->error("Required field `meta.license` is missing");
        return Error::InvalidGame;
    }
    if (!metadataToml["meta"]["version"].is_string()) {
        m_Logger->error("Required field `meta.version` is missing");
        return Error::InvalidGame;
    }
    if (!metadataToml["target"]["platforms"].is_array()) {
        m_Logger->error("Required field `target.platforms` is missing");
        return Error::InvalidGame;
    }
    if (!metadataToml["target"]["lua"].is_string()) {
        m_Logger->error("Required field `target.platforms` is missing");
        return Error::InvalidGame;
    }
    if (!metadataToml["game"]["entry_scene"].is_string()) {
        m_Logger->error("Required field `target.platforms` is missing");
        return Error::InvalidGame;
    }
    if (!metadataToml["graphics"]["resolution"].is_array()) {
        m_Logger->error("Required field `target.platforms` is missing");
        return Error::InvalidGame;
    }
    if (!metadataToml["graphics"]["fullscreen"].is_boolean()) {
        m_Logger->error("Required field `target.platforms` is missing");
        return Error::InvalidGame;
    }
    if (!metadataToml["graphics"]["allow_resizing"].is_boolean()) {
        m_Logger->error("Required field `target.platforms` is missing");
        return Error::InvalidGame;
    }
    if (!metadataToml["audio"]["volume"].is_floating_point()) {
        m_Logger->error("Required field `target.platforms` is missing");
        return Error::InvalidGame;
    }

    game::Game game;

    game.Meta.Name = metadataToml["meta"]["name"].as_string()->get();
    game.Meta.Title = metadataToml["meta"]["title"].as_string()->get();
    game.Meta.Description = metadataToml["meta"]["description"].as_string()->get();
    game.Meta.Author = metadataToml["meta"]["author"].as_string()->get();
    game.Meta.License = metadataToml["meta"]["license"].as_string()->get();
    game.Meta.Version = util::Version::FromString(metadataToml["meta"]["version"].as_string()->get()).UnwrapOrDefault(util::Version::Max());
    if (game.Meta.Version == util::Version::Max()) {
        m_Logger->error("Invalid version format");
        return Error::InvalidGame;
    }

    for (auto&& platformNode : *metadataToml["target"]["platforms"].as_array()) {
        if (!platformNode.is_string()) {
            m_Logger->error("Invalid platform format!");
            return Error::InvalidGame;
        }

        auto platform = platformNode.as_string()->get();
        if (platform == "Linux") {
            game.Meta.Target.Platforms.emplace_back(game::Platform::Linux);
        } else if (platform == "MacOS") {
            game.Meta.Target.Platforms.emplace_back(game::Platform::Darwin);
        } else if (platform == "Windows") {
            game.Meta.Target.Platforms.emplace_back(game::Platform::Windows);
        } else {
            m_Logger->error("Unknown platform: {}", platform);
            return Error::InvalidGame;
        }
    }

    std::string luaTarget = metadataToml["target"]["lua"].as_string()->get();
    if (luaTarget == "5.4") {
        game.Meta.Target.Lua = game::LuaTarget::Lua54;
    } else if (luaTarget == "5.1") {
        game.Meta.Target.Lua = game::LuaTarget::Lua51;
    } else if (luaTarget == "JIT") {
        game.Meta.Target.Lua = game::LuaTarget::LuaJit;
    } else {
        m_Logger->error("Unknown lua target: {}", luaTarget);
        return Error::InvalidGame;
    }

    game.Meta.Game.EntryScene = metadataToml["game"]["entry_scene"].as_string()->get();

    auto resolutionArray = *metadataToml["graphics"]["resolution"].as_array();
    if (!resolutionArray[0].is_integer() || !resolutionArray[1].is_integer()) {
        m_Logger->error("Invalid resolution");
        return Error::InvalidGame;
    }
    game.Meta.Graphics.WindowResolution.Width = resolutionArray[0].as_integer()->get();
    game.Meta.Graphics.WindowResolution.Height = resolutionArray[1].as_integer()->get();

    game.Meta.Graphics.WindowFullscreen = metadataToml["graphics"]["fullscreen"].as_boolean()->get();
    game.Meta.Graphics.WindowResizing = metadataToml["graphics"]["allow_resizing"].as_boolean()->get();

    game.Meta.Audio.Volume = metadataToml["audio"]["volume"].as_floating_point()->get();

    if (game.Meta.Audio.Volume > 1 || game.Meta.Audio.Volume < 0) {
        m_Logger->error("The audio volue must be in the range 0-1");
        return Error::InvalidGame;
    }

    tinyxml2::XMLDocument resourceTableXml;
    auto xmlError = resourceTableXml.LoadFile((path / "resources.xml").c_str());
    if (xmlError != tinyxml2::XML_SUCCESS) {
        m_Logger->error("Error loading the resource table: {}", resourceTableXml.ErrorStr());
        return Error::Io;
    }

    auto rootElem = resourceTableXml.RootElement();
    if (rootElem == nullptr) {
        m_Logger->error("No root element in resources.xml");
        return Error::InvalidGame;
    }
    if (std::string_view(rootElem->Name()) != "ResourceTable") {
        m_Logger->error("The root element isn't a resourceTable");
        return Error(Error::InvalidGame, "The root element isn't a resourceTable");
    }

    for (auto element = rootElem->FirstChildElement("Resource"); element != nullptr; element = element->NextSiblingElement("Resource")) {
        auto type = element->Attribute("type");
        auto key = element->Attribute("key");
        auto source = element->Attribute("source");

        if (!type || !key || !source) {
            m_Logger->error("The resource is missing a type or key or source");
            return Error::InvalidGame;
        }


        game::ResourceDef res;
        if (std::string_view(type) == "Text") {
            res.Type = game::ResourceType::Text;
        } else if (std::string_view(type) == "Sprite") {
            res.Type = game::ResourceType::Sprite;
        } else if (std::string_view(type) == "Music") {
            res.Type = game::ResourceType::Music;
        } else if (std::string_view(type) == "Sound") {
            res.Type = game::ResourceType::SoundEffect;
        } else if (std::string_view(type) == "Font") {
            res.Type = game::ResourceType::Font;
        } else if (std::string_view(type) == "Anim") {
            res.Type = game::ResourceType::Animation;
        } else {
            m_Logger->error("Invalid resource type: {}", type);
            return Error::InvalidGame;
        }
        res.Key = key;
        res.Source = source;
    }

    m_Game = game;

    return Result();
}

Result<> Engine::Update()
{
    if (auto res = m_Event->Update(); !res)
        return res;

    // m_Script->Update();

    return m_Rendering->Update();
}

Result<> Engine::Start() {
    if (!m_Game.has_value()) {
        m_Logger->error("No game loaded");
        return Error(Error::InvalidState, "No game loaded");
    }

    {
        auto pplatf = GetPlatform();
        auto platfOpt = game::FromPlatformPlatform(pplatf);
        if (!platfOpt.has_value()) {
            m_Logger->error("Unknown platform");
            return Error(Error::UnknownEnumVariant, "Unknown platform");
        }
        auto platf = platfOpt.value();

        if (
            pplatf == Platform::Unknown
            || std::find(m_Game->Meta.Target.Platforms.begin(), m_Game->Meta.Target.Platforms.end(), platf) == m_Game->Meta.Target.Platforms.end()
        ) {
            m_Logger->critical("Platform not supported!");
            return Error(Error::UnsupportedPlatform, "Platform not supported");
        }
    }

    m_Logger->warn("Omitting lua target check");

    m_Rendering->SetWindowTitle(fmt::format("{} - {}", m_Game->Meta.Title, Metadata.Title));

    m_Logger->trace("Entering the main loop");

    Result<> res;
    while (m_RunningFlag->load()) {
        res = Update();
        if (res.IsErr())
            return res;
    }

    return Result();
}

void Engine::Shutdown() {
    m_Logger->trace("Shutting down");
    m_RunningFlag->store(false);
}

} // namespace engine

