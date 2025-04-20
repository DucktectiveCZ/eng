#include "Engine.hpp"
#include "ScriptEngine.hpp"

#include <csignal>
#include <filesystem>
#include <spdlog/spdlog.h>

int main(const int argc, const char* argv[])
{
    auto script = engine::ScriptEngine::New(spdlog::default_logger()).Unwrap();
    script.Execute("print('test')").Unwrap();

    return 0;

    auto e = engine::Engine::New(argc, argv).Unwrap();
    auto g = e.LoadGame(std::filesystem::path("/home/ducktectivecz/.duckengine/games/test/"), engine::GameFormat::FOLDER).Unwrap();
    e.StartGame(g).Unwrap();
}
