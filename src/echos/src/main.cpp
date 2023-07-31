#include <memory>

#include "core/game.h"

int main(int argc, char **argv) {
    const auto game {std::make_unique<core::Game>(800, 600, "Echos")};
    game->Run();
    return 0;
}