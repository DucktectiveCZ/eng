#include <csignal>
#include <filesystem>
#include <memory>
#include <spdlog/spdlog.h>

#include "Engine.hpp"

int main(const int argc, const char **argv)
{
    auto e = engine::Engine::New(argc, argv).Unwrap();
    e->LoadGame(std::filesystem::path("/home/ducktectivecz/.duckengine/games/test/"), engine::GameFormat::FOLDER).Unwrap();
    e->Start().Unwrap();
}
